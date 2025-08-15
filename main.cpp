#include <Arduino.h>
#include "WiFiModule.h"
#include "TimeModule.h"
#include "DHTModule.h"
#include "WeatherModule.h"
#include "OLEDDisplay.h"
#include <Wire.h>

#define DHTPin 4 // DHT传感器引脚
#define LightDetectPin 16 // 光敏传感器引脚
#define I2C_SDA 22 // I2C SDA引脚
#define I2C_SCL 23 // I2C SCL引脚

// WiFi 配置
const char* ssid = "your wifi ssid";
const char* password = "your wifi password";

// 天气 API 配置
const char* weatherApiKey = "心知天气apikey";
const char* weatherLocation = "ip";

unsigned long lastWeatherUpdate = 0;
unsigned long lastDHTUpdate = 0;
unsigned long lastTimeUpdate = 0;

// NTP 服务器和时区（中国东八区 GMT+8）
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 8 * 3600;
const int daylightOffset_sec = 0;

float indoorTemp = 0.0;
float indoorHumi = 0.0;
String weatherText = "";
String currentTimeStr = "";
String currentDateStr = "";

void setup() {
    Serial.begin(115200);
    Wire.begin(I2C_SDA, I2C_SCL);  // 初始化I2C，GPIO22为SDA，GPIO23为SCL
    pinMode(LightDetectPin, INPUT);
    initWiFi(ssid, password);
    initTime(ntpServer, gmtOffset_sec, daylightOffset_sec); // 你的NTP初始化
    initDHT(DHTPin);
    initWeather(weatherApiKey, weatherLocation);
    initOLED();
}

void loop() {
    unsigned long now = millis();

    // 每分钟更新温湿度
    if (lastDHTUpdate == 0 || now - lastDHTUpdate > 60 * 1000) {
        lastDHTUpdate = now;
        indoorTemp = readTemperature();
        indoorHumi = readHumidity();
    }

    // 每秒更新时间
    if (lastTimeUpdate == 0 || millis() - lastTimeUpdate > 1000) {
        updateTime();
        currentTimeStr = getTimeStr(); // 获取当前时间字符串
        String newDateStr = getDateStr();
        if (newDateStr != currentDateStr) {
            currentDateStr = newDateStr; // 获取当前日期字符串
        }
        lastTimeUpdate = millis();
    }

    // 每15分钟更新天气，或在第一次运行时更新
    if (lastWeatherUpdate == 0 || now - lastWeatherUpdate > 15 * 60 * 1000) {
        lastWeatherUpdate = now;
        weatherText = getWeatherText();
    }

    if (digitalRead(LightDetectPin) == LOW) {
        // OLED 刷新
        showAllInfo(weatherText, currentTimeStr, currentDateStr,indoorTemp, indoorHumi);
    } else {
        oledOff(); // 关闭OLED显示
    }
}
