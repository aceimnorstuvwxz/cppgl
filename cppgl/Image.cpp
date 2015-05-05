/*
 Copyright (c) 2015 chenbingfeng (iichenbf#gmail.com)

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "Image.h"
#include "SOIL/SOIL.h"
#include <iostream>
#include "inter.h"

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

SPImage Image::create(const std::string &filename)
{
    return SPImage(new Image(filename));
}

void Image::load()
{
    if (_loaded) {
        CLOG("image", _filename, "already been loaded");
        return;
    } else {
        _data = SOIL_load_image(_filename.c_str(), &_width, &_height, 0, SOIL_LOAD_RGBA);
        if (_data == nullptr) {
            CLOG("image", _filename, "load filed:", SOIL_last_result());
        } else {
            _loaded = true;
            CLOG("image", _filename, "loaded width", _width, "height", _height);
        }
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