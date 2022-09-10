#include "M5Weather.h"

String getWeatherIconPath(int num) {
    std::map<int, String> weather_icon_dic = {
        {100, "100.jpg"}, {123, "100.jpg"}, {124, "100.jpg"}, {130, "100.jpg"},
        {131, "100.jpg"}, {101, "101.jpg"}, {132, "101.jpg"}, {102, "102.jpg"},
        {103, "102.jpg"}, {106, "102.jpg"}, {107, "102.jpg"}, {108, "102.jpg"},
        {120, "102.jpg"}, {121, "102.jpg"}, {140, "102.jpg"}, {104, "104.jpg"},
        {105, "104.jpg"}, {160, "104.jpg"}, {170, "104.jpg"}, {110, "110.jpg"},
        {111, "110.jpg"}, {112, "112.jpg"}, {113, "112.jpg"}, {114, "112.jpg"},
        {118, "112.jpg"}, {119, "112.jpg"}, {122, "112.jpg"}, {125, "112.jpg"},
        {126, "112.jpg"}, {127, "112.jpg"}, {128, "112.jpg"}, {115, "115.jpg"},
        {116, "115.jpg"}, {117, "115.jpg"}, {181, "115.jpg"}, {200, "200.jpg"},
        {209, "200.jpg"}, {231, "200.jpg"}, {201, "201.jpg"}, {223, "201.jpg"},
        {202, "202.jpg"}, {203, "202.jpg"}, {206, "202.jpg"}, {207, "202.jpg"},
        {208, "202.jpg"}, {220, "202.jpg"}, {221, "202.jpg"}, {240, "202.jpg"},
        {204, "204.jpg"}, {205, "204.jpg"}, {250, "204.jpg"}, {260, "204.jpg"},
        {270, "204.jpg"}, {210, "210.jpg"}, {211, "210.jpg"}, {212, "212.jpg"},
        {213, "212.jpg"}, {214, "212.jpg"}, {218, "212.jpg"}, {219, "212.jpg"},
        {222, "212.jpg"}, {224, "212.jpg"}, {225, "212.jpg"}, {226, "212.jpg"},
        {215, "215.jpg"}, {216, "215.jpg"}, {217, "215.jpg"}, {228, "215.jpg"},
        {229, "215.jpg"}, {230, "215.jpg"}, {281, "215.jpg"}, {300, "300.jpg"},
        {304, "300.jpg"}, {306, "300.jpg"}, {328, "300.jpg"}, {329, "300.jpg"},
        {350, "300.jpg"}, {301, "301.jpg"}, {302, "302.jpg"}, {303, "303.jpg"},
        {309, "303.jpg"}, {322, "303.jpg"}, {308, "308.jpg"}, {311, "311.jpg"},
        {316, "311.jpg"}, {320, "311.jpg"}, {323, "311.jpg"}, {324, "311.jpg"},
        {325, "311.jpg"}, {313, "313.jpg"}, {317, "313.jpg"}, {321, "313.jpg"},
        {314, "314.jpg"}, {315, "314.jpg"}, {326, "314.jpg"}, {327, "314.jpg"},
        {340, "400.jpg"}, {400, "400.jpg"}, {405, "400.jpg"}, {425, "400.jpg"},
        {426, "400.jpg"}, {427, "400.jpg"}, {450, "400.jpg"}, {401, "401.jpg"},
        {402, "402.jpg"}, {403, "403.jpg"}, {409, "403.jpg"}, {406, "406.jpg"},
        {407, "406.jpg"}, {361, "411.jpg"}, {411, "411.jpg"}, {420, "411.jpg"},
        {371, "413.jpg"}, {413, "413.jpg"}, {421, "413.jpg"}, {414, "414.jpg"},
        {422, "414.jpg"}, {423, "414.jpg"}};
    return "/img/" + weather_icon_dic[num];
}

int getWeatherCode() {
    HTTPClient http;
    String payload;
    http.begin(
        "https://www.jma.go.jp/bosai/forecast/data/forecast/130000.json");
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        payload = http.getString();
    }
    DynamicJsonDocument djd(4096);
    deserializeJson(djd, payload);
    return int(djd[0]["timeSeries"][0]["areas"][0]["weatherCodes"][0]);
}

int getRainyPercent() {
    HTTPClient http;
    String payload;
    http.begin(
        "https://www.jma.go.jp/bosai/forecast/data/forecast/130000.json");
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        payload = http.getString();
    }
    DynamicJsonDocument djd(4096);
    deserializeJson(djd, payload);
    return int(djd[0]["timeSeries"][0]["areas"][0]["pops"][0]);
}

