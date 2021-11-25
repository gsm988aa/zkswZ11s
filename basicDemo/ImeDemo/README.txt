移植说明：选择适合的分辨率输入法界面进行移植  (移植UserIme_xxx_xxx.ftu文件）

1. 将ui目录下UserIme_xxx_xxx.ftu(选择需要使用的分辨率)文件拷贝到自己工程ui目录下;
	将activity目录下UserImeActivity.h和UserImeActivity.cpp文件拷贝到自己工程activity目录下;
	将resources目录下的文件拷贝到自己工程的resources目录下.
	将logic目录下UserImeLogic.cc文件拷贝到自己工程logic目录下;

2. 将将jni目录下的pinyin目录拷贝到自己工程jni目录下,
	将jni目录下的feature.h拷贝到自己工程jni目录下

3. 如果移植到Z6, Z11, A33系列平台，需要有feature.h中的宏定义;
	如果移植到Z20, Z21, H500s系列平台，不能有feature中的宏定义,必须把宏定义注释掉		

4. 将移动到自己工程中的输入法界面文件UserIme_xxx_xxx.ftu修改名称, 改为UserIme.ftu

移植完成后，点击编辑/输入控件，就会跳转到输入法界面，，输入中文需要项目属性中勾选输入法选项