#ifndef ATM90E26_H
#define ATM90E26_H

#include <Arduino.h>
#include <SPI.h>

class ATM90E26 {
public:
    ATM90E26(uint8_t csPin);
    bool begin();
    float readVoltage();
    float readCurrent();
    void checkConnection();

private:
    uint8_t _csPin;
    uint16_t readRegister(uint16_t address);
    void writeRegister(uint16_t address, uint16_t value);
};

#endif
