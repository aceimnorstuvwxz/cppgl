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

#include "VertexArray.h"

NS_CPPGL_BEGIN

SPVertexArray VertexArray::create()
{
    return SPVertexArray(new VertexArray());
}

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_obj);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &_obj);
}

VertexArray::operator GLuint() const
{
    return _obj;
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

NS_CPPGL_END