//
//  Framebuffer.cpp
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/2.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Framebuffer.h"

#define PUSH_STATE() GLint restoreId; glGetIntegerv( GL_DRAW_FRAMEBUFFER_BINDING, &restoreId )
#define POP_STATE() glBindFramebuffer( GL_DRAW_FRAMEBUFFER, restoreId )

NS_CPPGL_BEGIN

Framebuffer::Framebuffer(const Framebuffer& other)
{
    gc.copy(other.obj, obj);
    texColor = other.texColor;
    texDepth = other.texDepth;
}

Framebuffer::Framebuffer(unsigned int width, unsigned int height, unsigned char color, unsigned char depth)
{
    // Fix me, use enumation instead
    assert(color == 24 || color == 32);
    assert(depth == 8 || depth == 16 || depth == 24 || depth == 32);

    // prevent the side effect of thie construction
    PUSH_STATE();

    // determine appropriate formats
    InternalFormat::internal_format_t colorFormat;
    colorFormat = color == 24 ? InternalFormat::RGB : InternalFormat::RGBA;

    InternalFormat::internal_format_t depthFormat;
    depthFormat = depth == 8 ? InternalFormat::DepthComponent :
                depth == 16 ? InternalFormat::DepthComponent16 :
                depth == 24 ? InternalFormat::DepthComponent24 : InternalFormat::DepthComponent32F;

    // create FBO
    gc.create(obj, glGenFramebuffers, glDeleteFramebuffers);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, obj);

    // Create texture to hold color buffer
    texColor.image2D( 0, DataType::UnsignedByte, Format::RGBA, width, height, colorFormat );
    texColor.setWrapping( Wrapping::ClampEdge, Wrapping::ClampEdge );
    texColor.setFilters( Filter::Linear, Filter::Linear );
    glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColor, 0 );

    // Create renderbuffer to hold depth buffer
    if ( depth > 0 ) {
        glBindTexture( GL_TEXTURE_2D, texDepth );
        glTexImage2D( GL_TEXTURE_2D, 0, depthFormat, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0 );
        texDepth.setWrapping( Wrapping::ClampEdge, Wrapping::ClampEdge );
        texDepth.setFilters( Filter::Nearest, Filter::Nearest );
        glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texDepth, 0 );
    }

    // Check
    assert(glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE );

    POP_STATE();
}

Framebuffer::~Framebuffer()
{
    gc.destroy(obj);
}

Framebuffer::operator GLuint() const
{
    return obj;
}

const Framebuffer& Framebuffer::operator=(const Framebuffer& other)
{
    gc.copy(other.obj, obj, true);
    texColor = other.texColor;
    texDepth = other.texDepth;

    return *this;
}

const Texture& Framebuffer::getTexture()
{
    return texColor;
}

const Texture& Framebuffer::getDepthTexture()
{
    return texDepth;
}

GC Framebuffer::gc;

NS_CPPGL_END