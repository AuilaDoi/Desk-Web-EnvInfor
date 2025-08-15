#include "WiFiModule.h"

void initWiFi(const char* ssid, const char* password) {
    Serial.print("连接 WiFi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi 已连接");
    Serial.print("IP 地址: ");
    Serial.println(WiFi.localIP());
}

IPAddress getLocalIP() {
    return WiFi.localIP();
}
