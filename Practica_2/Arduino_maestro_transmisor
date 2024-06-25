#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_AHTX0.h>

// Define dirección I2C del LCD y msp
#define LCD_ADDRESS 0x27
#define SLAVE_ADDRESS 0x48

// Crear instancia para el LCD
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

// Crear instancia para el sensor AHT20
Adafruit_AHTX0 aht;

void setup() {
  Wire.begin(); // Inicializar I2C como maestro
  lcd.init();//inicializa la pantalla
  lcd.backlight();//Enciende la luz de fondo
  lcd.backlight(); // Encender retroiluminación

  // Inicializar el sensor AHT20
  if (!aht.begin()) {
    lcd.print("Error AHT20");
    while (1) delay(10);
  }
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// Obtener datos del sensor

  // Mostrar datos en el LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp.temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity.relative_humidity);
  lcd.print(" %");

  // Enviar carácter 'A' al esclavo
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write('a');
  Wire.endTransmission();

  delay(2000); // Esperar 2 segundos antes de repetir
}
