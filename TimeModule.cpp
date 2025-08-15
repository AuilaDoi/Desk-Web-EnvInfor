#include "TimeModule.h"
#include <WiFi.h>
#include <time.h>

static String currentTime = "";
static String currentDate = "";

void initTime(const char* ntpServer, long gmtOffset_sec, int daylightOffset_sec) {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    Serial.println("正在从 NTP 获取时间...");
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("获取时间失败");
        return;
    }
    Serial.println("时间同步完成");
}

void updateTime() {
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
        char timeStr[9];  // HH:MM:SS
        strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);
        currentTime = timeStr;

        char dateStr[11]; // YYYY-MM-DD
        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &timeinfo);
        currentDate = dateStr;
    }
}

String getTimeStr() {
    return currentTime;
}

String getDateStr() {
    return currentDate;
}
