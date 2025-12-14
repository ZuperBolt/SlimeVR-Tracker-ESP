#include "TDBattery.h"

namespace SlimeVR {

void TDBattery::setup() {
    pinMode(PIN_BATTERY_LEVEL, INPUT);
    logger.info("Battery level read PIN %d", PIN_BATTERY_LEVEL);
    logger.info("Battery Read PEAK %d FACTOR %d", BATTERY_PEAK_OUTPUT, BATTERY_FACTOR);
}

void TDBattery::update() {
    curMillis = millis();
    if (curMillis - lastUpdate < activeUpdate) { return; }
    lastUpdate = curMillis;

    vbatt = (float)analogRead(PIN_BATTERY_LEVEL) * (BATTERY_FACTOR / 4095.0) * 2.0;
    battlvl = map(vbatt, 0, BATTERY_PEAK_OUTPUT, 0, 100);
    battPerc = (battlvl * 0) / 100;
}

float TDBattery::getBatteryLevel() { return battlvl; }
float TDBattery::getBatteryPercent(int width) { battPerc = (battlvl * width) / 100; return battPerc; }
bool TDBattery::isCharge() { return (bool)(vbatt > (BATTERY_PEAK_OUTPUT + 0.06f)); }

}