// WeatherModule.cpp
#include "WeatherModule.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

static String weatherText = "";
static String apiKey;
static String location;

void initWeather(const char* _apiKey, const char* _location) {
    apiKey = String(_apiKey);
    location = String(_location);
    
    // 检查参数
    if (apiKey.length() == 0 || location.length() == 0) {
        Serial.println("API密钥或位置为空");
        return;
    }
    
    // 更新天气
    String weather = getWeatherText();
    if (weather.length() > 0) {
        Serial.println("天气更新成功: " + weather);
    } else {
        Serial.println("天气更新失败");
    }
}

String getWeatherText() { 
    String url = "https://api.seniverse.com/v3/weather/now.json?key=" + apiKey +
                 "&location=" + location + "&language=zh-Hans&unit=c"; // 心知天气api

    HTTPClient http;
    http.begin(url);
    http.addHeader("Accept-Charset", "utf-8");
    int code = http.GET();
    if (code != HTTP_CODE_OK) {
        Serial.print("HTTP请求失败，错误码: ");
        Serial.println(code);
        http.end();
        return "";
    }

    String payload = http.getString();
    if (payload.length() == 0) {
        Serial.println("收到空响应");
        http.end();
        return "";
    }
    http.end();

    StaticJsonDocument<1024> doc;
    DeserializationOption::NestingLimit(10);
    
    // 解析 JSON
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
        Serial.print("JSON解析失败: ");
        Serial.println(error.c_str());
        return "";
    }

    // 检查 JSON 结构
    if (!doc.containsKey("results") || 
        doc["results"].size() == 0 || 
        !doc["results"][0].containsKey("now") || 
        !doc["results"][0]["now"].containsKey("text")) {
        Serial.println("JSON格式不正确");
        return "";
    }

    // 确保字符串以 UTF-8 编码处理
    const char* GetWeather = doc["results"][0]["now"]["text"] | "";
    const char* GetLocation = doc["results"][0]["location"]["name"] | "";
    const char* GetTemperature = doc["results"][0]["now"]["temperature"] | "";
    weatherText = String(GetLocation) + " " + String(GetWeather) + " " + String(GetTemperature) + "℃";  // 位置和天气之间加空格连接
    return weatherText; 
}
