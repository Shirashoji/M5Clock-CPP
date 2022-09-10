#include <M5Stack.h>
#include <WiFi.h>
#include <math.h>
#include <time.h>

#include <string>
#include <vector>

#include "M5Calendar.h"
#include "M5Loading.h"
#include "M5Watch.h"
#include "M5Weather.h"
#include "POS.h"

using std::string;
using std::vector;

#define SSID "******"
#define PASS "******"

#define TZ 3600 * 9

TFT_eSprite sprite = TFT_eSprite(&M5.Lcd);
HTTPClient http;
String payload;

void printDate(struct tm t);
void drawWatch(struct tm t);

void displayHome();
void displayWeather();

int old_min = -1;
int WeatherCode;

void setup() {
    // put your setup code here, to run once:
    M5.begin();
    M5.Lcd.setTextDatum(MC_DATUM);
    WiFi.begin(SSID, PASS);
    WiFi.setAutoReconnect(true);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.drawString("Connecting to NetWork", 160, 43);
    pos center = {160, 150};
    while (WiFi.status() != WL_CONNECTED) {
        M5Loading(center, 60);
    }
    configTime(TZ, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");
    M5.Lcd.fillScreen(BLACK);
    sprite.setColorDepth(8);
    sprite.setTextSize(3);
    sprite.setTextDatum(MC_DATUM);
    sprite.createSprite(M5.Lcd.width(), M5.Lcd.height());
    WeatherCode = getWeatherCode();
}

enum SCENE { MENU, WEATHER, TIME };
SCENE scene = MENU;

void loop() {
    switch (scene) {
        case MENU:
            displayHome();
            break;

        default:
            displayHome();
            break;
    }
}

void printDate(struct tm t) {
    sprite.drawString(String(t.tm_mday) + getRankSuffix(t.tm_mday) + " " +
                          getMonth(t.tm_mon + 1),
                      88, 36);
}

void drawWatch(struct tm t) {
    pos center = {245, 165};
    int r = 70;
    Watch(center, r, &sprite, t);
}

void displayHome() {
    // put your main code here, to run repeatedly:
    struct tm nowTime;
    getLocalTime(&nowTime);
    if (old_min != nowTime.tm_min) {
        sprite.fillScreen(BLACK);
        printDate(nowTime);
        drawWatch(nowTime);
        sprite.pushSprite(0, 0);

        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            payload = http.getString();
        }
        if (nowTime.tm_min % 10 == 0) {
            WeatherCode = getWeatherCode();
        }
        String dir = getWeatherIconPath(WeatherCode);
        M5.Lcd.drawJpgFile(SD, dir.c_str(), 7, 105);
        old_min = nowTime.tm_min;
    }
}

void displayWeather() {
    struct tm nowTime;
    getLocalTime(&nowTime);
    if (old_min != nowTime.tm_min) {
        sprite.fillScreen(BLACK);
        printDate(nowTime);
        drawWatch(nowTime);
        sprite.pushSprite(0, 0);

        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            payload = http.getString();
        }
        if (nowTime.tm_min % 10 == 0) {
            WeatherCode = getWeatherCode();
        }
        String dir = getWeatherIconPath(WeatherCode);
        M5.Lcd.drawJpgFile(SD, dir.c_str(), 7, 105);
        old_min = nowTime.tm_min;
    }
}