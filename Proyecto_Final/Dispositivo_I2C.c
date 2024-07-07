#include <Wire.h>

// Dirección I2C del convertidor UART-I2C
#define CONVERTIDOR 0x08

void setup() {
  Wire.begin(); // Inicia la comunicación I2C
  Serial.begin(9600); // Inicia la comunicación serie para debug
  


  // Registrar la función de recepción
  Wire.onReceive(recibirDatos);

}

void loop() {
  // Enviar datos a través de I2C
  enviarDatos_UART1("aaa");
  enviarDatos_UART2("aaa");
  delay(1000);
  enviarDatos_UART1("O");
  enviarDatos_UART2("O");
  delay(1000);
  
  // Recibir datos a través de I2C
  String datosRecibidos = recibirDatos();
  Serial.println("Datos recibidos: " + datosRecibidos);

  delay(1000); // Espera 1 segundo antes de la siguiente iteración
}

void enviarDatos_UART1(String mensaje) {
  Wire.beginTransmission(8);
  Wire.write('1');
  //Wire.write('0');
  Wire.write(mensaje.c_str());
  Wire.endTransmission();
  Serial.println("Mensaje enviado a UART1: " + mensaje);
}

void enviarDatos_UART2(String mensaje) {
  Wire.beginTransmission(8);
  Wire.write('2');
  //Wire.write('0');
  Wire.write(mensaje.c_str());
  
  
  Wire.endTransmission();
  Serial.println("Mensaje enviado a UART2: " + mensaje);
}


String recibirDatos() {
  Wire.requestFrom(8, 20); // Solicita hasta 32 bytes de datos

  String datos = "";
  while (Wire.available()) {
    char c = Wire.read();
    datos += c;
  }
  
  return datos;
}

//void recibirDatos(int bytes) {
//  while (Wire.available()) {
//    char c = Wire.read();
//    Serial.print("Recibido: ");
//    Serial.println(c);
//  }
//}
