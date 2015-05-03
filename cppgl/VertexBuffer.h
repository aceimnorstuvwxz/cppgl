//
//  VertexBuffer.h
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/3.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __lua2d_glfw__VertexBuffer__
#define __lua2d_glfw__VertexBuffer__

#include "utils.h"
#include <vector>
#include "GC.h"

NS_CPPGL_BEGIN

/*
 Buffer usage types
	*/
namespace BufferUsage
{
    enum buffer_usage_t
    {
        StreamDraw = GL_STREAM_DRAW,
        StreamRead = GL_STREAM_READ,
        StreamCopy = GL_STREAM_COPY,
        StaticDraw = GL_STATIC_DRAW,
        StaticRead = GL_STATIC_READ,
        StaticCopy = GL_STATIC_COPY,
        DynamicDraw = GL_DYNAMIC_DRAW,
        DynamicRead = GL_DYNAMIC_READ,
        DynamicCopy = GL_DYNAMIC_COPY
    };
}

/*
 Helper class for building vertex data
	*/
class VertexDataBuffer
{
public:
    void Float( float v ) { Bytes( (uchar*)&v, sizeof( v ) ); }
    void Int8( int8_t v ) { Bytes( (uchar*)&v, sizeof( v ) ); }
    void Int16( int16_t v ) { Bytes( (uchar*)&v, sizeof( v ) ); }
    void Int32( int32_t v ) { Bytes( (uchar*)&v, sizeof( v ) ); }
    void Uint8( uint8_t v ) { Bytes( (uchar*)&v, sizeof( v ) ); }
    void Uint16( uint16_t v ) { Bytes( (uchar*)&v, sizeof( v ) ); }
    void Uint32( uint32_t v ) { Bytes( (uchar*)&v, sizeof( v ) ); }

    void Vec2( const glm::vec2& v ) { Bytes( (uchar*)&v, sizeof( v ) ); }
    void Vec3( const glm::vec3& v ) { Bytes( (uchar*)&v, sizeof( v ) ); }
    void Vec4( const glm::vec4& v ) { Bytes( (uchar*)&v, sizeof( v ) ); }

    void* Pointer() { return &data[0]; } //Fixme ???? maybe bug!
    size_t Size() { return data.size(); }

private:
    std::vector<uchar> data;

    void Bytes( uchar* bytes, uint count ) {
        for ( uint i = 0; i < count; i++ )
            data.push_back( bytes[i] );
    }
};

/*
 Vertex Buffer
	*/
class VertexBuffer
{
public:
    VertexBuffer();
    VertexBuffer( const VertexBuffer& other );
    VertexBuffer( const void* data, size_t length, BufferUsage::buffer_usage_t usage );
//    VertexBuffer( const Mesh& mesh, BufferUsage::buffer_usage_t usage, std::function<void ( const Vertex& v, VertexDataBuffer& data )> f ); //support mesh later

    ~VertexBuffer();

    operator GLuint() const;
    const VertexBuffer& operator=( const VertexBuffer& other );

    void data( const void* data, size_t length, BufferUsage::buffer_usage_t usage );
    void subData( const void* data, size_t offset, size_t length );
    
    void getSubData( void* data, size_t offset, size_t length );
    
private:
    static GC _gc;
    GLuint _obj;
};

NS_CPPGL_END
#endif /* defined(__lua2d_glfw__VertexBuffer__) */
