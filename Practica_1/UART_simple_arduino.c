//Este programa reenvia por Tx los datos recibidos en RX

void setup() {
  Serial.begin(9600); //Establecer velocidad de comunicacion serial
}

void loop() {
  
  if (Serial.available()) { //Esperar a que la comunicacion este habilitada
      char c = Serial.read(); // Lee un carácter del puerto serial
       Serial.write(c); //Manda el caracter por el puerto serial
  }
}
