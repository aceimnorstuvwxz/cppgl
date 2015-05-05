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

#include "Program.h"
#include "inter.h"

#define COUNT_MAX 16

NS_CPPGL_BEGIN

SPProgram Program::create()
{
    return SPProgram(new Program());
}

SPProgram Program::create(const SPShader vertex)
{
    return SPProgram(new Program(vertex));
}

SPProgram Program::create(const SPShader vertex, const SPShader fragment)
{
    return SPProgram(new Program(vertex, fragment));
}

SPProgram Program::create(const SPShader vertex, const SPShader fragment, const SPShader geometry)
{
    return SPProgram(new Program(vertex, fragment, geometry));
}

Program::Program()
{
    _obj = glCreateProgram();
}

Program::Program( const SPShader vertex ):Program()
{
    attach(vertex);
    link();
}

Program::Program( const SPShader vertex, const SPShader fragment ):Program()
{
    attach(vertex);
    attach(fragment);
    link();
}

Program::Program( const SPShader vertex, const SPShader fragment, const SPShader geometry ):Program()
{
    attach(vertex);
    attach(fragment);
    attach(geometry);
    link();
}

Program::~Program()
{
    glDeleteProgram(_obj);
}

Program::operator GLuint() const
{
    return _obj;
}

void Program::attach( const SPShader shader )
{
    glAttachShader( _obj, *shader );
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

    if (res != GL_TRUE) {
        CLOG("link failed, ", getInfoLog());
        _linked = false;
    } else {
        _linked = true;
    }

    assert(res == GL_TRUE);
}

bool Program::isLinked() const
{
    return _linked;
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

NS_CPPGL_END