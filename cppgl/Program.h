//
//  Program.h
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/3.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __lua2d_glfw__Program__
#define __lua2d_glfw__Program__

#include "utils.h"
#include "Shader.h"

NS_CPPGL_BEGIN

/*
 Program
	*/
class Program
{
public:
    Program();
    Program( const Program& program );
    Program( const Shader& vertex );
    Program( const Shader& vertex, const Shader& fragment );
    Program( const Shader& vertex, const Shader& fragment, const Shader& geometry );

    ~Program();

    operator GLuint() const;
    const Program& operator=( const Program& other );

    void attach( const Shader& shader );
    void transformFeedbackVaryings( const char** varyings, unsigned int count );
    void link();
    void use();

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
    static GC _gc;
    GLuint _obj;
};


NS_CPPGL_END
#endif /* defined(__lua2d_glfw__Program__) */
