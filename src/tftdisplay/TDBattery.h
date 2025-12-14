#ifndef SLIMEVR_TFTMANAGER_TDBattery_H
#define SLIMEVR_TFTMANAGER_TDBattery_H

#include "logging/Logger.h"
#define BATTERY_PEAK_OUTPUT 3.80
#define BATTERY_FACTOR 3.44

namespace SlimeVR {
    class TDBattery {
        public:
            void setup();
            void update();
            float getBatteryLevel();
            float getBatteryPercent(int width);
            bool isCharge();
        private:
            SlimeVR::Logging::Logger logger{"TDBattery"};

            unsigned long lastUpdate = 0;
            unsigned long curMillis = 0;
            int activeUpdate = 200;
            float battlvl = 0.0f;
            float vbatt = 0.0f;
            float battPerc = 0.0f;

            int BatteryFactor = 0;
            int BatteryPeakOutput = 0;
    };
}

#endif