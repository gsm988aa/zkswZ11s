/*
 * utils.cpp
 *
 *  Created on: 2020年6月27日
 *      Author: pengzc
 */

#include "utils.h"
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string>
#include <vector>

std::vector<std::string> read_dir(std::string path, std::string prefix, std::vector<std::string>& content, bool recursion) {
  DIR *dir;
  struct dirent *entry;
  struct stat statbuf;
  if ((dir = opendir(path.c_str())) == NULL) {
    //can't open dir
    return content;
  }
  while ((entry = readdir(dir)) != NULL) {
    stat(entry->d_name, &statbuf);
    if ((strcmp(".", entry->d_name) == 0) || (strcmp("..", entry->d_name) == 0)) {
      continue;
    }
    content.push_back(prefix + "/" + entry->d_name);
    if ((S_IFDIR & statbuf.st_mode) && recursion) {
      read_dir(path + "/" + entry->d_name,
          prefix.empty() ? (entry->d_name):(prefix + "/" + entry->d_name),
          content,
          true);
    }
  }
  closedir(dir);
  return content;
}

std::vector<std::string> read_dir(std::string path, bool recursion) {
  std::vector<std::string> content;
  return read_dir(path, path, content, recursion);
}


bool endswith(const std::string& str, const std::string& end) {
  int srclen = str.size();
  int endlen = end.size();
  if(srclen >= endlen) {
    std::string temp = str.substr(srclen - endlen, endlen);
    if(temp == end)
      return true;
  }
  return false;
}

// 查找受支持的音频文件
// 不同系统版本受支持的格式可能不同，但mp3格式基本都可以
std::vector<std::string> find_supported_audio_files(std::vector<std::string> &v) {
  std::vector<std::string> result;
  for (size_t i = 0; i < v.size(); ++i) {
    if (endswith(v.at(i), ".mp3")) {
      result.push_back(v.at(i));
    } else if (endswith(v.at(i), ".wav")) {
      result.push_back(v.at(i));
    }
  }
  return result;
}
