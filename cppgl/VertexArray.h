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

#ifndef __lua2d_glfw__VertexArray__
#define __lua2d_glfw__VertexArray__

#include <memory>

#include "utils.h"
#include "VertexBuffer.h"

NS_CPPGL_BEGIN

class VertexArray;
typedef std::shared_ptr<VertexArray> SPVertexArray;

class VertexArray
{
public:
    static SPVertexArray create();

    ~VertexArray();

    operator GLuint() const;

    void bindAttribute( const Attribute& attribute, const VertexBuffer& buffer, Type::type_t type, unsigned int count, unsigned int stride, intptr_t offset );

    void bindElements( const VertexBuffer& elements );

    void bindTransformFeedback( unsigned int index, const VertexBuffer& buffer );

private:
    GLuint _obj;

    VertexArray();
};

NS_CPPGL_END

#endif /* defined(__lua2d_glfw__VertexArray__) */
