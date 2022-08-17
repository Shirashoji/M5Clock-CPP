#include "M5Watch.h"

void Watch_BG(pos center, int r, TFT_eSprite *sprite) {
    sprite->fillCircle(center.x, center.y, r, WHITE);
    for (int i = 0; i < 12; i++) {
        int dot_r = int(r / 32);
        if (i % 3 == 0) {
            dot_r = int(r / 16);
        }
        sprite->fillCircle(int(center.x + r * 16 / 20 * sin(i * PI * 2 / 12)),
                           int(center.y + r * 16 / 20 * cos(i * PI * 2 / 12)),
                           dot_r, BLACK);
    }
}

void Watch_Needle(pos center, int r, TFT_eSprite *sprite, struct tm time_data) {
    int hour = time_data.tm_hour % 12;
    int min = time_data.tm_min % 60;
    sprite->fillTriangle(
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
    sprite->fillTriangle(
        int(center.x - r * 4 / 5.0 * sin(-min / 60.0 * PI * 2)),
        int(center.y - r * 4 / 5.0 * cos(-min / 60.0 * PI * 2)),
        int(center.x - r / 20.0 * sin(-min / 60.0 * PI * 2 + PI / 2.0)),
        int(center.y - r / 20.0 * cos(-min / 60.0 * PI * 2 + PI / 2.0)),
        int(center.x - r / 20.0 * sin(-min / 60.0 * PI * 2 - PI / 2.0)),
        int(center.y - r / 20.0 * cos(-min / 60.0 * PI * 2 - PI / 2.0)), BLACK);
    sprite->fillCircle(center.x, center.y, int(r / 14), BLACK);
}

void Watch(pos center, int r, TFT_eSprite *sprite, struct tm t) {
    Watch_BG(center, r, sprite);
    Watch_Needle(center, 70, sprite, t);
}
