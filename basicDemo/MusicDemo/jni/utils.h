/*
 * utils.h
 *
 *  Created on: 2020年6月27日
 *      Author: pengzc
 */

#ifndef JNI_UTILS_H_
#define JNI_UTILS_H_

#include <string>
#include <vector>

/**
 * 遍历目录
 */
std::vector<std::string> read_dir(std::string path, bool recursion);
std::vector<std::string> read_dir(std::string path, std::string prefix, std::vector<std::string>& content, bool recursion);

/**
   *  查找受支持的音频文件
 */
std::vector<std::string> find_supported_audio_files(std::vector<std::string> &v);


#endif /* JNI_UTILS_H_ */
