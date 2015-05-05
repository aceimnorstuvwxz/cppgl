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

#ifndef __lua2d_glfw__Program__
#define __lua2d_glfw__Program__

#include <memory>

#include "utils.h"
#include "Shader.h"

NS_CPPGL_BEGIN

class Program;
typedef std::shared_ptr<Program> SPProgram;

class Program
{
public:
    static SPProgram create();
    static SPProgram create(const SPShader vertex);
    static SPProgram create(const SPShader vertex, const SPShader fragment);
    static SPProgram create(const SPShader vertex, const SPShader fragment, const SPShader geometry);

    ~Program();

    operator GLuint() const;

    void attach( const SPShader shader );
    void transformFeedbackVaryings( const char** varyings, unsigned int count );
    void link();
    bool isLinked() const;

    std::string getInfoLog();

    Attribute getAttribute( const std::string& name );
    Uniform getUniform( const std::string& name );

    void setUniform( const Uniform& uniform, int value );
    void setUniform( const Uniform& uniform, float value );
    void setUniform( const Uniform& uniform, const glm::vec2& value );
    void setUniform( const Uniform& uniform, const glm::vec3& value );
    void setUniform( const Uniform& uniform, const glm::vec4& value );
    void setUniform( const Uniform& uniform, const float* values, unsigned int count );
    void setUniform( const Uniform& uniform, const glm::vec2* values, unsigned int count );
    void setUniform( const Uniform& uniform, const glm::vec3* values, unsigned int count );
    void setUniform( const Uniform& uniform, const glm::vec4* values, unsigned int count );
    void setUniform( const Uniform& uniform, const glm::mat3& value );
    void setUniform( const Uniform& uniform, const glm::mat4& value );

    template <typename T>
    void setUniform( const std::string& name, const T& value )
    {
        setUniform( getUniform( name ), value );
    }

    template <typename T>
    void setUniform( const std::string& name, const T* values, unsigned int count)
    {
        setUniform( getUniform(name), values, count );
    }

private:
    GLuint _obj;

    Program();
    Program( const SPShader vertex );
    Program( const SPShader vertex, const SPShader fragment );
    Program( const SPShader vertex, const SPShader fragment, const SPShader geometry );

    bool _linked = false;
};


NS_CPPGL_END
#endif /* defined(__lua2d_glfw__Program__) */
