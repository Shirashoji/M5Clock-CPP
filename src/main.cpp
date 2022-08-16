#include <M5Stack.h>
#include <WiFi.h>
#include <math.h>
#include <time.h>

#include <string>
#include <vector>

using std::string;
using std::vector;

#define SSID "******"
#define PASS "******"

#define TZ 3600 * 9

TFT_eSprite sprite = TFT_eSprite(&M5.Lcd);

typedef struct date_struct {
    int year, month, day;
} date;

typedef struct position_struct {
    int x, y;
} pos;

String getRankSuffix(int rank) {
    if (rank % 10 == 1 and rank != 11) {
        return "st";
    } else if (rank % 10 == 2 and rank != 12) {
        return "nd";
    } else if (rank % 10 == 3 and rank != 13) {
        return "rd";
    } else {
        return "th";
    }
}

String getMonth(int m) {
    String month[] = {"January",   "February", "March",    "April",
                      "May",       "June",     "July",     "August",
                      "September", "October",  "November", "December"};
    return month[m - 1];
}

void printDate(struct tm t) {
    sprite.drawString(String(t.tm_mday) + getRankSuffix(t.tm_mday) + " " +
                          getMonth(t.tm_mon + 1),
                      88, 36);
}

void loading(pos center, int r) {
    M5.Lcd.fillCircle(center.x, center.y, r, 0XFFFFFF);
    for (int i = 0; i < 10; i++) {
        int dot_r = int(r / 16);
        delay(50);
        M5.Lcd.fillCircle(int(center.x + r * 2 / 3 * sin(i * PI * 2 / 10 + PI)),
                          int(center.y + r * 2 / 3 * cos(i * PI * 2 / 10 + PI)),
                          dot_r, 0X000000);
    }
}

void Watch_BG(pos center) {
    int r = 70;
    sprite.fillCircle(center.x, center.y, r, WHITE);
    for (int i = 0; i < 12; i++) {
        int dot_r = int(r / 32);
        if (i % 3 == 0) {
            dot_r = int(r / 16);
        }
        sprite.fillCircle(int(center.x + r * 16 / 20 * sin(i * PI * 2 / 12)),
                          int(center.y + r * 16 / 20 * cos(i * PI * 2 / 12)),
                          dot_r, BLACK);
    }
}

void Watch_Needle(pos center, int r, struct tm time_data) {
    int hour = time_data.tm_hour % 12;
    int min = time_data.tm_min % 60;
    sprite.fillTriangle(
        (int)(center.x -
              r / 2.0 * sin(-(hour % 12 + min / 60.0) / 12.0 * PI * 2)),
        (int)(center.y -
              r / 2.0 * cos(-(hour % 12 + min / 60.0) / 12.0 * PI * 2)),
        (int)(center.x -
              r / 20.0 *
                  sin(-(hour % 12 + min / 60.0) / 12.0 * PI * 2 + PI / 2.0)),
        (int)(center.y -
              r / 20.0 *
                  cos(-(hour % 12 + min / 60.0) / 12.0 * PI * 2 + PI / 2.0)),
        (int)(center.x -
              r / 20.0 *
                  sin(-(hour % 12 + min / 60.0) / 12.0 * PI * 2 - PI / 2.0)),
        (int)(center.y -
              r / 20.0 *
                  cos(-(hour % 12 + min / 60.0) / 12.0 * PI * 2 - PI / 2.0)),
        BLACK);
    sprite.fillTriangle(
        int(center.x - r * 4 / 5.0 * sin(-min / 60.0 * PI * 2)),
        int(center.y - r * 4 / 5.0 * cos(-min / 60.0 * PI * 2)),
        int(center.x - r / 20.0 * sin(-min / 60.0 * PI * 2 + PI / 2.0)),
        int(center.y - r / 20.0 * cos(-min / 60.0 * PI * 2 + PI / 2.0)),
        int(center.x - r / 20.0 * sin(-min / 60.0 * PI * 2 - PI / 2.0)),
        int(center.y - r / 20.0 * cos(-min / 60.0 * PI * 2 - PI / 2.0)), BLACK);
    sprite.fillCircle(center.x, center.y, int(r / 14), BLACK);
}

void Watch(struct tm t) {
    pos center = {245, 165};
    Watch_BG(center);
    Watch_Needle(center, 70, t);
}

int old_min = -1;
void setup() {
    // put your setup code here, to run once:
    M5.begin();
    M5.Lcd.setTextDatum(MC_DATUM);
    WiFi.begin(SSID, PASS);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.drawString("Connecting to NetWork", 160, 43);
    pos center = {160, 150};
    configTime(TZ, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");
    while (WiFi.status() != WL_CONNECTED) {
        loading(center, 60);
    }
    M5.Lcd.fillScreen(BLACK);
    sprite.setColorDepth(8);
    sprite.setTextSize(3);
    sprite.setTextDatum(MC_DATUM);
    sprite.createSprite(M5.Lcd.width(), M5.Lcd.height());
}

void loop() {
    // put your main code here, to run repeatedly:
    struct tm nowTime;
    getLocalTime(&nowTime);
    if (old_min != nowTime.tm_min) {
        sprite.fillScreen(BLACK);
        printDate(nowTime);
        Watch(nowTime);
        sprite.pushSprite(0, 0);
        old_min = nowTime.tm_min;
    }
}
