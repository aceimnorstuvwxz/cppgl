//
//  Framebuffer.h
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/2.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __lua2d_glfw__Framebuffer__
#define __lua2d_glfw__Framebuffer__

#include "utils.h"
#include "GC.h"
#include "Texture.h"

NS_CPPGL_BEGIN

class Texture;

class Framebuffer
{
public:
    Framebuffer(const Framebuffer& other);
    Framebuffer(unsigned int width, unsigned int height, unsigned char color = 32, unsigned char depth = 24);
    ~Framebuffer();

    operator GLuint() const;
    const Framebuffer& operator=(const Framebuffer& other);

    const Texture& getTexture();
    const Texture& getDepthTexture();

private:
    static GC gc; // TODO remove GC, using shared_ptr to wrapping OpenGL object!!!
    GLuint obj;
    Texture texColor;
    Texture texDepth;
};

NS_CPPGL_END

#endif /* defined(__lua2d_glfw__Framebuffer__) */
