//
//  Image.h
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/3.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __lua2d_glfw__Image__
#define __lua2d_glfw__Image__

#include "utils.h"
#include <string>

NS_CPPGL_BEGIN

class Image
{
public:
    Image(const std::string& filename);

    void load();

    ~Image();

    int getWidth() const;
    int getHeight() const;

    const unsigned char* getData() const;

private:
    const std::string _filename;
    bool _loaded = false;
    int _width = 0;
    int _height = 0;
    unsigned char* _data = nullptr;

    // no copy
    Image(const Image&);
    const Image& operator=(const Image&);
};


NS_CPPGL_END

#endif /* defined(__lua2d_glfw__Image__) */
