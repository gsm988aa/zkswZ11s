#pragma once
#include "uart/ProtocolSender.h"

#include "utils/TimeHelper.h"      //时钟源，可替换
#include "time.h"
#include <string>
using namespace std;

namespace
{

static struct tm St;
//TimeHelper T;					   //时钟源，可替换

static float sec_angle;
static float min_angle;
static float hour_angle;

const char* isweek[] = {"日","一","二","三","四","五","六"};

//获取时间   如 9：30  或  21：30
//int h = 16;
//int m = 05;
//int s = 0;

// 时钟角度初始化
static void clock_Init(int hour = 0, int min = 0, int sec = 0)
{
	if(hour >= 12) {
		hour -= 12;
	}

	sec_angle = sec * 6.0;
	min_angle = min * 6.0 + sec_angle/60;
	hour_angle = hour * 30.0 + min_angle/12;
}

}

/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	{0,  1000}, //定时器id=0, 时间间隔1秒  // 时钟运行定时器
	//{1,  1000},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
	St = *(TimeHelper::getDateTime());  	 //时钟源，可替换
	clock_Init(St.tm_hour, St.tm_min, St.tm_sec);
	char dateBuf[30] = {0};
	snprintf(dateBuf, TABLESIZE(dateBuf), "%d年%d月%d日",St.tm_year + 1900, St.tm_mon + 1, St.tm_mday);
	mTextviewDatePtr->setText(dateBuf);

	string weekBuf = "星期";
	//weekBuf.append(isweek(St.tm_wday));
	weekBuf.append(isweek[St.tm_wday%7]);

	mTextviewWeekPtr->setText(weekBuf);

}

/**
 * 当切换到该界面时触发
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
}

/*
 * 当界面显示时触发
 */
static void onUI_show() {

}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {

}

/*
 * 当界面完全退出时触发
 */
static void onUI_quit() {

}

/**
 * 串口数据回调接口
 */
static void onProtocolDataUpdate(const SProtocolData &data) {

}

/**
 * 定时器触发函数
 * 不建议在此函数中写耗时操作，否则将影响UI刷新
 * 参数： id
 *         当前所触发定时器的id，与注册时的id相同
 * 返回值: true
 *             继续运行当前定时器
 *         false
 *             停止运行当前定时器
 */
static bool onUI_Timer(int id){
	switch (id) {
	case 0:
		sec_angle += 6.0;      //秒针 每秒跳6度
	    mPointer_SecPtr->setTargetAngle(sec_angle);
	    static int count;
	    	count++;
	    	if (12 == count) {			 // 每过12秒，时针达到最小跳动度数
	    		hour_angle += 6.0/60;
	    		count = 0;
	    	}

			if (360 == sec_angle) {
				sec_angle = 0;
			}

	    min_angle += 6.0/60;			// 每过一秒钟，分针达到最小跳动度数
	    mPointer_MinuePtr->setTargetAngle(min_angle);
	    if (360 == min_angle) {
	    	min_angle = 0;
	    }

	    mPointer_HourPtr->setTargetAngle(hour_angle);
	    if (360 == hour_angle) {
	    	hour_angle = 0;
	    }

		break;
		default:
			break;
	}
    return true;
}

/**
 * 有新的触摸事件时触发
 * 参数：ev
 *         新的触摸事件
 * 返回值：true
 *            表示该触摸事件在此被拦截，系统不再将此触摸事件传递到控件上
 *         false
 *            触摸事件将继续传递到控件上
 */
static bool onclockwindowActivityTouchEvent(const MotionEvent &ev) {
    switch (ev.mActionStatus) {
		case MotionEvent::E_ACTION_DOWN://触摸按下
			//LOGD("时刻 = %ld 坐标  x = %d, y = %d", ev.mEventTime, ev.mX, ev.mY);
			break;
		case MotionEvent::E_ACTION_MOVE://触摸滑动
			break;
		case MotionEvent::E_ACTION_UP:  //触摸抬起
			break;
		default:
			break;
	}
	return false;
}
