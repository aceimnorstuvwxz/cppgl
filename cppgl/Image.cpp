//
//  Image.cpp
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/3.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Image.h"
#include "SOIL/SOIL.h"
#include <iostream>

NS_CPPGL_BEGIN

Image::Image(const std::string& filename):_filename(filename)
{
    // do nothing.
}

Image::~Image()
{
    if (_loaded) {
        SOIL_free_image_data(_data);
    }
}

void Image::load()
{
    if (_loaded) {
        //TODO log
        return;
    } else {
        _data = SOIL_load_image(_filename.c_str(), &_width, &_height, 0, SOIL_LOAD_RGBA);
//        auto p = _data;
//        p += 3;
//        for(int i = 0; i < _width * _height; i++) {
//            std::cout << (int)(*p)<<" ";
//            p += 4;
//        }
        _loaded = true;
    }
}

int Image::getWidth() const
{
    return _width;
}
int Image::getHeight() const
{
    return _height;
}

const unsigned char* Image::getData() const
{
    return _data;
}


NS_CPPGL_END