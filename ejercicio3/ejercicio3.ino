/*
 * =====================================================================================
 *  Bienvenidos a Sys On Chip
 * =====================================================================================
 *  Ejercicio No. 3 – Semáforo con botón de peatón robusto
 *
 *  Descripción general:
 *  Este programa implementa un semáforo vehicular con solicitud peatonal
 *  utilizando una arquitectura basada en:
 *
 *   1) Máquina de estados finitos (FSM).
 *   2) Temporización no bloqueante con millis().
 *   3) Interrupciones externas (ISR).
 *   4) Protección contra rebote (debounce por software).
 *
 *  A diferencia del Ejercicio No.2, aquí se introduce un evento externo:
 *  un botón de peatón que genera una interrupción cuando es presionado.
 *
 *  La rutina de interrupción (ISR) está diseñada bajo buenas prácticas:
 *   - Es mínima (no contiene delays ni código pesado).
 *   - Solo genera un evento.
 *   - Utiliza variables compartidas declaradas como volatile.
 *   - Implementa debounce por software.
 *   - Solo acepta solicitudes cuando el sistema está en estado VERDE.
 *
 *  Secuencia de funcionamiento:
 *
 *      VERDE  → AMARILLO → ROJO → VERDE
 *
 *  Si el peatón presiona el botón durante VERDE,
 *  el sistema fuerza la transición controlada hacia AMARILLO.
 *
 * =====================================================================================
 */


// -------------------------------------------------------------------------------------
// Definición de pines
// -------------------------------------------------------------------------------------

const uint8_t pin_verde    = 2;
const uint8_t pin_amarillo = 3;
const uint8_t pin_rojo     = 4;
const uint8_t pin_boton    = 8;


// -------------------------------------------------------------------------------------
// Definición de tiempos (milisegundos)
// -------------------------------------------------------------------------------------

const unsigned long tiempo_verde    = 5000;
const unsigned long tiempo_amarillo = 1000;
const unsigned long tiempo_rojo     = 5000;

const unsigned long tiempo_debounce = 200;


// -------------------------------------------------------------------------------------
// Definición de la máquina de estados
// -------------------------------------------------------------------------------------

enum EstadoSemaforo {
  ESTADO_VERDE,
  ESTADO_AMARILLO,
  ESTADO_ROJO
};

// Estado actual (volatile porque es leído dentro de una ISR)
volatile EstadoSemaforo estado_actual = ESTADO_VERDE;


// -------------------------------------------------------------------------------------
// Variables compartidas con la ISR
// -------------------------------------------------------------------------------------

volatile bool solicitud_peaton = false;     // Evento generado por el botón
volatile unsigned long ultimo_disparo = 0;  // Para control de debounce

unsigned long tiempo_anterior = 0;          // Referencia temporal para FSM


// -------------------------------------------------------------------------------------
// Rutina de Interrupción (ISR)
// -------------------------------------------------------------------------------------
// Se ejecuta automáticamente cuando el botón detecta un flanco FALLING.
// Debe ser lo más corta y eficiente posible.

void ISR_boton() {

  unsigned long ahora = millis();

  // Condiciones:
  // 1) Debounce por tiempo
  // 2) Solo aceptar si el estado actual es VERDE
  if ((ahora - ultimo_disparo > tiempo_debounce) &&
      (estado_actual == ESTADO_VERDE)) {

    solicitud_peaton = true;   // Generamos evento
    ultimo_disparo = ahora;    // Actualizamos referencia temporal
  }
}


// -------------------------------------------------------------------------------------
// Función setup()
// -------------------------------------------------------------------------------------

void setup() {

  // Configuración de salidas
  pinMode(pin_verde, OUTPUT);
  pinMode(pin_amarillo, OUTPUT);
  pinMode(pin_rojo, OUTPUT);

  // Configuración del botón con resistencia interna pull-up
  pinMode(pin_boton, INPUT_PULLUP);

  // Asociación de la interrupción externa al pin del botón
  attachInterrupt(digitalPinToInterrupt(pin_boton),
                  ISR_boton,
                  FALLING);

  // Inicialización temporal
  tiempo_anterior = millis();
}


// -------------------------------------------------------------------------------------
// Función loop()
// -------------------------------------------------------------------------------------
// Implementación de la máquina de estados principal.

void loop() {

  unsigned long tiempo_actual = millis();

  switch (estado_actual) {

    // =====================================================
    // ESTADO VERDE
    // =====================================================
    case ESTADO_VERDE:

      digitalWrite(pin_verde, HIGH);
      digitalWrite(pin_amarillo, LOW);
      digitalWrite(pin_rojo, LOW);

      // Evento externo: botón de peatón
      if (solicitud_peaton) {
        solicitud_peaton = false;          // Consumimos el evento
        tiempo_anterior = tiempo_actual;   // Reiniciamos temporización
        estado_actual = ESTADO_AMARILLO;
      }

      // Evento por temporización normal
      else if (tiempo_actual - tiempo_anterior >= tiempo_verde) {
        tiempo_anterior = tiempo_actual;
        estado_actual = ESTADO_AMARILLO;
      }

      break;


    // =====================================================
    // ESTADO AMARILLO
    // =====================================================
    case ESTADO_AMARILLO:

      digitalWrite(pin_verde, LOW);
      digitalWrite(pin_amarillo, HIGH);
      digitalWrite(pin_rojo, LOW);

      if (tiempo_actual - tiempo_anterior >= tiempo_amarillo) {
        tiempo_anterior = tiempo_actual;
        estado_actual = ESTADO_ROJO;
      }

      break;


    // =====================================================
    // ESTADO ROJO
    // =====================================================
    case ESTADO_ROJO:

      digitalWrite(pin_verde, LOW);
      digitalWrite(pin_amarillo, LOW);
      digitalWrite(pin_rojo, HIGH);

      if (tiempo_actual - tiempo_anterior >= tiempo_rojo) {
        tiempo_anterior = tiempo_actual;
        estado_actual = ESTADO_VERDE;
      }

      break;
  }

  // -----------------------------------------------------------------
  // Aquí podrían agregarse tareas concurrentes:
  // - Comunicación serial
  // - WiFi
  // - Sensores
  // - Watchdog
  //
  // La arquitectura sigue siendo no bloqueante.
  // -----------------------------------------------------------------
}
