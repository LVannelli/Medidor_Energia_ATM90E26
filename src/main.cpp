#include <Arduino.h>
#include <SPI.h>

const int PIN_CS   = 5;
const int PIN_SCK  = 18;
const int PIN_MISO = 19;
const int PIN_MOSI = 23;

SPISettings spiSettings(500000, MSBFIRST, SPI_MODE0);

void setup() {
  Serial.begin(115200);
  delay(200);

  pinMode(PIN_CS, OUTPUT);
  digitalWrite(PIN_CS, HIGH);

  SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_CS);
  Serial.println();
  Serial.println("=== Prueba SPI ESP32 ===");
  Serial.println("Inicialización completa");
}

void loop() {
  SPI.beginTransaction(spiSettings);
  digitalWrite(PIN_CS, LOW);

  // lectura genérica (dos bytes)
  uint8_t msb = SPI.transfer(0x00);
  uint8_t lsb = SPI.transfer(0x00);

  digitalWrite(PIN_CS, HIGH);
  SPI.endTransaction();

  uint16_t val = ((uint16_t)msb << 8) | lsb;
  Serial.print("Lectura SPI: 0x");
  if (val < 0x1000) Serial.print("0");
  Serial.println(val, HEX);

  delay(1000);
}
