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

#include "Framebuffer.h"

#define PUSH_STATE() GLint restoreId; glGetIntegerv( GL_DRAW_FRAMEBUFFER_BINDING, &restoreId )
#define POP_STATE() glBindFramebuffer( GL_DRAW_FRAMEBUFFER, restoreId )

NS_CPPGL_BEGIN

SPFramebuffer Framebuffer::create(unsigned int width, unsigned int height, unsigned char color, unsigned char depth)
{
    return SPFramebuffer(new Framebuffer(width, height, color, depth));
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

    _texColor = Texture::create();
    _texDepth = Texture::create();

    // create FBO
    glGenFramebuffers(1, &_obj);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _obj);

    // Create texture to hold color buffer
    _texColor->image2D( 0, DataType::UnsignedByte, Format::RGBA, width, height, colorFormat );
    _texColor->setWrapping( Wrapping::ClampEdge, Wrapping::ClampEdge );
    _texColor->setFilters( Filter::Linear, Filter::Linear );
    glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *_texColor, 0 );

    // Create renderbuffer to hold depth buffer
    if ( depth > 0 ) {
        glBindTexture( GL_TEXTURE_2D, *_texDepth );
        glTexImage2D( GL_TEXTURE_2D, 0, depthFormat, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0 );
        _texDepth->setWrapping( Wrapping::ClampEdge, Wrapping::ClampEdge );
        _texDepth->setFilters( Filter::Nearest, Filter::Nearest );
        glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *_texDepth, 0 );
    }

    // Check
    assert(glCheckFramebufferStatus( GL_DRAW_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE );

    POP_STATE();
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &_obj);
}

Framebuffer::operator GLuint() const
{
    return _obj;
}

const SPTexture& Framebuffer::getTexture()
{
    return _texColor;
}

const SPTexture& Framebuffer::getDepthTexture()
{
    return _texDepth;
}

NS_CPPGL_END