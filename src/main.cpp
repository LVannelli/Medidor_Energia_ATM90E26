#include <Arduino.h>
#include "ATM90E26.h"
#include <esp_task_wdt.h>
#define CS_PIN 5   // Pin de Chip Select del sensor
#define WDT_TIMEOUT 10  // segundos

ATM90E26 atm90e26(CS_PIN);
unsigned long lastCheck = 0;

void initWatchdog() {
    esp_task_wdt_init(WDT_TIMEOUT, true);
    esp_task_wdt_add(NULL);
}

void resetWatchdog() {
    esp_task_wdt_reset();
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Inicializando comunicación con ATM90E26...");
    if (atm90e26.begin()) {
        Serial.println("ATM90E26 inicializado correctamente.");
    } else {
        Serial.println("Fallo al inicializar el ATM90E26. Revisar conexión SPI.");
    }

    initWatchdog();
}

void loop() {
    resetWatchdog();

    if (millis() - lastCheck > 2000) {
        lastCheck = millis();
        atm90e26.checkConnection();

        float voltage = atm90e26.readVoltage();
        float current = atm90e26.readCurrent();

        Serial.print("Tensión: ");
        Serial.print(voltage);
        Serial.print(" V | Corriente: ");
        Serial.print(current);
        Serial.println(" A");
    }
}
