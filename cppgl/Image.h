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

#ifndef __lua2d_glfw__Image__
#define __lua2d_glfw__Image__

#include "utils.h"
#include <string>
#include <memory>

NS_CPPGL_BEGIN

class Image;

typedef std::shared_ptr<Image> SPImage;

class Image
{
public:
    static SPImage create(const std::string& filename);

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

    Image(const std::string& filename);
};


NS_CPPGL_END

#endif /* defined(__lua2d_glfw__Image__) */
