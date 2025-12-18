#include "TFTManager.h"
#include "logging/Logger.h"

namespace SlimeVR {

void TFTManager::drawWelcome() {
    return; //disabled for now
    tft.fillScreen(TFT_BLACK);
    tft.drawString("v." FIRMWARE_VERSION, 0, 0, 1);
    tft.setTextSize(4.0f);
    tft.setTextColor(TFT_PINK);
	tft.setFreeFont(FF26);
    //tft.drawString("WG", 30, 10);
	tft.drawCentreString("WG", displayW / 2, 6, 1);
    tft.setTextSize(2.0f);
	tft.setFreeFont(FSBI12);
    tft.setTextColor(TFT_PURPLE);
    tft.drawCentreString("SlimeVR", displayW / 2, 93, 1);
}
void TFTManager::setup() {
    return; //disabled for now
    tft.init();
    tftLog.info("TFT setup detail PIN CS %d , SCLK %d, MOSI %d, MISO %d , RST %d", TFT_CS, TFT_SCLK, TFT_MOSI, TFT_MISO, TFT_RST);
    tft.setRotation(1);
    displayW = tft.width(); displayH = tft.height();
    tftLog.info("TFT Display %d x %d", displayW, displayH);

    drawWelcome();
}

void TFTManager::update() {
    return; //disabled for now
    curMillis = millis();
    if(drawCycle < drawActive) { drawCycle++; return; }
    drawCycle = 0; //RESET cycle

    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(7);
    tft.setTextColor(TFT_PINK);
    tft.drawString("WG", 15, 5, 1);
    tft.setTextSize(2.5);
    tft.setTextColor(TFT_PURPLE);
    tft.drawString("SlimeVR", 10, 55, 2);

	//connection status
	tft.setTextSize(1);
	switch (wifiNetwork.getWiFiState())
	{
        case SlimeVR::WiFiNetwork::WiFiReconnectionStatus::Success:
            wifiStatus = "Connected";
            tft.fillCircle(120, 70, 6, TFT_GREEN);
            break;
        case SlimeVR::WiFiNetwork::WiFiReconnectionStatus::ServerCredAttempt:
            wifiStatus = "Connecting";
            tft.fillCircle(120, 70, 6, TFT_YELLOW);
            break;
        case SlimeVR::WiFiNetwork::WiFiReconnectionStatus::Failed:
            wifiStatus = "Failed";
            tft.fillCircle(120, 70, 6, TFT_ORANGE);
            break;
        default:
            wifiStatus = "Not Connected";
            tft.fillCircle(120, 70, 6, TFT_RED);
            break;
	}
	serverStatus = networkConnection.isConnected()?"Connected":"Not Connected";
    tft.drawString("WiFi : " + wifiStatus, 5, 85, 2);
    tft.drawString("Server : " + serverStatus, 5, 100, 2);
    tft.drawRightString("72 ms", 235, 105, 2);

    //Battery Level display
    tft.drawRoundRect(0, 120, 240, 8, 5, TFT_GREEN);
    tft.fillRoundRect(1, 121, TDbattery.getBatteryPercent(239), 8, 5, TFT_GREEN);
    if(TDbattery.isCharge()) {
        tft.setTextSize(1);
        tft.setTextColor(TFT_BLUE);
        tft.drawCentreString(">>> CHARGING >>>", displayW / 2, 121, 1);
    }
}

void TFTManager::setupState(boolean value) { isSetup = value; }

void TFTManager::drawLog(String message) {// available for setup screen only
    if(!isSetup) return;

	tft.setTextSize(1.0f);
	tft.setTextColor(TFT_WHITE);
	tft.fillRect(0, drawLogPosY, displayW, 16, TFT_BLACK);
	tft.drawCentreString(String(message), displayW / 2, drawLogPosY, 2);
}

}