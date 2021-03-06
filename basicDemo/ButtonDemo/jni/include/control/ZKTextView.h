/*
 * ZKTextView.h
 *
 *  Created on: Jun 10, 2017
 *      Author: guoxs
 */

#ifndef _CONTROL_ZKTEXTVIEW_H_
#define _CONTROL_ZKTEXTVIEW_H_

#include "ZKBase.h"

class ZKTextViewPrivate;

/**
 * @brief 文本控件
 */
class ZKTextView : public ZKBase {
	ZK_DECLARE_PRIVATE(ZKTextView)

public:
	ZKTextView(HWND hParentWnd);
	virtual ~ZKTextView();

	/**
	 * @brief 设置string文本
	 */
	void setText(const std::string &text);

	/**
	 * @brief 设置字符串文本
	 */
	void setText(const char *text);

	/**
	 * @brief 设置字符文本
	 */
	void setText(char text);

	/**
	 * @brief 设置数字文本
	 */
	void setText(int text);

	/**
	 * @brief 获取文本内容
	 */
	const std::string& getText() const { return mText; }

	/**
	 * @brief 支持多国语言设置接口
	 */
	void setTextTr(const char *name);

	void reloadTextTr();

	/**
	 * @brief 设置文本颜色
	 * @param color 颜色值为0x RGB，不支持alpha
	 */
	void setTextColor(int color);

	/**
	 * @brief 设置文本状态颜色
	 * @param status 状态
	 *    正常状态： E_CONTROL_STATUS_NORMAL
	 *    按下状态： E_CONTROL_STATUS_PRESSED
	 *    选中状态： E_CONTROL_STATUS_SELECTED
	 *    选中按下状态： E_CONTROL_STATUS_PRESSED | E_CONTROL_STATUS_SELECTED
	 *    无效状态： E_CONTROL_STATUS_INVALID
	 * @param color 颜色值为0x ARGB
	 */
	void setTextStatusColor(int status, int color);
	
	/**
	 * @brief 获取文本内容宽高
	 * @param text 文本内容
	 * @param w 返回文本宽度
	 * @param h 返回文本高度
	 */
	void getTextExtent(const char *text, int &w, int &h);

public:
	/**
	 * @brief 文本内容改变监听接口
	 */
	class ITextChangeListener {
	public:
		virtual ~ITextChangeListener() { }
		virtual void onTextChanged(ZKTextView *pTextView, const std::string &text) = 0;
	};

	void setTextChangeListener(ITextChangeListener *pListener) {
		mTextChangeListenerPtr = pListener;
	}

protected:
	ZKTextView(HWND hParentWnd, ZKBasePrivate *pBP);

	virtual void onBeforeCreateWindow(const Json::Value &json);
	virtual void onAfterCreateWindow(const Json::Value &json);
	virtual const char* getClassName() const { return ZK_TEXTVIEW; }

	virtual void onDraw(HDC hdc);
	virtual void onTimer(int id);

	void _section_(zk) drawText(HDC hdc);

private:
	void _section_(zk) parseTextViewAttributeFromJson(const Json::Value &json);
	int getCurTextColor() const;

private:
	typedef struct {
		char chr;
		PBITMAP pBmp;
		SIZE sz;
	} SCharsetInfo;

	typedef struct {
		SCharsetInfo *charsetList;
		int size;
	} SCharsetInfoTab;

	const SCharsetInfo* getCharsetInfo(const char c) const;

	typedef enum {
		E_ROLL_DIRECTION_LEFT_TO_RIGHT,
		E_ROLL_DIRECTION_RIGHT_TO_LEFT,
		E_ROLL_DIRECTION_TOP_TO_BOTTOM,
		E_ROLL_DIRECTION_BOTTOM_TO_TOP
	} ERollDirection;

protected:
	std::string mText;

	ITextChangeListener *mTextChangeListenerPtr;

	LayoutPosition mTextPosition;
	int mAlignment;			// 对齐方式

	PLOGFONT mLogFontPtr;
	int mFontSize;
	std::string mFontFamily; 	// 使用的字体库
	std::string mFontType; 		// 使用的字体库类型,如: ttf, bmp

	int mTextStatusColorTab[S_CONTROL_STATUS_TAB_LEN];
	int mTextBgColor;

	// 字符集相关
	SCharsetInfoTab mCharsetInfoTab;

	bool mIsRollEnable;		// 滚动字符使能
	int mRollIntervalTime;	// 滚动时间间隔
	int mRollStep;			// 滚动步进
	ERollDirection mRollDirection;
	LayoutPosition mRollPosition;
};

#endif /* _CONTROL_ZKTEXTVIEW_H_ */
