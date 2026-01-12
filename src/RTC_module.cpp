#include "Ds1302.h"
#include "../inc/RTC_module.h"
#include "../inc/pins.h"
#include <Arduino.h>

static Ds1302 rtc(RTC_RST, RTC_CLK, RTC_DAT); // RST, DAT, CLK

void RTC_init() {
    rtc.init();
}

void RTC_setTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {
    Ds1302::DateTime dt;
    dt.year = year;
    dt.month = month;
    dt.day = day;
    dt.hour = hour;
    dt.minute = minute;
    dt.second = second;
    rtc.setDateTime(&dt);
}

void RTC_printTime() {
	Ds1302::DateTime now;
	rtc.getDateTime(&now);
    Serial.print("Year: ");
    Serial.print(now.year);
    Serial.print("Month: ");
    Serial.print(now.month);
    Serial.print("Day: ");
    Serial.print(now.day);
	Serial.print("Hour: ");
	Serial.print(now.hour);
	Serial.print(" Minute: ");
	Serial.print(now.minute);
	Serial.print(" Second: ");
	Serial.println(now.second);
}

int RTC_isMealTime(uint8_t targetHour, uint8_t targetMin) {
    Ds1302::DateTime now;
    rtc.getDateTime(&now);

    if (now.hour == targetHour && now.minute == targetMin && now.second == 0) {
        return 1;
    }
    return 0;
}
