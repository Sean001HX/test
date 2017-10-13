//  字符串格式化输出， 安全版

#ifndef HX_SPRINTF_S_H
#define HX_SPRINTF_S_H

#include <stdio.h>

#define hx_sprintf_s(char_buf, ...)  \
			(_snprintf_s(char_buf, sizeof(char_buf) / sizeof(char_buf[0] - 1, __VA_ARGS__))

#endif  //  HX_SPRINTF_S_H