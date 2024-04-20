#define TIMEOUT_MS 5000 // Tiempo de espera en milisegundos
#define MAX_BUFFER_SIZE 64 // Tamaño máximo del buffer

void setup() {
  Serial.begin(9600); // Inicializa el puerto serial
}

void loop() {
  char buffer[MAX_BUFFER_SIZE]; // Buffer para almacenar la cadena recibida
  memset(buffer, 0, sizeof(buffer)); // Limpia el buffer

  unsigned long startTime = millis(); // Guarda el tiempo de inicio

  int index = 0; // Índice para rastrear la posición actual en el buffer

  while (true) {
    // Verifica si hay datos disponibles para leer
    if (Serial.available()) {
      char c = Serial.read(); // Lee un carácter del puerto serial
      
       startTime = millis();
      

      // Verifica si el carácter es un salto de línea ('\n') o el buffer está lleno
      if (c == 13 || index >= MAX_BUFFER_SIZE - 1) {
        // Finaliza la cadena con un carácter nulo
        buffer[index] = '\0';
        break; // Sale del bucle
      }
      
      // Almacena el carácter en el buffer
      buffer[index++] = c;
    }
    
    // Verifica si ha pasado el tiempo de espera
    if (millis() - startTime > TIMEOUT_MS) {
      // Si ha pasado el tiempo de espera, finaliza la lectura
      break;
    }
  }

  // Imprime la cadena recibida en el monitor serial
  Serial.write("Cadena recibida: ");
  Serial.write(buffer);
}
