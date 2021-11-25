#pragma once
#include "uart/ProtocolSender.h"
#include "media/ZKMediaPlayer.h"
#include "utils.h"

static ZKMediaPlayer* player;
static bool is_play_success = false;

static std::vector<string> file_list;
static int play_index;

static bool is_tracking = false;
static int track_progress = -1;

namespace  {
class SeekbarChangeListener: public ZKSeekBar::ISeekBarChangeListener {
public:
  virtual void onProgressChanged(ZKSeekBar *pSeekBar, int progress) {
    track_progress = progress;
  }
  virtual void onStartTrackingTouch(ZKSeekBar *pSeekBar) {
    is_tracking = true;
  }
  virtual void onStopTrackingTouch(ZKSeekBar *pSeekBar) {
    is_tracking = false;
    if (track_progress >= 0) {
      player->seekTo(track_progress * 1000);
      track_progress = -1;
    }
  }
};

}
static SeekbarChangeListener progressbar;

// 播放下一首
static void next() {
    if (!file_list.empty()) {
        play_index = (play_index + 1) % file_list.size();
        player->play(file_list[play_index].c_str());
        mTextviewNamePtr->setText(file_list[play_index].c_str());
    }
}

// 播放上一首
static void prev() {
    if (!file_list.empty()) {
        play_index = (play_index - 1 + file_list.size()) % file_list.size();
        player->play(file_list[play_index].c_str());
        mTextviewNamePtr->setText(file_list[play_index].c_str());
    }
}

static void setPlayerVolume(ZKMediaPlayer* player, float volume) {
  player->setVolume(volume, volume);
}

class PlayerMessageListener : public ZKMediaPlayer::IPlayerMessageListener {
public:
    virtual void onPlayerMessage(ZKMediaPlayer *pMediaPlayer, int msg, void *pMsgData) {
        switch (msg) {
        case ZKMediaPlayer::E_MSGTYPE_ERROR_INVALID_FILEPATH:
        case ZKMediaPlayer::E_MSGTYPE_ERROR_MEDIA_ERROR:
            // 出错消息
            is_play_success = false;
            next();
            break;

        case ZKMediaPlayer::E_MSGTYPE_PLAY_STARTED:
            // 开始播放消息
        {
            is_play_success = true;
            int max = player->getDuration() / 1000;
            char timeStr[12] = {0};
            snprintf(timeStr, sizeof(timeStr), "%02d:%02d", max / 60, max % 60);
            mDurationTextViewPtr->setText(timeStr);
            mPlayProgressSeekbarPtr->setMax(max);
            mButtonPlayPtr->setSelected(true);
        }
            break;

        case ZKMediaPlayer::E_MSGTYPE_PLAY_COMPLETED:
            // 播放结束消息
            is_play_success = false;
            next();
            break;
        }
    }
};
static PlayerMessageListener sPlayerMessageListener;

/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
  //{0,  6000}, //定时器id=0, 时间间隔6秒
  {1,  1000},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
    player = new ZKMediaPlayer(ZKMediaPlayer::E_MEDIA_TYPE_AUDIO);
    player->setPlayerMessageListener(&sPlayerMessageListener);
    setPlayerVolume(player, 0.5);
    mPlayProgressSeekbarPtr->setSeekBarChangeListener(&progressbar);
}

/**
 * 当切换到该界面时触发
 */
static void onUI_intent(const Intent *intentPtr) {

}

/*
 * 当界面显示时触发
 */
static void onUI_show() {
  file_list.clear();
  // 递归扫描TF卡内的文件
  file_list = read_dir("/mnt/extsd", true);
  // 根据后缀名查找能播放的音频格式文件
  file_list = find_supported_audio_files(file_list);

  play_index = -1;
  mSeekbar1Ptr->setProgress(5);
  next();
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
    mPlayProgressSeekbarPtr->setSeekBarChangeListener(NULL);
    player->setPlayerMessageListener(NULL);
    player->stop();
    if (player) {
      delete player;
    }
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
static bool onUI_Timer(int id) {
    switch (id) {
    case 1: {
        int curPos = -1;
        if (player->isPlaying()) {
            curPos = player->getCurrentPosition() / 1000;
        }
        if (curPos >= 0) {
            char timeStr[10];
            snprintf(timeStr, sizeof(timeStr), "%02d:%02d", curPos / 60, curPos % 60);
            mCurPosTextViewPtr->setText(timeStr);
            mPlayProgressSeekbarPtr->setProgress(curPos);
        }
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

static bool onButtonClick_NextButton(ZKButton *pButton) {
    next();
    return false;
}

static bool onButtonClick_PrevButton(ZKButton *pButton) {
    prev();
    return false;
}

static void onProgressChanged_PlayProgressSeekbar(ZKSeekBar *pSeekBar, int progress) {

}

static bool onButtonClick_VoiceButton(ZKButton *pButton) {
    mSoundWindowPtr->showWnd();
    return false;
}

static void onProgressChanged_Seekbar1(ZKSeekBar *pSeekBar, int progress) {
    setPlayerVolume(player, (float) progress / 10);
}
static bool onButtonClick_ButtonPlay(ZKButton *pButton) {
    if (player->isPlaying()) {
        mButtonPlayPtr->setSelected(false);
        player->pause();
    } else {
        player->resume();
        mButtonPlayPtr->setSelected(true);
    }
    return false;
}
static bool onButtonClick_Button4(ZKButton *pButton) {
    EASYUICONTEXT->openActivity("helpAudioActivity");
    return false;
}
