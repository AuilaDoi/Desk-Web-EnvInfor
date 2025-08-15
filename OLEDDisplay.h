#pragma once
#include <Arduino.h>

void initOLED();
void showAllInfo(const String &weatherText, const String &timeStr, const String &dateStr,
                 float indoorTemp, float indoorHumi);
void oledOff();