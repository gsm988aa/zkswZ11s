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
#include "uart/ProtocolSender.h"

//实现长按监听接口
class LongClickListener : public ZKBase::ILongClickListener {

	virtual void onLongClick(ZKBase *pBase) {
        LOGD("触发长按事件");
        static int count = 0;

        char buf[128] = {0};
        snprintf(buf, sizeof(buf), "长按事件触发次数 %d", ++count);
        mLongButtonPtr->setText(buf);
	}
};

namespace {  // 加个匿名作用域，防止多个源文件定义相同类名，运行时冲突
// 实现触摸监听接口
class TouchListener : public ZKBase::ITouchListener {
public:
    virtual void onTouchEvent(ZKBase *pBase, const MotionEvent &ev) {
        switch (ev.mActionStatus) {
        case MotionEvent::E_ACTION_DOWN:
            mButtonTouchPtr->setText("按下");
            break;
        case MotionEvent::E_ACTION_UP:
            mButtonTouchPtr->setText("抬起");
            break;
        default:
            break;
        }
    }
};
}

static LongClickListener longButtonClickListener;
static TouchListener touchListener;

static void onUI_init(){
	//注册按键长按监听
	mLongButtonPtr->setLongClickListener(&longButtonClickListener);
	//注册按键触摸监听
	mButtonTouchPtr->setTouchListener(&touchListener);
}

static void onUI_quit() {
	//取消按键长按监听
  mLongButtonPtr->setLongClickListener(NULL);
  //取消按键触摸监听
  mButtonTouchPtr->setTouchListener(NULL);
}

/**
 * 注册定时器
 * 在此数组中添加即可
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

// 串口数据回调接口
static void onProtocolDataUpdate(const SProtocolData &data) {
	//根据串口解析后的数据，按自己的需求控制UI

	//例如
	//本样例程序协议初步定义为 FF 55 00 01 01 xx
	//串口协议解析部分可查看uart/ProtocolParser.cpp 文件中的 parseProtocol函数及procParse函数
	//向本机串口发送 FF 55 00 01 01 01   可控制mButton1 显示
	//向本机串口发送 FF 55 00 01 01 00   可控制mButton1 隐藏

	if (data.value == 1) { //当value为1，显示Button1
		mButton1Ptr->setVisible(true);
	} else if (data.value == 0) { //当value为0，隐藏Button1
		mButton1Ptr->setVisible(false);
	}
}

static bool onUI_Timer(int id) {
    //Tips:添加定时器响应的代码到这里,但是需要在本文件的 REGISTER_ACTIVITY_TIMER_TAB 数组中 注册
    //id 是定时器设置时候的标签,这里不要写耗时的操作，否则影响UI刷新,ruturn:[true] 继续运行定时器;[false] 停止运行当前定时器
    return true;
}

static bool onmainActivityTouchEvent(const MotionEvent &ev) {
    // 返回false触摸事件将继续传递到控件上，返回true表示该触摸事件在此被拦截了，不再传递到控件上
    return false;
}

static bool onButtonClick_Button1(ZKButton *pButton) {
    LOGD(" ButtonClick Button1 !!!\n");
	pButton->setSelected(!pButton->isSelected());

	BYTE req[1] = {0};
	sendProtocol(1, req, sizeof(req));

    return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {
    //LOGD(" ButtonClick Button2 !!!\n");
	pButton->setSelected(!pButton->isSelected());
    return false;
}

static bool onButtonClick_ClkButton(ZKButton *pButton) {
    //LOGD(" ButtonClick ClkButton !!!\n");
	EASYUICONTEXT->openActivity("subActivity");
    return false;
}

static bool onButtonClick_LongButton(ZKButton *pButton) {
    //LOGD(" ButtonClick LongButton !!!\n");
    return false;
}
static bool onButtonClick_ButtonTouch(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonTouch !!!\n");
    return false;
}
