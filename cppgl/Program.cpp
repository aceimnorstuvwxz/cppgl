//
//  Program.cpp
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/3.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Program.h"
#define COUNT_MAX 16

NS_CPPGL_BEGIN
Program::Program()
{
    _obj = _gc.create( glCreateProgram(), glDeleteProgram );
}

Program::Program( const Program& other )
{
    _gc.copy( other._obj, _obj );
}

Program::Program( const Shader& vertex )
{
    _obj = _gc.create( glCreateProgram(), glDeleteProgram );
    attach( vertex );
    link();
//    glUseProgram( _obj ); // call program.use() to use, so multiple shader-program is supported.
}

Program::Program( const Shader& vertex, const Shader& fragment )
{
    _obj = _gc.create( glCreateProgram(), glDeleteProgram );
    attach( vertex );
    attach( fragment );
    link();
//    glUseProgram( _obj );
}

Program::Program( const Shader& vertex, const Shader& fragment, const Shader& geometry )
{
    _obj = _gc.create( glCreateProgram(), glDeleteProgram );
    attach( vertex );
    attach( fragment );
    attach( geometry );
    link();
//    glUseProgram( obj );
}

Program::~Program()
{
    _gc.destroy( _obj );
}

Program::operator GLuint() const
{
    return _obj;
}

const Program& Program::operator=( const Program& other )
{
    _gc.copy( other._obj, _obj, true );
    return *this;
}

void Program::attach( const Shader& shader )
{
    glAttachShader( _obj, shader );
}

void Program::transformFeedbackVaryings( const char** varyings, unsigned int count )
{
    glTransformFeedbackVaryings( _obj, count, varyings, GL_INTERLEAVED_ATTRIBS );
}

void Program::link()
{
    GLint res;

    glLinkProgram( _obj );
    glGetProgramiv( _obj, GL_LINK_STATUS, &res );

    assert(res == GL_TRUE);
}

std::string Program::getInfoLog()
{
    GLint res;
    glGetProgramiv( _obj, GL_INFO_LOG_LENGTH, &res );

    if ( res > 0 )
    {
        std::string infoLog( res, 0 );
        glGetProgramInfoLog( _obj, res, &res, &infoLog[0] );
        return infoLog;
    } else {
        return "";
    }
}

Attribute Program::getAttribute( const std::string& name )
{
    return glGetAttribLocation( _obj, name.c_str() );
}

Uniform Program::getUniform( const std::string& name )
{
    return glGetUniformLocation( _obj, name.c_str() );
}

void Program::setUniform( const Uniform& uniform, int value )
{
    glUniform1i( uniform, value );
}

void Program::setUniform( const Uniform& uniform, float value )
{
    glUniform1f( uniform, value );
}

void Program::setUniform( const Uniform& uniform, const glm::vec2& value )
{
    glUniform2f( uniform, value.x, value.y);
}

void Program::setUniform( const Uniform& uniform, const glm::vec3& value )
{
    glUniform3f( uniform, value.x, value.y, value.z );
}

void Program::setUniform( const Uniform& uniform, const glm::vec4& value )
{
    glUniform4f( uniform, value.x, value.y, value.z, value.w );
}

void Program::setUniform( const Uniform& uniform, const float* values, unsigned int count )
{
    glUniform1fv( uniform, count, values );
}

void Program::setUniform( const Uniform& uniform, const glm::vec2* values, unsigned int count )
{
    //Fixme: found a better way!
    assert(count < COUNT_MAX);
    float buffer[COUNT_MAX*2];
    for(int i = 0; i < count; i++) {
        buffer[2*i] = values[i].x;
        buffer[2*i + 1] = values[i].y;
    }
    glUniform2fv( uniform, count, buffer);
}

void Program::setUniform( const Uniform& uniform, const glm::vec3* values, unsigned int count )
{
    assert(count < COUNT_MAX);
    float buffer[COUNT_MAX*3];
    for(int i = 0; i < count; i++) {
        buffer[3*i] = values[i].x;
        buffer[3*i + 1] = values[i].y;
        buffer[3*i + 2] = values[i].z;
    }
    glUniform3fv( uniform, count, buffer );
}

void Program::setUniform( const Uniform& uniform, const glm::vec4* values, unsigned int count )
{
    assert(count < COUNT_MAX);
    float buffer[COUNT_MAX*4];
    for (int i = 0; i < count; ++i) {
        buffer[4*i] = values[i].x;
        buffer[4*i + 1] = values[i].y;
        buffer[4*i + 2] = values[i].z;
        buffer[4*i + 3] = values[i].w;
    }
    glUniform4fv( uniform, count, buffer);
}

void Program::setUniform( const Uniform& uniform, const glm::mat3& value )
{
    glUniformMatrix3fv( uniform, 1, GL_FALSE, glm::value_ptr(value) );
}

void Program::setUniform( const Uniform& uniform, const glm::mat4& value )
{
    glUniformMatrix4fv( uniform, 1, GL_FALSE, glm::value_ptr(value) );
}

GC Program::_gc;

NS_CPPGL_END