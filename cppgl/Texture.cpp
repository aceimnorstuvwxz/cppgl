//
//  Texture.cpp
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/2.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Texture.h"

#define PUSH_STATE() GLint restoreId; glGetIntegerv(GL_TEXTURE_BINDING_2D, &restoreId)
#define POP_STATE() glBindTexture(GL_TEXTURE_2D, restoreId)

NS_CPPGL_BEGIN

Texture::Texture()
{
    _gc.create(_obj, glGenTextures, glDeleteTextures);
}

Texture::Texture(const Texture& other)
{
    _gc.copy(other._obj, _obj);
}

Texture::Texture(const Image& image, InternalFormat::internal_format_t internalFormat)
{
    PUSH_STATE();

    _gc.create(_obj, glGenTextures, glDeleteTextures);
    glBindTexture(GL_TEXTURE_2D, _obj);
    
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image.getWidth(), image.getHeight(), 0, Format::RGBA, DataType::UnsignedByte, image.getData());

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glGenerateMipmap( GL_TEXTURE_2D );

    POP_STATE();
}

Texture::~Texture()
{
    _gc.destroy(_obj);
}

Texture::operator GLuint() const
{
    return _obj;
}

const Texture& Texture::operator=(const Texture& other)
{
    _gc.copy(other._obj, _obj, true);
    return *this;
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

GC Texture::_gc;

NS_CPPGL_END