#include "ATM90E26.h"

ATM90E26::ATM90E26(uint8_t csPin) {
    _csPin = csPin;
}

bool ATM90E26::begin() {
    SPI.begin();
    pinMode(_csPin, OUTPUT);
    digitalWrite(_csPin, HIGH);

    delay(100);

    // Intento simple de comunicación
    uint16_t sysStatus = readRegister(0x01);
    if (sysStatus == 0xFFFF || sysStatus == 0x0000) {
        return false; // No hay respuesta válida
    }
    return true;
}

uint16_t ATM90E26::readRegister(uint16_t address) {
    uint16_t result = 0;
    uint8_t hi, lo;

    digitalWrite(_csPin, LOW);
    delayMicroseconds(10);

    SPI.transfer16(0x8000 | address);
    hi = SPI.transfer(0x00);
    lo = SPI.transfer(0x00);

    digitalWrite(_csPin, HIGH);
    result = (hi << 8) | lo;
    return result;
}

void ATM90E26::writeRegister(uint16_t address, uint16_t value) {
    digitalWrite(_csPin, LOW);
    SPI.transfer16(address & 0x7FFF);
    SPI.transfer16(value);
    digitalWrite(_csPin, HIGH);
}

float ATM90E26::readVoltage() {
    uint16_t raw = readRegister(0x24);
    return raw * 0.01;  // Valor de ejemplo
}

float ATM90E26::readCurrent() {
    uint16_t raw = readRegister(0x28);
    return raw * 0.001; // Valor de ejemplo
}

void ATM90E26::checkConnection() {
    uint16_t sysStatus = readRegister(0x01);
    if (sysStatus == 0xFFFF || sysStatus == 0x0000) {
        Serial.println("Error: comunicación perdida con ATM90E26");
    }
}
