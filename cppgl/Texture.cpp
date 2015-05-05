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

#include "Texture.h"

#define PUSH_STATE() GLint restoreId; glGetIntegerv(GL_TEXTURE_BINDING_2D, &restoreId)
#define POP_STATE() glBindTexture(GL_TEXTURE_2D, restoreId)

NS_CPPGL_BEGIN

SPTexture Texture::create()
{
    return SPTexture(new Texture());
}

SPTexture Texture::create(const SPImage image, InternalFormat::internal_format_t format)
{
    return SPTexture(new Texture(image, format));
}

Texture::Texture()
{
    glGenTextures(1, &_obj);
}

Texture::Texture(const SPImage& image, InternalFormat::internal_format_t internalFormat):Texture()
{
    PUSH_STATE();

    glBindTexture(GL_TEXTURE_2D, _obj);
    
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image->getWidth(), image->getHeight(), 0, Format::RGBA, DataType::UnsignedByte, image->getData());

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glGenerateMipmap( GL_TEXTURE_2D );

    POP_STATE();
}

Texture::~Texture()
{
    glDeleteTextures(1, &_obj);
}

Texture::operator GLuint() const
{
    return _obj;
}

void Texture::image2D(const GLvoid *data, DataType::data_type_t type, Format::format_t format, unsigned int width, unsigned int height, InternalFormat::internal_format_t internalFormat)
{
    PUSH_STATE();

    glBindTexture(GL_TEXTURE_2D, _obj);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);

    POP_STATE();
}

void Texture::setWrapping(Wrapping::wrapping_t s)
{
    PUSH_STATE();

    glBindTexture(GL_TEXTURE_2D, _obj);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);

    POP_STATE();
}

void Texture::setWrapping(Wrapping::wrapping_t s, Wrapping::wrapping_t t)
{
    PUSH_STATE();

    glBindTexture( GL_TEXTURE_2D, _obj );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t );

    POP_STATE();
}

void Texture::setWrapping(Wrapping::wrapping_t s, Wrapping::wrapping_t t, Wrapping::wrapping_t r)
{
    PUSH_STATE();

    glBindTexture( GL_TEXTURE_2D, _obj );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, r );

    POP_STATE();
}

void Texture::setFilters(Filter::filter_t min, Filter::filter_t mag)
{
    PUSH_STATE();

    glBindTexture(GL_TEXTURE_2D, _obj);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);

    POP_STATE();
}


void Texture::setBorderColor( const Color& color )
{
    PUSH_STATE();

    glBindTexture( GL_TEXTURE_2D, _obj );
    
    glTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color_ptr(color));

    POP_STATE();
}

void Texture::generateMipmaps()
{
    PUSH_STATE();

    glBindTexture( GL_TEXTURE_2D, _obj );
    glGenerateMipmap( GL_TEXTURE_2D );

    POP_STATE();
}

NS_CPPGL_END