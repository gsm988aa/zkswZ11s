#pragma once
/*
*此文件由GUI工具生成
*文件功能：用于处理用户的逻辑相应代码
*功能说明：
*========================onButtonClick_XXXX
当页面中的按键按下后系统会调用对应的函数，XXX代表GUI工具里面的[ID值]名称，
如Button1,当返回值为false的时候系统将不再处理这个按键，返回true的时候系统将会继续处理此按键。比如SYS_BACK.
*========================onSlideWindowItemClick_XXXX(int index) 
当页面中存在滑动窗口并且用户点击了滑动窗口的图标后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称，
如slideWindow1;index 代表按下图标的偏移值
*========================onSeekBarChange_XXXX(int progress) 
当页面中存在滑动条并且用户改变了进度后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称，
如SeekBar1;progress 代表当前的进度值
*========================ogetListItemCount_XXXX() 
当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表的总数目,XXX代表GUI工具里面的[ID值]名称，
如List1;返回值为当前列表的总条数
*========================oobtainListItemData_XXXX(ZKListView::ZKListItem *pListItem, int index)
 当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表当前条目下的内容信息,XXX代表GUI工具里面的[ID值]名称，
如List1;pListItem 是贴图中的单条目对象，index是列表总目的偏移量。具体见函数说明
*========================常用接口===============
*LOGD(...)  打印调试信息的接口
*mTextXXXPtr->setText("****") 在控件TextXXX上显示文字****
*mButton1Ptr->setSelected(true); 将控件mButton1设置为选中模式，图片会切换成选中图片，按钮文字会切换为选中后的颜色
*mSeekBarPtr->setProgress(12) 在控件mSeekBar上将进度调整到12
*mListView1Ptr->refreshListView() 让mListView1 重新刷新，当列表数据变化后调用
*mDashbroadView1Ptr->setTargetAngle(120) 在控件mDashbroadView1上指针显示角度调整到120度
*
* 在Eclipse编辑器中  使用 “alt + /”  快捷键可以打开智能提示
*/

/**
 * 引入头文件
 */
#include "utils/GpioHelper.h"

/**
 * 注册定时器
 * 在此数组中添加即可
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	{1,  1000},
};

static void onUI_init() {
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
}

static void onUI_quit() {
}

static void onProtocolDataUpdate(const SProtocolData &data) {
    // 串口数据回调接口
}

static bool onUI_Timer(int id) {
    //Tips:添加定时器响应的代码到这里,但是需要在本文件的 REGISTER_ACTIVITY_TIMER_TAB 数组中 注册
    //id 是定时器设置时候的标签,这里不要写耗时的操作，否则影响UI刷新,ruturn:[true] 继续运行定时器;[false] 停止运行当前定时器
	switch (id) {
		case 1:
		{
		  // 注意：！！！！！！
		  // GpioHelper::input 参数为脚位名称， 不同的平台，名字的定义不同，具体要参考 文档网站 GPIO操作部分
		  // 如果购买的是模组，还需要启用gpio功能，升级生成的固件后才可正常使用

		  // 例如将B_02脚设为输入，并读取B_02 这个 io口的 状态
		  // 1 为 高电平
		  // 0 为 低电平
		  // -1 读取失败
			int state = GpioHelper::input("B_02");
			mTextview2Ptr->setText(state);
		}
			break;
		default:
			break;
	}
    return true;
}

static bool onmainActivityTouchEvent(const MotionEvent &ev) {
    // 返回false触摸事件将继续传递到控件上，返回true表示该触摸事件在此被拦截了，不再传递到控件上
    return false;
}

static bool onButtonClick_Button1(ZKButton *pButton) {
  // 注意：！！！！！！
  // GpioHelper::input 参数为脚位名称， 不同的平台，名字的定义不同，具体要参考 文档网站 GPIO操作部分
  // 如果购买的是模组，还需要启用gpio功能，升级生成的固件后才可正常使用

  // 将z11s平台  B02脚 输出高
	GpioHelper::output("B_02", 1);

	// 将SV50PB平台 PIN7脚 输出高
	GpioHelper::output("PIN7", 1);

	// 将SV50PC平台 PIN2脚 输出高
	GpioHelper::output("PIN2", 1);

    return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {
  // 注意：
  // GpioHelper::input 参数为脚位名称， 不同的平台，名字的定义不同，具体要参考 文档网站 GPIO操作部分
  // 如果购买的是模组，还需要启用gpio功能，升级生成的固件后才可正常使用

  // 将z11s平台  B02脚 输出低
  GpioHelper::output("B_02", 0);

  // 将SV50PB平台 PIN7脚 输出低
  GpioHelper::output("PIN7", 0);

  // 将SV50PC平台 PIN2脚 输出低
  GpioHelper::output("PIN2", 0);

    return false;
}
