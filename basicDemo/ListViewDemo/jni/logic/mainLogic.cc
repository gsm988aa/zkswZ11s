#pragma once
#include "uart/ProtocolSender.h"

#include <vector>
#include "manager/ConfigManager.h"

#define MAX_NUM 12  // 列表最大条目数

typedef struct data{
	char mainText[20];
	char subText[20];
	bool state;
}SDATA;

vector <SDATA> vData;
static int num;     //列表条目数
static int cur_index;  //当前选中的条目索引值

string city[20] = {"北京","上海","天津","重庆","广州","深圳","合肥","郑州","石家庄"};


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
static int getListItemCount_ListView1(const ZKListView *pListView) {
    //LOGD("getListItemCount_ListView1 !\n");
	if (0 == num) {
		mTextView_TipPtr->setVisible(true);
	} else {
		mTextView_TipPtr->setVisible(false);
	}
    return num;
}

static void obtainListItemData_ListView1(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index) {
    //LOGD(" obtainListItemData_ ListView1  !!!\n");
	ZKListView::ZKListSubItem* psubText = pListItem->findSubItemByID(ID_MAIN_SubItemText);
	ZKListView::ZKListSubItem* psubSelectButton = pListItem->findSubItemByID(ID_MAIN_SubSetlectBtn);
	ZKListView::ZKListSubItem* SubDeleteBtn = pListItem->findSubItemByID(ID_MAIN_SubDeleteBtn);

	char backgroundPicPath[60] = {0};
	snprintf(backgroundPicPath,sizeof(backgroundPicPath),"pic/subListBackground%d.jpg",index);
	std::string path = CONFIGMANAGER->getResFilePath(backgroundPicPath);                //样例，可按需求添加图片
	psubText->setBackgroundPic(path.c_str());


	vector <SDATA>::iterator it = vData.begin();

	pListItem->setText(it[index].mainText);


	psubSelectButton->setSelected(it[index].state);

}

//static int IsMainText;
static void onListItemClick_ListView1(ZKListView *pListView, int index, int id) {
    //LOGD(" onListItemClick_ ListView1  !!!\n");

	if (id == ID_MAIN_SubItemText) {      //子项标题

		char backgroundPicPath[60] = {0};
		snprintf(backgroundPicPath,sizeof(backgroundPicPath),"pic/subListBackground%d.jpg",index);
		std::string path = CONFIGMANAGER->getResFilePath(backgroundPicPath);
		mWindow4Ptr->setBackgroundPic(path.c_str());
    	mWindow4Ptr->showWnd();

	}
	else if (id == ID_MAIN_SubSetlectBtn) {
		vector <SDATA>::iterator it = vData.begin();

		it[index].state = !it[index].state;
	}
	else if (id == ID_MAIN_SubDeleteBtn) {
		vector <SDATA>::iterator it = vData.begin();

    	vData.erase(it+index);
    	num = vData.size();  //更新num
	}
	else {     //主标题
		cur_index = index;     //记录索引值
		mTextView2Ptr->setText("修改主标题");
    	mWindow1Ptr->showWnd();
    	mEditText1Ptr->setText("");
	}
}

static bool onButtonClick_CityButton(ZKButton *pButton) {
    LOGD(" ButtonClick CityButton !!!\n");
    if (!mCityWindowPtr->isWndShow()) {
    	mCityWindowPtr->showWnd();
    }
    else {
    	mCityWindowPtr->hideWnd();
    }
    return false;
}

static int getListItemCount_CityListView(const ZKListView *pListView) {
    //LOGD("getListItemCount_CityListView !\n");
    return 9;
}

static void obtainListItemData_CityListView(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index) {
    //LOGD(" obtainListItemData_ CityListView  !!!\n");
	pListItem->setText(city[index].c_str());
}

static void onListItemClick_CityListView(ZKListView *pListView, int index, int id) {
    //LOGD(" onListItemClick_ CityListView  !!!\n");
	mCityButtonPtr->setText(city[index].c_str());
	mCityWindowPtr->hideWnd();
}

static bool onButtonClick_AddButton(ZKButton *pButton) {
    LOGD(" ButtonClick AddButton !!!\n");
    mTextView_TipPtr->setVisible(false);
    SDATA sdata;
    if (num < MAX_NUM) {

    	char text1[20] = {0};
    	sprintf(text1, "主标题%d", num+1);
    	strcpy(sdata.mainText,text1);

		sdata.state = false;

		vData.push_back(sdata);
		num = vData.size();  				//更新num

        mListView1Ptr->refreshListView();     //主动立即刷新UI
    }else{
    	mWindow3Ptr->showWnd();
    }

    return false;
}

static void onEditTextChanged_EditText1(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditText1 %s !!!\n", text.c_str());
}

static bool onButtonClick_Button1(ZKButton *pButton) {
    LOGD(" ButtonClick Button1 !!!\n");
    mWindow1Ptr->hideWnd();
    return false;
}

static bool onButtonClick_OKButton(ZKButton *pButton) {
    LOGD(" ButtonClick OKButton !!!\n");
    vector <SDATA>::iterator it = vData.begin();

	strcpy(it[cur_index].mainText, mEditText1Ptr->getText().c_str());


    mListView1Ptr->refreshListView();     						 //主动立即刷新UI
    mWindow1Ptr->hideWnd();

    return false;
}

static bool onButtonClick_ConcelButton(ZKButton *pButton) {
    LOGD(" ButtonClick ConcelButton !!!\n");
    mWindow1Ptr->hideWnd();
    return false;
}
static bool onButtonClick_Button2(ZKButton *pButton) {
    LOGD(" ButtonClick Button2 !!!\n");
    mWindow3Ptr->hideWnd();
    return false;
}

static bool onButtonClick_Button3(ZKButton *pButton) {
    LOGD(" ButtonClick Button3 !!!\n");
    mWindow3Ptr->hideWnd();
    return false;
}
static bool onButtonClick_WinHideButton(ZKButton *pButton) {
    LOGD(" ButtonClick WinHideButton !!!\n");
    if(!mListWindowPtr->isWndShow()) {
    	mListWindowPtr->showWnd();
    	mWinHideButtonPtr->setText("列表隐藏");
    }else {
    	mListWindowPtr->hideWnd();
    	mWinHideButtonPtr->setText("列表显示");
    }
    return false;
}

static bool onButtonClick_SubHideButton(ZKButton *pButton) {
    LOGD(" ButtonClick SubHideButton !!!\n");
    return false;
}
