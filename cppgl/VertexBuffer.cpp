//
//  VertexBuffer.cpp
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/3.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "VertexBuffer.h"

NS_CPPGL_BEGIN

VertexBuffer::VertexBuffer()
{
    _gc.create( _obj, glGenBuffers, glDeleteBuffers );
}

VertexBuffer::VertexBuffer( const VertexBuffer& other )
{
    _gc.copy( other._obj, _obj );
}

VertexBuffer::VertexBuffer( const void* data, size_t length, BufferUsage::buffer_usage_t usage )
{
    _gc.create( _obj, glGenBuffers, glDeleteBuffers );
    this->data(data, length, usage );
}

/*
VertexBuffer::VertexBuffer( const Mesh& mesh, BufferUsage::buffer_usage_t usage, std::function<void ( const Vertex& v, VertexDataBuffer& data )> f )
{
    VertexDataBuffer data;
    const Vertex* vertices = mesh.Vertices();
    uint count = mesh.VertexCount();

    for ( uint i = 0; i < count; i++ )
        f( vertices[i], data );

    gc.Create( obj, glGenBuffers, glDeleteBuffers );
    Data( data.Pointer(), data.Size(), usage );
}*/

VertexBuffer::~VertexBuffer()
{
    _gc.destroy( _obj );
}

VertexBuffer::operator GLuint() const
{
    return _obj;
}

const VertexBuffer& VertexBuffer::operator=( const VertexBuffer& other )
{
    _gc.copy( other._obj, _obj, true );
    return *this;
}

void VertexBuffer::data( const void* data, size_t length, BufferUsage::buffer_usage_t usage )
{
    glBindBuffer( GL_ARRAY_BUFFER, _obj );
    glBufferData( GL_ARRAY_BUFFER, length, data, usage );
}

void VertexBuffer::subData( const void* data, size_t offset, size_t length )
{
    glBindBuffer( GL_ARRAY_BUFFER, _obj );
    glBufferSubData( GL_ARRAY_BUFFER, offset, length, data );
}

void VertexBuffer::getSubData( void* data, size_t offset, size_t length )
{
    glBindBuffer( GL_ARRAY_BUFFER, _obj );
    glGetBufferSubData( GL_ARRAY_BUFFER, offset, length, data );
}

GC VertexBuffer::_gc;

NS_CPPGL_END