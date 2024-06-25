#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <LiquidCrystal_I2C.h>

Adafruit_AHTX0 aht;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Dirección I2C de la LCD 0x27, 16 columnas y 2 filas
#define SLAVE_ADDRESS 8 // Dirección del esclavo

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  // Inicialización del sensor AHT20
  if (!aht.begin()) {
    Serial.println("No se encontró el sensor AHT20");
    while (1); // Bucle infinito si no se encuentra el sensor
  }

  // Inicialización de la LCD
  lcd.init();
  lcd.backlight();

  // Mensaje inicial en la LCD
  lcd.setCursor(0, 0);
  lcd.print("Temperatura: ");

  // Iniciar comunicación I2C con la LCD
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write("hola");
  Wire.endTransmission();
}

void loop() {
  // Leer datos del sensor AHT20
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  float temperatureC = temp.temperature;
  
  // Mostrar datos del AHT20 en la LCD
  lcd.setCursor(13, 0);
  lcd.print(temperatureC, 1);  // Imprimir temperatura con un decimal
  
  // Solicitar datos al esclavo
  Wire.requestFrom(SLAVE_ADDRESS, 10); // Solicitar 10 bytes al esclavo
  
  // Leer y mostrar datos recibidos del esclavo en la LCD
  if (Wire.available() > 0) {
    lcd.setCursor(0, 1);
    while (Wire.available() > 0) {
      char c = Wire.read();
      lcd.print(c);
    }
  }

  delay(2000); // Esperar 2 segundos antes de la siguiente lectura
}
