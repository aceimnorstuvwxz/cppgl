//
//  Shader.cpp
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/3.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Shader.h"
#include <iostream>

NS_CPPGL_BEGIN

Shader::Shader( const Shader& other )
{
    _gc.copy(other._obj, _obj);
    _type = other._type;
}

Shader::Shader( ShaderType::shader_type_t shader )
{
    _type = shader;
    _obj = _gc.create( glCreateShader( shader ), glDeleteShader );
}

Shader::Shader( ShaderType::shader_type_t shader, const std::string& code )
{
    _type = shader;
    _obj = _gc.create( glCreateShader( shader ), glDeleteShader );
    source( code );
    compile();
}

Shader::~Shader()
{
    _gc.destroy( _obj );
}

Shader::operator GLuint() const
{
    return _obj;
}

const Shader& Shader::operator=( const Shader& other )
{
    _gc.copy( other._obj, _obj, true );
    return *this;
}

void Shader::source( const std::string& code )
{
    const char* c = code.c_str();
    glShaderSource( _obj, 1, &c, NULL );
}

void Shader::compile()
{
    GLint res;

    glCompileShader( _obj );
    glGetShaderiv( _obj, GL_COMPILE_STATUS, &res );

    std::cout << getInfoLog() << std::endl;

    assert(res == GL_TRUE);
}

std::string Shader::getInfoLog()
{
    GLint res;
    glGetShaderiv( _obj, GL_INFO_LOG_LENGTH, &res );

    std::cout << (_type == ShaderType::Vertex ? "Vertex " :
                  _type == ShaderType::Fragment ? "Fragment " : "Geomentry");


    if ( res > 0 )
    {
        std::string infoLog( res, 0 );
        glGetShaderInfoLog( _obj, res, &res, &infoLog[0] );
        return infoLog;
    } else {
        return "OK!";
    }
}

GC Shader::_gc;

NS_CPPGL_END