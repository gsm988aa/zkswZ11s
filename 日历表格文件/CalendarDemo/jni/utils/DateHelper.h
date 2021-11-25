/*
 * DateHelper.h
 *
 *  Created on: 2019年2月19日
 *      Author: guoxs
 */

#ifndef JNI_UTILS_DATEHELPER_H_
#define JNI_UTILS_DATEHELPER_H_

class DateHelper {
public:
	// 是否是闰年
	static bool isLeapYear(int year);

	// 获取某年某月的天数
	static int getDays(int year, int month);

	// 判断某个日期是星期几的函数
	static int getWeekDay(int year, int month, int day);
};

#endif /* JNI_UTILS_DATEHELPER_H_ */
