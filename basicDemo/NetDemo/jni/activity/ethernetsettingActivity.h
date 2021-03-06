/***********************************************
/gen auto by zuitools
***********************************************/
#ifndef __ETHERNETSETTINGACTIVITY_H__
#define __ETHERNETSETTINGACTIVITY_H__


#include "app/Activity.h"
#include "entry/EasyUIContext.h"

#include "uart/ProtocolData.h"
#include "uart/ProtocolParser.h"

#include "utils/Log.h"
#include "control/ZKDigitalClock.h"
#include "control/ZKButton.h"
#include "control/ZKCircleBar.h"
#include "control/ZKDiagram.h"
#include "control/ZKListView.h"
#include "control/ZKPointer.h"
#include "control/ZKQRCode.h"
#include "control/ZKTextView.h"
#include "control/ZKSeekBar.h"
#include "control/ZKEditText.h"
#include "control/ZKVideoView.h"
#include "window/ZKSlideWindow.h"

/*TAG:Macro宏ID*/
#define ID_ETHERNETSETTING_macAddress    50013
#define ID_ETHERNETSETTING_ipAddress    50011
#define ID_ETHERNETSETTING_macAddrTip    50009
#define ID_ETHERNETSETTING_ipAddrTip    50007
#define ID_ETHERNETSETTING_menuTipWin    110003
#define ID_ETHERNETSETTING_saveTip    50038
#define ID_ETHERNETSETTING_saveTipWin    100012
#define ID_ETHERNETSETTING_secondDNSInput    51005
#define ID_ETHERNETSETTING_secondDNS    50018
#define ID_ETHERNETSETTING_firstDNSInput    51004
#define ID_ETHERNETSETTING_firstDNS    50014
#define ID_ETHERNETSETTING_gateWayInput    51003
#define ID_ETHERNETSETTING_gateWay    50010
#define ID_ETHERNETSETTING_maskInput    51002
#define ID_ETHERNETSETTING_mask    50005
#define ID_ETHERNETSETTING_ipAddrInput    51001
#define ID_ETHERNETSETTING_ipAddr    50002
#define ID_ETHERNETSETTING_staticIPSetUpWin    110001
#define ID_ETHERNETSETTING_connectType    50001
#define ID_ETHERNETSETTING_bottomLine    50006
#define ID_ETHERNETSETTING_title    50019
#define ID_ETHERNETSETTING_topWin    100006
#define ID_ETHERNETSETTING_BUTTON_MENU    20037
#define ID_ETHERNETSETTING_sys_back   100
#define ID_ETHERNETSETTING_STATIC_IP_BUTTON    20003
#define ID_ETHERNETSETTING_DYNAMIC_IP_BUTTON    20002
#define ID_ETHERNETSETTING_SAVE_BUTTON    20001
/*TAG:Macro宏ID END*/

class ethernetsettingActivity : public Activity, 
                     public ZKSeekBar::ISeekBarChangeListener, 
                     public ZKListView::IItemClickListener,
                     public ZKListView::AbsListAdapter,
                     public ZKSlideWindow::ISlideItemClickListener,
                     public EasyUIContext::ITouchListener,
                     public ZKEditText::ITextChangeListener,
                     public ZKVideoView::IVideoPlayerMessageListener
{
public:
    ethernetsettingActivity();
    virtual ~ethernetsettingActivity();

    /**
     * 注册定时器
     */
	void registerUserTimer(int id, int time);
	/**
	 * 取消定时器
	 */
	void unregisterUserTimer(int id);
	/**
	 * 重置定时器
	 */
	void resetUserTimer(int id, int time);

protected:
    /*TAG:PROTECTED_FUNCTION*/
    virtual const char* getAppName() const;
    virtual void onCreate();
    virtual void onClick(ZKBase *pBase);
    virtual void onResume();
    virtual void onPause();
    virtual void onIntent(const Intent *intentPtr);
    virtual bool onTimer(int id);

    virtual void onProgressChanged(ZKSeekBar *pSeekBar, int progress);

    virtual int getListItemCount(const ZKListView *pListView) const;
    virtual void obtainListItemData(ZKListView *pListView, ZKListView::ZKListItem *pListItem, int index);
    virtual void onItemClick(ZKListView *pListView, int index, int subItemIndex);

    virtual void onSlideItemClick(ZKSlideWindow *pSlideWindow, int index);

    virtual bool onTouchEvent(const MotionEvent &ev);

    virtual void onTextChanged(ZKTextView *pTextView, const string &text);

    void rigesterActivityTimer();

    virtual void onVideoPlayerMessage(ZKVideoView *pVideoView, int msg);
    void videoLoopPlayback(ZKVideoView *pVideoView, int msg, size_t callbackTabIndex);
    void startVideoLoopPlayback();
    void stopVideoLoopPlayback();
    bool parseVideoFileList(const char *pFileListPath, std::vector<string>& mediaFileList);
    int removeCharFromString(string& nString, char c);


private:
    /*TAG:PRIVATE_VARIABLE*/
    int mVideoLoopIndex;
    int mVideoLoopErrorCount;

};

#endif