#ifndef SLIMEVR_TFTMANAGER_H
#define SLIMEVR_TFTMANAGER_H

#include <SPI.h>
#include <TFT_eSPI.h>
#include "Fonts.h"
#include "logging/Logger.h"
#include "sensors/SensorManager.h"
#include "status/LEDManager.h"
#include "status/StatusManager.h"
#include "configuration/Configuration.h"
#include "network/manager.h"
#include "network/connection.h"
#include "network/manager.h"
#include "network/wifiprovisioning.h"
#include "./batterymonitor.h"
#include "TDBattery.h"

namespace SlimeVR {
    class TFTManager {
        public:
            void setup();
            void update();
            void setupState(boolean value);
            void drawLog(String message);
        private:
            TFT_eSPI tft = TFT_eSPI();
            //SlimeVR::Logging::Logger log = SlimeVR::Logging::Logger("TFTManager");
            SlimeVR::Logging::Logger tftLog{"TFTManager"};
            SlimeVR::Sensors::SensorManager sensorManager;
            SlimeVR::LEDManager ledManager;
            SlimeVR::Status::StatusManager statusManager;
            SlimeVR::Configuration::Configuration configuration;
            SlimeVR::Network::Manager networkManager;
            SlimeVR::Network::Connection networkConnection;
            SlimeVR::WiFiNetwork wifiNetwork;
            SlimeVR::WifiProvisioning wifiProvisioning;
            SlimeVR::TDBattery TDbattery;
            BatteryMonitor battery;

            int drawCycle = 0;
            int drawActive = 150; // ms
            int curMillis = 0;
            boolean isSetup = false;
            int drawLogPosY = 80;
            int16_t displayW = 0;
            int16_t displayH = 0;
            String serverStatus = "";
            String wifiStatus = "";

            void drawWelcome();
    };
} // namespace SlimeVR
#endif