#include <M5Stack.h>
#include <time.h>

#include "POS.h"
#ifndef M5Watch_H
#define M5Watch_H

void Watch_BG(pos center, int r, TFT_eSprite *sprite);
void Watch_Needle(pos center, int r, TFT_eSprite *sprite, struct tm time_data);
void Watch(pos center, int r, TFT_eSprite *sprite, struct tm t);

#endif