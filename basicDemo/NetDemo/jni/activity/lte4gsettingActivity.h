/***********************************************
/gen auto by zuitools
***********************************************/
#ifndef __LTE4GSETTINGACTIVITY_H__
#define __LTE4GSETTINGACTIVITY_H__


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
#define ID_LTE4GSETTING_TextMacAddr    50013
#define ID_LTE4GSETTING_TextIPAddr    50011
#define ID_LTE4GSETTING_Textview6    50009
#define ID_LTE4GSETTING_Textview5    50007
#define ID_LTE4GSETTING_WindowMenuMode    110003
#define ID_LTE4GSETTING_TextViewVersion    50005
#define ID_LTE4GSETTING_Textview2    50001
#define ID_LTE4GSETTING_TextView4    50014
#define ID_LTE4GSETTING_TextViewManufacturer    50015
#define ID_LTE4GSETTING_TextViewICCID    50012
#define ID_LTE4GSETTING_TextViewIMSI    50010
#define ID_LTE4GSETTING_TextViewIMEI    50008
#define ID_LTE4GSETTING_TextView3    50004
#define ID_LTE4GSETTING_TextView2    50003
#define ID_LTE4GSETTING_TextView1    50002
#define ID_LTE4GSETTING_ButtonOnOff    20038
#define ID_LTE4GSETTING_ButtonMenu    20037
#define ID_LTE4GSETTING_Textview8    50006
#define ID_LTE4GSETTING_Textview1    50019
#define ID_LTE4GSETTING_sys_back   100
#define ID_LTE4GSETTING_Window1    100006
/*TAG:Macro宏ID END*/

class lte4gsettingActivity : public Activity, 
                     public ZKSeekBar::ISeekBarChangeListener, 
                     public ZKListView::IItemClickListener,
                     public ZKListView::AbsListAdapter,
                     public ZKSlideWindow::ISlideItemClickListener,
                     public EasyUIContext::ITouchListener,
                     public ZKEditText::ITextChangeListener,
                     public ZKVideoView::IVideoPlayerMessageListener
{
public:
    lte4gsettingActivity();
    virtual ~lte4gsettingActivity();

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