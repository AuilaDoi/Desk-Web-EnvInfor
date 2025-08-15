#pragma once
#include <Arduino.h>

void initTime(const char* ntpServer, long gmtOffset_sec, int daylightOffset_sec);
void updateTime();
String getTimeStr();   // HH:MM:SS
String getDateStr();   // YYYY-MM-DD
