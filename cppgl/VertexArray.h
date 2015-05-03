//
//  VertexArray.h
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/3.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __lua2d_glfw__VertexArray__
#define __lua2d_glfw__VertexArray__

#include "utils.h"
#include "GC.h"
#include "VertexBuffer.h"

NS_CPPGL_BEGIN

/*
 Vertex Array Object
	*/
class VertexArray
{
public:
    VertexArray();
    VertexArray( const VertexArray& other );

    ~VertexArray();

    operator GLuint() const;
    const VertexArray& operator=( const VertexArray& other );

    void bindAttribute( const Attribute& attribute, const VertexBuffer& buffer, Type::type_t type, unsigned int count, unsigned int stride, intptr_t offset );

    void bindElements( const VertexBuffer& elements );

    void bindTransformFeedback( unsigned int index, const VertexBuffer& buffer );

private:
    static GC _gc;
    GLuint _obj;
};

NS_CPPGL_END

#endif /* defined(__lua2d_glfw__VertexArray__) */
