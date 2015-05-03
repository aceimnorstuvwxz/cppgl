//
//  utils.h
//  common utilities for cppgl
//
//  Created by chenbingfeng on 15/5/2.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __lua2d_glfw__utils__
#define __lua2d_glfw__utils__

#include <stdio.h>

#define NS_CPPGL_BEGIN namespace cppgl {
#define NS_CPPGL_END   }

// use glm as math lib, which is a header only library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// opengl lib is a common
#include <OpenGL/gl3.h>

NS_CPPGL_BEGIN

namespace Type
{
    enum type_t
    {
        Byte = GL_BYTE,
        UnsignedByte = GL_UNSIGNED_BYTE,
        Short = GL_SHORT,
        UnsignedShort = GL_UNSIGNED_SHORT,
        Int = GL_INT,
        UnsignedInt = GL_UNSIGNED_INT,
        Float = GL_FLOAT,
        Double = GL_DOUBLE
    };
}

typedef GLint Attribute;
typedef GLint Uniform;

typedef unsigned int uint;
typedef unsigned char uchar;

typedef glm::vec4 Color;
inline const float* color_ptr(const Color& color)
{
    return glm::value_ptr(color);
}

NS_CPPGL_END

#endif /* defined(__lua2d_glfw__utils__) */
