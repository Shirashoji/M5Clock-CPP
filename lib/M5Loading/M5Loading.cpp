#include "M5Loading.h"

void M5Loading(pos center, int r) {
    M5.Lcd.fillCircle(center.x, center.y, r, 0XFFFFFF);
    for (int i = 0; i < 10; i++) {
        int dot_r = int(r / 16);
        delay(50);
        M5.Lcd.fillCircle(int(center.x + r * 2 / 3 * sin(i * PI * 2 / 10 + PI)),
                          int(center.y + r * 2 / 3 * cos(i * PI * 2 / 10 + PI)),
                          dot_r, 0X000000);
    }
}
