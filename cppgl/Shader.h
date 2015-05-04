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

#ifndef __lua2d_glfw__Shader__
#define __lua2d_glfw__Shader__

#include <memory>

#include <string>
#include "utils.h"

#define GLSL( x ) "#version 150\n" #x

NS_CPPGL_BEGIN

namespace ShaderType
{
    enum shader_type_t
    {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Geometry = GL_GEOMETRY_SHADER
    };
}

class Shader;
typedef std::shared_ptr<Shader> SPShader;

class Shader
{
public:
    static SPShader create(ShaderType::shader_type_t type);
    static SPShader create(ShaderType::shader_type_t type, const std::string& code);

    ~Shader();

    operator GLuint() const;

    void source( const std::string& code );
    void compile();
    bool isCompiled() const;

    std::string getInfoLog();

private:
    ShaderType::shader_type_t _type;
    GLuint _obj;
    bool _compiled = false;

    Shader( ShaderType::shader_type_t type );
    Shader( ShaderType::shader_type_t type, const std::string& code );
};

NS_CPPGL_END
#endif /* defined(__lua2d_glfw__Shader__) */
