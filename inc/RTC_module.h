#ifndef RTC_MODULE_H
#define RTC_MODULE_H

#include <stdint.h>

void RTC_init();
void RTC_printTime();
void RTC_printBTTime();
int RTC_isMealTime(uint8_t targetHour, uint8_t targetMin);
void RTC_setTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);

#endif // RTC_MODULE_H
