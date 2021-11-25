#pragma once
#include "uart/ProtocolSender.h"
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
typedef struct {
	int id;
	int sampleWeight;
	string waterContent;
	string sulfurContent;
	string drySulfurContent;
	string time;
}TestData;

static TestData data[] = {
		{1, 100, "15.2%", "14.3", "16.4", "2019-07-01"},
		{2, 100, "16.2%", "15.3", "17.4", "2019-07-02"},
		{3, 100, "17.2%", "16.3", "18.4", "2019-07-03"},
		{4, 100, "18.2%", "17.3", "19.4", "2019-07-04"},
		{5, 100, "19.2%", "18.3", "20.4", "2019-07-05"},
		{6, 100, "20.2%", "19.3", "21.4", "2019-07-06"},
		{7, 100, "21.2%", "20.3", "22.4", "2019-07-07"},
		{8, 100, "22.2%", "21.3", "23.4", "2019-07-08"},
		{9, 100, "23.2%", "22.3", "24.4", "2019-07-09"},
		{10, 100, "24.2%", "23.3", "25.4", "2019-07-10"},
};

static const char *buff[] = {"样号", "样重", "水分", "硫含量", "干基硫", "实验时间"};
/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");

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
static int getListItemCount_Listview1(const ZKListView *pListView) {
    //LOGD("getListItemCount_Listview1 !\n");
    return (sizeof(data)/sizeof(TestData));
}

static void obtainListItemData_Listview1(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index) {
    //LOGD(" obtainListItemData_ Listview1  !!!\n");
	ZKListView::ZKListSubItem* pSubId = pListItem->findSubItemByID(ID_MAIN_IDSubItem);
	ZKListView::ZKListSubItem* pSubWeight = pListItem->findSubItemByID(ID_MAIN_WeightSubItem);
	ZKListView::ZKListSubItem* pSubWater = pListItem->findSubItemByID(ID_MAIN_WaterSubItem);
	ZKListView::ZKListSubItem* pSubSul = pListItem->findSubItemByID(ID_MAIN_SulSubItem);
	ZKListView::ZKListSubItem* pSubDrySul = pListItem->findSubItemByID(ID_MAIN_DrySulSubItem);
	ZKListView::ZKListSubItem* pSubTime = pListItem->findSubItemByID(ID_MAIN_TimeSubItem);

	pSubId->setText(data[index].id);
	pSubWeight->setText(data[index].sampleWeight);
	pSubWater->setText(data[index].waterContent);
	pSubSul->setText(data[index].sulfurContent);
	pSubDrySul->setText(data[index].drySulfurContent);
	pSubTime->setText(data[index].time);


}

static void onListItemClick_Listview1(ZKListView *pListView, int index, int id) {
    //LOGD(" onListItemClick_ Listview1  !!!\n");
}
static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
    return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {
    //LOGD(" ButtonClick Button2 !!!\n");
    return false;
}

static bool onButtonClick_Button3(ZKButton *pButton) {
    //LOGD(" ButtonClick Button3 !!!\n");
    return false;
}

static bool onButtonClick_Button4(ZKButton *pButton) {
    //LOGD(" ButtonClick Button4 !!!\n");
    return false;
}

static bool onButtonClick_Button5(ZKButton *pButton) {
    //LOGD(" ButtonClick Button5 !!!\n");
    return false;
}

static bool onButtonClick_Button6(ZKButton *pButton) {
    //LOGD(" ButtonClick Button6 !!!\n");
    return false;
}
