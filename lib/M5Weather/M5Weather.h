#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <M5Stack.h>

#include <map>
#include <string>
#ifndef M5Weather_H
#define M5Weather_H

String getWeatherIconPath(int num);

int getWeatherCode();
#endif