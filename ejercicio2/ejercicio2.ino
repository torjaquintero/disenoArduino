/* 
 *  Bienvenidos a Sys On Chip
 * ==============================
 * Ejercicio No.2
 * En este programa vamos a simular el funcionamiento de un semáforo
 * utilizando temporización NO bloqueante con millis().
 * A diferencia del ejercicio anterior, aquí no usamos delay(),
 * lo que permite que el microcontrolador ejecute otras tareas
 * mientras controla los tiempos del semáforo.
 * ==============================================================================================
 */

// ==============================
// Definición de pines
// ==============================
// Creamos constantes para identificar los pines donde están conectados los LEDs
const int LED_Rojo   = 4;
const int LED_Ambar  = 3;
const int LED_Verde  = 2;

// ==============================
// Definición de tiempos (en milisegundos)
// ==============================
// Estos valores determinan cuánto tiempo permanece activo cada estado
const unsigned long TIEMPO_ROJO   = 4000;
const unsigned long TIEMPO_VERDE  = 6000;
const unsigned long TIEMPO_AMBAR  = 2000;

// ==============================
// Definición de los estados del sistema
// ==============================
// Creamos un tipo enumerado para modelar la máquina de estados
enum EstadoSemaforo {
  ROJO,
  VERDE,
  AMBAR
};

// Variable que almacena el estado actual del semáforo
EstadoSemaforo estadoActual = ROJO;

// Variable que almacena el instante en que ocurrió el último cambio de estado
unsigned long tiempoAnterior = 0;

// ==============================
// Función setup()
// ==============================
// En esta función configuramos los pines como salida
// y definimos el estado inicial del sistema
void setup() {
  pinMode(LED_Rojo, OUTPUT);
  pinMode(LED_Ambar, OUTPUT);
  pinMode(LED_Verde, OUTPUT);

  // Iniciar en ROJO
  digitalWrite(LED_Rojo, HIGH);
  digitalWrite(LED_Verde, LOW);
  digitalWrite(LED_Ambar, LOW);

  tiempoAnterior = millis();
}

// ==============================
// Función loop()
// ==============================
// En esta función implementamos la máquina de estados
// utilizando temporización basada en millis()
void loop() {

  // Capturamos el tiempo actual del sistema
  unsigned long tiempoActual = millis();

  // Evaluamos el estado actual del semáforo
  switch (estadoActual) {

    // ==============================
    // Estado ROJO
    // ==============================
    case ROJO:

      // Verificamos si ha transcurrido el tiempo configurado
      if (tiempoActual - tiempoAnterior >= TIEMPO_ROJO) {

        // Actualizamos referencia temporal
        tiempoAnterior = tiempoActual;

        // Cambiamos al siguiente estado
        estadoActual = VERDE;

        // Actualizamos salidas
        digitalWrite(LED_Rojo, LOW);
        digitalWrite(LED_Verde, HIGH);
      }
      break;

    // ==============================
    // Estado VERDE
    // ==============================
    case VERDE:

      if (tiempoActual - tiempoAnterior >= TIEMPO_VERDE) {

        tiempoAnterior = tiempoActual;
        estadoActual = AMBAR;

        digitalWrite(LED_Verde, LOW);
        digitalWrite(LED_Ambar, HIGH);
      }
      break;

    // ==============================
    // Estado AMBAR
    // ==============================
    case AMBAR:

      if (tiempoActual - tiempoAnterior >= TIEMPO_AMBAR) {

        tiempoAnterior = tiempoActual;
        estadoActual = ROJO;

        digitalWrite(LED_Ambar, LOW);
        digitalWrite(LED_Rojo, HIGH);
      }
      break;
  }

  // En esta zona podrían ejecutarse otras tareas
  // como lectura de sensores, comunicación serial o WiFi
}
