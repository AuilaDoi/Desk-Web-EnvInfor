#pragma once
#include <WiFi.h>

void initWiFi(const char* ssid, const char* password);
IPAddress getLocalIP();
