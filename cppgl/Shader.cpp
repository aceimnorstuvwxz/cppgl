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

#include "Shader.h"
#include "inter.h"
#include <iostream>

NS_CPPGL_BEGIN

SPShader Shader::create(ShaderType::shader_type_t type)
{
    return SPShader(new Shader(type));
}

SPShader Shader::create(ShaderType::shader_type_t type, const std::string &code)
{
    return SPShader(new Shader(type, code));
}

Shader::Shader( ShaderType::shader_type_t shader )
{
    _type = shader;
    _obj = glCreateShader(shader);
}

Shader::Shader( ShaderType::shader_type_t shader, const std::string& code ):Shader(shader)
{
    source( code );
    compile();
}

Shader::~Shader()
{
    glDeleteShader(_obj);
}

Shader::operator GLuint() const
{
    return _obj;
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

    if (res != GL_TRUE) {
        CLOG(getInfoLog());
        _compiled = false;
    } else {
        _compiled = true;
    }

    assert(res == GL_TRUE);
}

bool Shader::isCompiled() const
{
    return _compiled;
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

NS_CPPGL_END