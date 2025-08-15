#include "DHTModule.h"
#include <DHT.h>

static DHT* dhtSensor = nullptr;

void initDHT(int pin) {
    static DHT dht(pin, DHT11);
    dht.begin();
    dhtSensor = &dht;
}

float readTemperature() {
    if (dhtSensor) return dhtSensor->readTemperature();
    return NAN;
}

float readHumidity() {
    if (dhtSensor) return dhtSensor->readHumidity();
    return NAN;
}
