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

#include "net/NetManager.h"

#include "features.h"


#if defined(FLYTHINGS_ENABLE_HOTSPOT)
#define SOFTAPMANAGER		NETMANAGER->getSoftApManager()

class MySoftApStateListener : public SoftApManager::ISoftApStateListener {
public:
	virtual void handleSoftApState(ESoftApState state) {
		LOGD("MySoftApStateListener handleSoftApState state %d\n", state);

		switch (state) {
		case E_SOFTAP_ENABLED:
			mButtonOnOffPtr->setInvalid(false);
			mButtonOnOffPtr->setSelected(true);
			break;
		case E_SOFTAP_DISABLED:
			mButtonOnOffPtr->setInvalid(false);
			mButtonOnOffPtr->setSelected(false);
			break;
		case E_SOFTAP_DISABLING:
		case E_SOFTAP_ENABLING:
			mButtonOnOffPtr->setInvalid(true);
			mButtonOnOffPtr->setSelected(false);
			break;
		case E_SOFTAP_ENABLE_ERROR:
			mButtonOnOffPtr->setInvalid(false);
			mButtonOnOffPtr->setSelected(false);
			break;
		}
	}
};

static MySoftApStateListener sMySoftApStateListener;

#endif

/**
 * 注册定时器
 * 在此数组中添加即可
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

static void onUI_init() {
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
#if defined(FLYTHINGS_ENABLE_HOTSPOT)
	mButtonOnOffPtr->setSelected(SOFTAPMANAGER->isEnable());
	mEditTextSsidPtr->setText(SOFTAPMANAGER->getSsid());
	mEditTextPwdPtr->setText(SOFTAPMANAGER->getPwd());

	SOFTAPMANAGER->addSoftApStateListener(&sMySoftApStateListener);
#endif
}

static void onUI_quit() {
#if defined(FLYTHINGS_ENABLE_HOTSPOT)
	SOFTAPMANAGER->removeSoftApStateListener(&sMySoftApStateListener);
#endif
}


static void onProtocolDataUpdate(const SProtocolData &data) {
    // 串口数据回调接口
}

static bool onUI_Timer(int id) {
    //Tips:添加定时器响应的代码到这里,但是需要在本文件的 REGISTER_ACTIVITY_TIMER_TAB 数组中 注册
    //id 是定时器设置时候的标签,这里不要写耗时的操作，否则影响UI刷新,ruturn:[true] 继续运行定时器;[false] 停止运行当前定时器
    return true;
}

static bool onsoftapsettingActivityTouchEvent(const MotionEvent &ev) {
    // 返回false触摸事件将继续传递到控件上，返回true表示该触摸事件在此被拦截了，不再传递到控件上
    return false;
}

static bool onButtonClick_ButtonOnOff(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonOnOff !!!\n");
#if defined(FLYTHINGS_ENABLE_HOTSPOT)
	SOFTAPMANAGER->setEnable(!SOFTAPMANAGER->isEnable());
#endif
    return false;
}

static void onEditTextChanged_EditTextSsid(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextSsid %s !!!\n", text.c_str());
}

static void onEditTextChanged_EditTextPwd(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextPwd %s !!!\n", text.c_str());
}

static bool onButtonClick_ButtonPwd(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonPwd !!!\n");
	pButton->setSelected(!pButton->isSelected());
	mEditTextPwdPtr->setPassword(!pButton->isSelected());
    return false;
}

static bool onButtonClick_ButtonSave(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonSave !!!\n");
#if defined(FLYTHINGS_ENABLE_HOTSPOT)
	SOFTAPMANAGER->setSsidAndPwd(mEditTextSsidPtr->getText().c_str(),
					mEditTextPwdPtr->getText().c_str());
#endif
    return false;
}

static bool onButtonClick_sys_back(ZKButton *pButton) {
    //LOGD(" ButtonClick sys_back !!!\n");
    return false;
}
