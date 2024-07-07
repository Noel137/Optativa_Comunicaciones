#include <Wire.h>
#include <SoftwareSerial.h>

// Configura los pines para UART adicional
//SoftwareSerial mySerial2(3, 11); // RX, TX
//SoftwareSerial mySerial1(12, 13); // RX, TX

SoftwareSerial mySerial2(12, 13); // RX, TX
SoftwareSerial mySerial1(3, 11); // RX, TX


// Dirección I2C del dispositivo
const int convertidor = 8; // Dirección I2C del Arduino como esclavo

char receivedData1 ;
char receivedData2 ;

String datos_UART1 = "1: ";
String datos_UART2 = " 2: ";
  

void setup() {
  // Inicia la comunicación serie a 9600 baudios
  Serial.begin(9600);
  mySerial2.begin(9600);
  mySerial1.begin(9600);
  //mySerial2.begin(9600);

  // Inicia la comunicación I2C como esclavo
  Wire.begin(convertidor);

  // Funcion para cuando recive
  Wire.onReceive(receiveEvent);

  // Funcion para cuando el maestro requiere
  Wire.onRequest(requestEvent);

  // Mensaje de inicio
  Serial.println("Iniciando convertidor bidireccional UART-I2C...");
}

void loop() {
  // Verifica si hay datos disponibles en los puertos serie
    int c1 = 0;
    int c2 = 0;

    if (Serial.available() > 0 && c1 < 6) {
      receivedData1 = Serial.read();
      datos_UART1 +=  receivedData1;
      //Serial.print("           ");
      //Serial.print(receivedData1);
      c1++;
      if(c1 == 6){
        c2 = 0;
      }
    }
    
    if (mySerial1.available() > 0 && c2 < 6) {
      receivedData2 = mySerial1.read();
      datos_UART2 +=  receivedData2;
      //Serial.print("           ");
      //Serial.print(receivedData2);
      c2 ++;
      if(c2 == 6){
        c1 = 0;
      }
    }
    
    
    // Verifica si hubo algún error en la transmisión I2C
    //if (error == 0) {
    //  Serial.print("Datos enviados por I2C: ");
    //  Serial.print(receivedData);
    //  Serial.print(", ");
    //  Serial.println(receivedData1);
    //} else if (error == 2) {
    //  Serial.println("Error al enviar por I2C: NACK en la transmisión de datos.");
    //} else {
    //  Serial.print("Error al enviar por I2C. Código de error: ");
    //  Serial.println(error);
    //}
  
}

//void receiveEvent(int howMany) {
void receiveEvent() {
  int b1 = 3;
  String datos = "";
  while (Wire.available()) {
    char c = Wire.read();

    if(b1 == 3){
    if(c == '1'){
      b1 = 1;
      Serial.print("Mensaje a UART1: ");
     
    }else if(c == '2'){
      b1 = 2;
      Serial.print("Mensaje a UART2: ");
    }
    }
    else{
    Serial.print(c);
    if(b1 == 1){
      mySerial2.write(c);

    }else if(b1 == 2){
      mySerial1.write(c);
    }
    datos += c;
    }
    
    // Imprime el dato recibido en el monitor serie
    
  }
Serial.println("");
Serial.print("Dato recibido por I2C: ");
Serial.println(datos);
}

void requestEvent() {
  // En este ejemplo, no se maneja la solicitud I2C (puede dejar vacío este bloque si no se necesita)
  Wire.write(datos_UART1.c_str());
  Wire.write(datos_UART2.c_str());
  datos_UART1 = "1: ";
  datos_UART2 = " 2: ";  
}
