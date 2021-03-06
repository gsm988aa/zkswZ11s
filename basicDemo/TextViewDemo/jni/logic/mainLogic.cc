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

#include "utils/TimeHelper.h"

static void updateTime() {
	char timeStr[20];
	struct tm *t = TimeHelper::getDateTime();

	snprintf(timeStr, sizeof(timeStr), "%02d:%02d", t->tm_hour, t->tm_min);
	mTextTimePtr->setText(timeStr);
}


static void updateAnimation(){
    static int animationIndex = 0;
	char path[50] = {0};
	snprintf(path, sizeof(path), "animation/loading_%d.png", animationIndex);
	mTextviewAnimationPtr->setBackgroundPic(path);
	animationIndex = (animationIndex + 1) % 60;
}

/**
 * 注册定时器
 * 在此数组中添加即可
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	{ 0, 1000 },	// 定时器id=0, 时间间隔1秒
	{ 1, 50 },
};

static void onUI_init() {
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
	updateTime();
}

static void onUI_quit() {

}


// 串口数据回调接口
static void onProtocolDataUpdate(const SProtocolData &data) {
  //根据串口解析后的数据，按自己的需求控制UI

  //例如
  //本样例程序协议初步定义为 FF 55 00 01 len xx xx xx ,  len为后续字节的长度
  //串口协议解析部分可查看uart/ProtocolParser.cpp 文件中的 parseProtocol函数及procParse函数
  //向本机串口发送 ff 55 00 01 05 61 62 63 64 65   ，则设置文本为 “abcde”
  //注意，本系统仅支持utf-8编码，如果是其他编码请自行转换编码，才能正确显示文字
  std::string old_str = "通过串口更新文字：";
  mTextview23Ptr->setText(old_str + (char*)data.buf);
}

static bool onUI_Timer(int id) {
    //Tips:添加定时器响应的代码到这里,但是需要在本文件的 REGISTER_ACTIVITY_TIMER_TAB 数组中 注册
    //id 是定时器设置时候的标签,这里不要写耗时的操作，否则影响UI刷新,ruturn:[true] 继续运行定时器;[false] 停止运行当前定时器
    switch (id) {
		case 0:
		{
			updateTime();

			static int num = 0;
			// 设置数字
			mNumTextviewPtr->setText(num);
			num = (num + 1) % 10;

			static char chr = 'A';
			// 设置字符
			mCharTextviewPtr->setText(chr);

			char str[4] = { 0 };
			str[0] = str[1] = str[2] = chr;
			// 设置字符串
			mStrTextviewPtr->setText(str);

			chr++;
			if (chr > 'Z') { chr = 'A'; }

			static int index = 0;
			int colTab[5] = { 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFFFF, 0x000000 };
			mColorTextviewPtr->setTextColor(colTab[index]);
			index = (index + 1) % 5;
		}
			break;
		case 1:
		{
			updateAnimation();
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
