/* 
 * =====================================================================================
 *  Bienvenidos a Sys On Chip
 * =====================================================================================
 *  Ejercicio No. 1 – Simulación básica de un semáforo con Arduino UNO
 *
 *  Descripción general:
 *  Este programa implementa la simulación del funcionamiento de un semáforo
 *  vehicular utilizando tres LEDs conectados a pines digitales del Arduino UNO.
 *
 *  El objetivo es introducir los fundamentos del control de salidas digitales
 *  en sistemas embebidos:
 *
 *   1) Configuración de pines como salidas digitales.
 *   2) Escritura de niveles lógicos HIGH (5V) y LOW (0V).
 *   3) Control temporal mediante retardos con la función delay().
 *
 *  Secuencia de funcionamiento:
 *
 *      - LED Rojo   → encendido durante 4 segundos.
 *      - LED Verde  → encendido durante 6 segundos.
 *      - LED Ámbar  → encendido durante 2 segundos.
 *
 *  Esta secuencia se repite indefinidamente dentro de la función loop(),
 *  simulando el comportamiento continuo de un semáforo real.
 *
 *  Nota técnica importante:
 *  La función delay() detiene completamente la ejecución del microcontrolador
 *  durante el tiempo especificado. Esto simplifica el diseño para un ejercicio
 *  inicial, pero no es adecuado para sistemas más complejos que requieran
 *  multitarea o respuesta a eventos externos.
 *
 * =====================================================================================
 */


// -------------------------------------------------------------------------------------
// Definición de constantes
// -------------------------------------------------------------------------------------
// Se utilizan constantes para identificar claramente los pines donde están conectados
// los LEDs. Esto evita el uso de "números mágicos" dentro del código y facilita
// futuras modificaciones.

const int LED_Rojo   = 4;   // LED rojo conectado al pin digital 4
const int LED_Ambar  = 3;   // LED ámbar conectado al pin digital 3
const int LED_Verde  = 2;   // LED verde conectado al pin digital 2


// -------------------------------------------------------------------------------------
// Función setup()
// -------------------------------------------------------------------------------------
// Esta función se ejecuta una sola vez cuando el Arduino se energiza o reinicia.
// Aquí se configuran los pines y se establece el estado inicial del sistema.

void setup() { 
  
  // Configuración de los pines como salidas digitales
  // Esto permite que el microcontrolador entregue tensión (HIGH) o 0V (LOW)
  // a los LEDs conectados.
  pinMode(LED_Rojo, OUTPUT);
  pinMode(LED_Ambar, OUTPUT);
  pinMode(LED_Verde, OUTPUT);

  // Inicialización del sistema en un estado seguro:
  // Todos los LEDs apagados al comenzar la ejecución.
  digitalWrite(LED_Rojo, LOW);
  digitalWrite(LED_Ambar, LOW);
  digitalWrite(LED_Verde, LOW);
}


// -------------------------------------------------------------------------------------
// Función loop()
// -------------------------------------------------------------------------------------
// Esta función se ejecuta de manera repetitiva e indefinida.
// Contiene la secuencia principal del semáforo.

void loop() {

  // ===============================
  // ESTADO 1: LUZ ROJA
  // ===============================
  // Se coloca el pin en nivel lógico HIGH (≈5V),
  // lo que permite el paso de corriente a través del LED.
  digitalWrite(LED_Rojo, HIGH);

  // Se mantiene encendido durante 4 segundos (4000 milisegundos).
  delay(4000);

  // Se apaga el LED colocando el pin en nivel LOW (0V).
  digitalWrite(LED_Rojo, LOW);


  // ===============================
  // ESTADO 2: LUZ VERDE
  // ===============================
  digitalWrite(LED_Verde, HIGH);

  // Permanece encendido durante 6 segundos.
  delay(6000);

  digitalWrite(LED_Verde, LOW);


  // ===============================
  // ESTADO 3: LUZ ÁMBAR
  // ===============================
  digitalWrite(LED_Ambar, HIGH);

  // Permanece encendido durante 2 segundos.
  delay(2000);

  digitalWrite(LED_Ambar, LOW);

  // Al finalizar este bloque, el programa vuelve automáticamente
  // al inicio de loop() y repite la secuencia indefinidamente.
}
