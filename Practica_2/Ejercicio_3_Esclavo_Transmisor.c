#include <Wire.h>

#define SLAVE_ADDRESS 8 // Dirección del esclavo

String message = "Hola";

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
}

void loop() {
  // No se necesita código en el loop principal
}

void requestEvent() {
  Wire.write(message.c_str(), message.length()); // Enviar la cadena al maestro
}
