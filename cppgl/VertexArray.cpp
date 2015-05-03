//
//  VertexArray.cpp
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/3.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "VertexArray.h"

NS_CPPGL_BEGIN

VertexArray::VertexArray()
{
    _gc.create( _obj, glGenVertexArrays, glDeleteVertexArrays );
}

VertexArray::VertexArray( const VertexArray& other )
{
    _gc.copy( other._obj, _obj );
}

VertexArray::~VertexArray()
{
    _gc.destroy( _obj );
}

VertexArray::operator GLuint() const
{
    return _obj;
}

const VertexArray& VertexArray::operator=( const VertexArray& other )
{
    _gc.copy( other._obj, _obj, true );
    return *this;
}

void VertexArray::bindAttribute( const Attribute& attribute, const VertexBuffer& buffer, Type::type_t type, unsigned int count, unsigned int stride, intptr_t offset )
{
    glBindVertexArray( _obj );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glEnableVertexAttribArray( attribute );
    glVertexAttribPointer( attribute, count, type, GL_FALSE, stride, (const GLvoid*)offset );
}

void VertexArray::bindElements( const VertexBuffer& elements )
{
    glBindVertexArray( _obj );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, elements );
}

void VertexArray::bindTransformFeedback( unsigned int index, const VertexBuffer& buffer )
{
    glBindVertexArray( _obj );
    glBindBufferBase( GL_TRANSFORM_FEEDBACK_BUFFER, index, buffer );
}

GC VertexArray::_gc;

NS_CPPGL_END