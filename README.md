# disenoArduino

# Ejercicio No. 1

Este programa implementa la simulación básica de un semáforo vehicular utilizando tres LEDs conectados a pines digitales del **Arduino UNO**. A través de la configuración de los pines como salidas y el control de niveles lógicos HIGH y LOW, el sistema ejecuta una secuencia temporal donde el LED rojo permanece encendido durante 4 segundos, el verde durante 6 segundos y el ámbar durante 2 segundos, repitiéndose el ciclo de manera indefinida. El ejercicio introduce los fundamentos del manejo de salidas digitales en sistemas embebidos, así como el uso de retardos bloqueantes mediante la función `delay()`, sirviendo como punto de partida para comprender arquitecturas de control más avanzadas basadas en máquinas de estado y temporización no bloqueante.

# Ejercicio No. 2

Este programa implementa la simulación de un semáforo vehicular en el Arduino UNO, utilizando una arquitectura basada en máquina de estados y temporización no bloqueante mediante la función millis(). A diferencia del ejercicio anterior, no se emplea delay(), lo que permite que el microcontrolador continúe ejecutando otras tareas mientras controla los tiempos de cada estado. El sistema define tres estados (ROJO, VERDE y ÁMBAR) mediante un tipo enumerado (enum) y realiza las transiciones cuando se cumple el intervalo temporal correspondiente (4 s, 6 s y 2 s respectivamente). Este enfoque introduce un modelo de diseño más cercano a aplicaciones embebidas reales, donde la concurrencia cooperativa y la gestión eficiente del tiempo son fundamentales para integrar sensores, comunicación serial o conectividad WiFi sin bloquear la CPU.

# Ejercicio No. 3

Este programa implementa un semáforo vehicular con solicitud peatonal sobre **Arduino UNO**, incorporando una arquitectura más robusta basada en máquina de estados finitos (FSM), temporización no bloqueante con `millis()` e interrupciones externas. El sistema utiliza una rutina de servicio de interrupción (ISR) mínima para detectar la pulsación del botón de peatón, aplicando debounce por software y aceptando solicitudes únicamente cuando el semáforo se encuentra en estado VERDE. Las variables compartidas entre la ISR y el programa principal están declaradas como `volatile`, garantizando coherencia en el acceso concurrente. Esta implementación introduce conceptos fundamentales de diseño embebido profesional, como gestión de eventos asíncronos, separación entre lógica de control y generación de eventos, y arquitectura reactiva sin bloqueo de CPU.
