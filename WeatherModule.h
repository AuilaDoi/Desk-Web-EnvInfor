// WeatherModule.h
#pragma once
#include <Arduino.h>

void initWeather(const char* apiKey, const char* location);
String getWeatherText();
