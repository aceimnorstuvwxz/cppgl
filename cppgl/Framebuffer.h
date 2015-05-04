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

#ifndef __lua2d_glfw__Framebuffer__
#define __lua2d_glfw__Framebuffer__

#include <memory>

#include "utils.h"
#include "Texture.h"

NS_CPPGL_BEGIN

class Texture;
class Framebuffer;

typedef std::shared_ptr<Framebuffer> SPFramebuffer;

class Framebuffer
{
public:
    static SPFramebuffer create(unsigned int width, unsigned int height, unsigned char color = 32, unsigned char depth = 24);
    ~Framebuffer();

    operator GLuint() const;

    const SPTexture& getTexture();
    const SPTexture& getDepthTexture();

private:
    GLuint _obj;
    SPTexture _texColor;
    SPTexture _texDepth;

    Framebuffer(unsigned int width, unsigned int height, unsigned char color = 32, unsigned char depth = 24);
};

NS_CPPGL_END

#endif /* defined(__lua2d_glfw__Framebuffer__) */
