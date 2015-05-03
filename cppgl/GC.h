//
//  GC.h
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/2.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __lua2d_glfw__GC__
#define __lua2d_glfw__GC__

#include <map>
#include <utility>

#include "utils.h"

NS_CPPGL_BEGIN

typedef void ( * createFunc ) ( GLsizei, GLuint* );
typedef void ( * deleteFunc ) ( GLsizei, const GLuint* );
typedef void ( * deleteFunc2 ) ( GLuint );

/*
 OpenGL object garbage collector
 One GC <-> One GL object type.
	*/
class GC
{
public:
    void create( GLuint& obj, createFunc c, deleteFunc d )
    {
        c( 1, &obj );
        refs.insert( std::pair<GLuint, unsigned int>( obj, 1 ) );

        this->d = d;
        this->d2 = 0;
    }

    int create( const GLuint& obj, deleteFunc2 d2 )
    {
        refs.insert( std::pair<GLuint, unsigned int>( obj, 1 ) );

        this->d = 0;
        this->d2 = d2;

        return obj;
    }

    void copy( const GLuint& from, GLuint& to, bool destructive = false )
    {
        if ( destructive )
            destroy( to );

        to = from;
        refs[from]++;
    }

    void destroy( GLuint& obj )
    {
        if ( --refs[obj] == 0 )
        {
            if ( d != 0 ) d( 1, &obj ); else d2( obj );
            refs.erase( obj );
        }
    }

private:
    std::map<GLuint, unsigned int> refs;
    deleteFunc d;
    deleteFunc2 d2;
};
NS_CPPGL_END

#endif /* defined(__lua2d_glfw__GC__) */
