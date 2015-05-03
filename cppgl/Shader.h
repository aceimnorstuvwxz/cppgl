//
//  Shader.h
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/3.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __lua2d_glfw__Shader__
#define __lua2d_glfw__Shader__

#include <string>
#include "utils.h"
#include "GC.h"

#define GLSL( x ) "#version 150\n" #x

NS_CPPGL_BEGIN
/*
 Shader type
	*/
namespace ShaderType
{
    enum shader_type_t
    {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Geometry = GL_GEOMETRY_SHADER
    };
}

class Shader
{
public:
    Shader( const Shader& other );
    Shader( ShaderType::shader_type_t type );
    Shader( ShaderType::shader_type_t type, const std::string& code );

    ~Shader();

    operator GLuint() const;
    const Shader& operator=( const Shader& other );

    void source( const std::string& code );
    void compile();

    std::string getInfoLog();

private:
    static GC _gc;
    ShaderType::shader_type_t _type;
    GLuint _obj;
};

NS_CPPGL_END
#endif /* defined(__lua2d_glfw__Shader__) */
