//
//  inter.h
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/5.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __lua2d_glfw__inter__
#define __lua2d_glfw__inter__

#include <iostream>
#include "utils.h"

NS_CPPGL_BEGIN

#define CLOG(...) Log(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

inline void LogRecursive(std::ostream& os){}

template<typename T, typename... Args>
void LogRecursive(std::ostream& os, T first, const Args&... rest)
{
    os << first << " ";
    LogRecursive(os, rest...);
}

template<typename... Args>
void Log(const char* file, const char* func, int line, const Args&... args)
{
    //std::cout << file <<":"<< "(" << line << ")"<< func<<": ";
    std::cout << func << "/" << line << ": ";
    LogRecursive(std::cout, args...);
    std::cout << std::endl;
}

NS_CPPGL_END

#endif /* defined(__lua2d_glfw__inter__) */