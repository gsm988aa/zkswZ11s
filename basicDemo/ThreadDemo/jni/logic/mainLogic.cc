#pragma once
#include "uart/ProtocolSender.h"

#include <system/Thread.h>

static int loop_count = 0;

class MyThread: public Thread {
public:
  /**
   * 线程创建成功后会调用该函数，可以在该函数中做一些初始化操作
   * return true   继续线程
   *        false  退出线程
   */
  virtual bool readyToRun() {
    LOGD("Thread 已经创建完成");
    return true;
  }

  /**
   * 线程循环函数
   *
   * return true  继续线程循环
   *        false 推出线程
   */
  virtual bool threadLoop() {
    LOGD("线程循环函数");

    //检查是否有退出线程的请求，如果有，则返回false，立即退出线程
    if (exitPending()) {
      return false;
    }

    //累加计数，并显示到屏幕上
    loop_count += 1;
    mTextView2Ptr->setText(loop_count);

    //为了方便观察，这里添加休眠500ms
    usleep(1000 * 500);

    //返回真，继续下次线程循环
    return true;
  }
};

static MyThread my_thread;

/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	{1,  200},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){

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
	case 1:
	  if (my_thread.isRunning()) {
	    mTextView4Ptr->setText("正在运行");
	  } else {
	    mTextView4Ptr->setText("已停止");
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
static bool onmainActivityTouchEvent(const MotionEvent &ev) {
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
static bool onButtonClick_Button1(ZKButton *pButton) {
  //调用线程类的run函数启动线程， 参数为线程名，可以任意指定。
  my_thread.run("this is thread name");
  return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {
  //请求退出线程，并且等待，直到线程完全退出后，该函数才返回
  my_thread.requestExitAndWait();
  return false;
}
