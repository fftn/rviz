#ifndef RVIZ_LOG_UTILS_H
#define RVIZ_LOG_UTILS_H
 
#include <stdio.h>
#include <string.h>
 
#define DEBUG // log开关
 
#define __FILENAME__ (strrchr(__FILE__, '/') + 1) // 文件名
 
#ifdef DEBUG
#define LOGD(format, ...) printf("[DEBUG][%s][%s][%d]: " format "\n", __FILENAME__, __FUNCTION__,\
                            __LINE__, ##__VA_ARGS__)
#else
#define LOGD(format, ...)
#endif
#define LOGE(format, ...) printf("[ERROR][%s][%s][%d]: " format "\n", __FILENAME__, __FUNCTION__,\
                            __LINE__, ##__VA_ARGS__)
 
#endif // RVIZ_LOG_UTILS_H
