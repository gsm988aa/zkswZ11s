/*
 * DateHelper.cpp
 *
 *  Created on: 2019年2月19日
 *      Author: guoxs
 */

#include "DateHelper.h"

static int sDayTab[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool DateHelper::isLeapYear(int year) {
	return ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0));
}

int DateHelper::getDays(int year, int month) {
	if ((month == 2) && isLeapYear(year)) {	// 二月
		return 29;
	}

	return sDayTab[month - 1];
}

int DateHelper::getWeekDay(int year, int month, int day) {
	int i, temp, weekday, days = 0;
	for (i = 1; i <= month - 1; i++) {
		days += getDays(year, i);
	}
	days += day;
	temp = (year - 1) + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400 + days;
	weekday = temp % 7;

	return weekday;
}
