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
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "manager/ConfigManager.h"

#define   SRC_PATH  "/mnt/extsd"

typedef struct{
	char path[256];
	int type;
	char name[256];
}FileInfo;

static vector<FileInfo>fileList;
static vector<FileInfo>curPathFile;
static string curPath = SRC_PATH;
static int sTotalFileNum = 0;

/**
 * 扫描文件
 * path:扫描路径
 * fileType:指令扫描文件类型，为空时表示不指定文件类型
 */
static bool ScanFile(const char *path, const char *fileType) {
	bool isHaveFile = false;
    struct dirent* d = NULL;
    DIR *pDir;
    pDir = opendir(path);
    if (pDir == NULL) {
        //被当作目录，但是执行opendir后发现又不是目录，比如软链接就会发生这样的情况。
        return 0;
    }
    while (NULL != (d = readdir(pDir))) {
    	FileInfo info;
        if (d->d_type == DT_REG) {
            //file
        	if(strlen(fileType) == 0){
        		if(curPath == path){
        			memset(info.path, 0, 256);
					strcpy(info.path, path);
					info.type = DT_REG;
					memset(info.name, 0, 256);
					strcpy(info.name, d->d_name);
					fileList.push_back(info);
        		}
				isHaveFile = true;
        	}else{
        		string name = d->d_name;
        		unsigned int pos = name.rfind(".");
        		if(pos != string::npos){
        			name = name.substr(pos+1, name.length());
        			if(strcmp(fileType, name.c_str()) == 0){
        				if(curPath == path){
        					memset(info.path, 0, 256);
							strcpy(info.path, path);
							info.type = DT_REG;
							memset(info.name, 0, 256);
							strcpy(info.name, d->d_name);
							fileList.push_back(info);
        				}
						isHaveFile = true;
        			}
        		}
        	}
        } else {
            if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) {
                continue;
            }
            //directory
            string tempPath(path);
            tempPath += "/";
            tempPath += d->d_name;
            string fullDirPath = tempPath;
            if(strlen(fileType) == 0){
            	if(curPath == path){
            		memset(info.path, 0, 256);
					strcpy(info.path, path);
					info.type = DT_DIR;
					memset(info.name, 0, 256);
					strcpy(info.name, d->d_name);
					fileList.push_back(info);
            	}
				ScanFile(fullDirPath.c_str(), fileType);
            }else{
            	if(ScanFile(fullDirPath.c_str(), fileType)){
            		if(curPath == path){
            			memset(info.path, 0, 256);
						strcpy(info.path, path);
						info.type = DT_DIR;
						memset(info.name, 0, 256);
						strcpy(info.name, d->d_name);
						fileList.push_back(info);
            		}
					isHaveFile = true;
				}
            }
        }
    }
    closedir(pDir);
    return isHaveFile;
}

/**
 * 计算要显示的文件数量
 */
static int getFileNum(){
	sTotalFileNum = 0;
	curPathFile.clear();
	std::vector<FileInfo>::iterator it = fileList.begin();
	for(; it != fileList.end(); it++){
		if(((strcmp(it->path, curPath.c_str()) == 0))){
			sTotalFileNum++;
			curPathFile.push_back(*it);
		}
	}
	return sTotalFileNum;
}
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
	mCurPathButtonPtr->setText(SRC_PATH);
	fileList.clear();
	ScanFile(SRC_PATH, "");
	getFileNum();
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
static int getListItemCount_FileListview(const ZKListView *pListView) {
    //LOGD("getListItemCount_FileListview !\n");
    return sTotalFileNum;
}

static void obtainListItemData_FileListview(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index) {
    //LOGD(" obtainListItemData_ FileListview  !!!\n");
	//获取列表子项，并设置要显示的内容
	ZKListView::ZKListSubItem* pSubIcon = pListItem->findSubItemByID(ID_MAIN_IconSubItem);
	ZKListView::ZKListSubItem* pSubName = pListItem->findSubItemByID(ID_MAIN_FileNameSubItem);
	pSubIcon->setBackgroundPic((curPathFile.at(index).type == DT_REG) ? CONFIGMANAGER->getResFilePath("file.png").c_str() : CONFIGMANAGER->getResFilePath("folder.png").c_str());
	pSubName->setText(curPathFile.at(index).name);
}

/**
 * 点击按钮返回上一层目录
 */
static void onListItemClick_FileListview(ZKListView *pListView, int index, int id) {
    //LOGD(" onListItemClick_ FileListview  !!!\n");
	if(curPathFile.at(index).type == DT_DIR){
		curPath += '/';
		curPath += curPathFile.at(index).name;
		mCurPathButtonPtr->setText(curPath.c_str());
		fileList.clear();
		ScanFile(curPath.c_str(), mFileTypeEdittextPtr->getText().c_str());
		getFileNum();
		mFileListviewPtr->refreshListView();
		mFileListviewPtr->setSelection(0);
	}
}

static bool onButtonClick_CurPathButton(ZKButton *pButton) {
    //LOGD(" ButtonClick CurPathButton !!!\n");
	if(strcmp(curPath.c_str(), SRC_PATH)){
		unsigned int pos = curPath.rfind('/');
		if(pos != string::npos){
			curPath = curPath.substr(0, pos);
		}
		fileList.clear();
		ScanFile(curPath.c_str(), mFileTypeEdittextPtr->getText().c_str());
		pButton->setText(curPath.c_str());
		getFileNum();

		mFileListviewPtr->refreshListView();
		mFileListviewPtr->setSelection(0);
	}
    return false;
}
static void onEditTextChanged_FileTypeEdittext(const std::string &text) {
    //LOGD(" onEditTextChanged_ FileTypeEdittext %s !!!\n", text.c_str());
    fileList.clear();
	ScanFile(SRC_PATH, text.c_str());
	getFileNum();
}
