#include "OLEDDisplay.h"
#include <U8g2lib.h>
#include <Wire.h>

// 创建U8g2对象，I2C接口，0x3C为默认SSD1315地址
U8G2_SSD1315_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 23, /* data=*/ 22);

void initOLED() {
    Wire.begin();  // 初始化I2C
    if (!u8g2.begin()) {
        Serial.println("OLED 初始化失败！");
        return;
    }
    u8g2.enableUTF8Print();  // 启用UTF8支持
    u8g2.setFont(u8g2_font_wqy12_t_gb2312);  // 使用更兼容的中文字体
    u8g2.setFontMode(1);  // 启用透明模式
    u8g2.setDrawColor(1);
    u8g2.setFontDirection(0);
    
    // 测试显示
    u8g2.clearBuffer();
    u8g2.setCursor(0, 15);
    u8g2.print("OLED测试");
    u8g2.sendBuffer();
    Serial.println("OLED 初始化成功！");
}

void showAllInfo(const String &weatherText, const String &timeStr, const String &dateStr,
                 float indoorTemp, float indoorHumi) {
    u8g2.setPowerSave(0);
    u8g2.clearBuffer();

    // 天气
    u8g2.setCursor(0, 14);
    if (weatherText.length() > 0) {
        u8g2.print(weatherText);
    } else {
        u8g2.print("等待天气...");
    }

    // 时间
    u8g2.setCursor(0, 28);
    u8g2.print(timeStr);
    
    // 日期
    u8g2.setCursor(0, 44);
    u8g2.print(dateStr);

    // 室内温度
    u8g2.setCursor(0, 60);
    u8g2.print("室内温:");
    u8g2.print(indoorTemp, 1);
    u8g2.print("℃");

    // 室内湿度
    u8g2.setCursor(80, 60);
    u8g2.print("湿:");
    u8g2.print(indoorHumi, 1);
    u8g2.print("%");

    u8g2.sendBuffer();
}

void oledOff() {
    u8g2.setPowerSave(1);
}
