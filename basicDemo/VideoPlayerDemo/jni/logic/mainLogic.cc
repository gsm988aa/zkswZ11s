#include "media/ZKMediaPlayer.h"
#include "utils.h"

static std::vector<string> media_file_list_;
static int play_index_;


static bool is_tracking_ = false;
static int track_progress_ = -1;

namespace video {
class SeekbarChangeListener: public ZKSeekBar::ISeekBarChangeListener {
public:
  virtual void onProgressChanged(ZKSeekBar *pSeekBar, int progress) {
    track_progress_ = progress;
  }
  virtual void onStartTrackingTouch(ZKSeekBar *pSeekBar) {
    is_tracking_ = true;
  }
  virtual void onStopTrackingTouch(ZKSeekBar *pSeekBar) {
    is_tracking_ = false;
    if (track_progress_ >= 0) {
      mVideoviewTTPtr->seekTo(track_progress_ * 1000);
      track_progress_ = -1;
    }
  }
};
}
static video::SeekbarChangeListener progressbar;

//下一视频
static void next() {
    if (!media_file_list_.empty()) {
        LOGD("! empty");
        play_index_ = (play_index_ + 1) % media_file_list_.size();
        mVideoviewTTPtr->play(media_file_list_[play_index_].c_str());
    }
}

//上一个视频
static void prev() {
    if (!media_file_list_.empty()) {
        play_index_ = (play_index_ - 1 + media_file_list_.size()) % media_file_list_.size();
        mVideoviewTTPtr->play(media_file_list_[play_index_].c_str());
    }
}

/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
    //{0,  6000}, //定时器id=0, 时间间隔6秒
    { 1, 1000 },
};

/**
 * 当界面构造时触发
 */
static void onUI_init() {
    mPlayProgressSeekbarPtr->setSeekBarChangeListener(&progressbar);

    media_file_list_.clear();
    // 递归扫描TF卡内的文件
    media_file_list_ = read_dir("/mnt/extsd", true);
    // 根据后缀名查找能播放的视频格式文件
    media_file_list_ = find_supported_video_files(media_file_list_);

    LOGD("播放列表 size = %d", media_file_list_.size());
    for (size_t i = 0; i < media_file_list_.size(); ++i) {
      LOGD("%s", media_file_list_.at(i).c_str());
    }

    mVideoviewTTPtr->setVolume(0.5);
    play_index_ = -1;
    mSoundSeekbarPtr->setProgress(5);
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
  if (!mVideoviewTTPtr->isPlaying()) {
    play_index_ = play_index_ > 0 ? play_index_ - 1 : 0;
    next();
  }
}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {
    if (mVideoviewTTPtr->isPlaying()) {
        mVideoviewTTPtr->stop();
    }
}

/*
 * 当界面完全退出时触发
 */
static void onUI_quit() {
    if (mVideoviewTTPtr->isPlaying()) {
        mVideoviewTTPtr->stop();
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
        if (mVideoviewTTPtr->isPlaying()) {
            curPos = mVideoviewTTPtr->getCurrentPosition() / 1000;
            LOGD("curPos = %d", mVideoviewTTPtr->getDuration());
        }
        if (curPos >= 0) {
            char timeStr[10];
            sprintf(timeStr, "%02d:%02d", curPos / 60, curPos % 60);
            mCurPosTextViewPtr->setText(timeStr);

            if (!is_tracking_) {
                mPlayProgressSeekbarPtr->setProgress(curPos);
            }
            if (curPos > mPlayProgressSeekbarPtr->getMax()) {
              next();
            }
        }
        break;
    }
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
    return false;
}

static void onProgressChanged_SoundSeekbar(ZKSeekBar *pSeekBar, int progress) {
    mVideoviewTTPtr->setVolume((float) progress / 10);
}

static bool onButtonClick_PlayButton(ZKButton *pButton) {
    if (mVideoviewTTPtr->isPlaying()) {
        mVideoviewTTPtr->pause();
        pButton->setSelected(false);
    } else {
        mVideoviewTTPtr->resume();
        pButton->setSelected(true);
    }
    return false;
}

static bool onButtonClick_PrevButton(ZKButton *pButton) {
    prev();
    return false;
}

static bool onButtonClick_NextButton(ZKButton *pButton) {
    next();
    return false;
}

static void onProgressChanged_PlayProgressSeekbar(ZKSeekBar *pSeekBar, int progress) {

}

static bool onButtonClick_VoiceButton(ZKButton *pButton) {
    //LOGD(" ButtonClick VoiceButton !!!\n");
    mSoundWindowPtr->showWnd();
    return false;
}

static bool onButtonClick_sys_back(ZKButton *pButton) {
    return false;
}

static void onVideoViewPlayerMessageListener_VideoviewTT(ZKVideoView *pVideoView, int msg) {
    switch (msg) {
    case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_STARTED:
        {
            int max = pVideoView->getDuration() / 1000;
            char timeStr[12] = {0};
            snprintf(timeStr, sizeof(timeStr), "%02d:%02d", max / 60, max % 60);
            mDurationTextViewPtr->setText(timeStr);
            mPlayProgressSeekbarPtr->setMax(max);
            mPlayButtonPtr->setSelected(true);
        }
        break;
    case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED:
        next();
        break;
    case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_ERROR:
      LOGD("播放出错");
        break;
    }
}
static bool onButtonClick_ButtonZoom(ZKButton *pButton) {
    return false;
}
