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

#ifndef __lua2d_glfw__Context__
#define __lua2d_glfw__Context__

#include <memory>

#include "utils.h"
#include "Program.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Framebuffer.h"

NS_CPPGL_BEGIN

// plain enum will keep things simple
// instead of enum class

/*
 Buffer types
 */
namespace Buffer
{
    enum buffer_t
    {
        Color = GL_COLOR_BUFFER_BIT,
        Depth = GL_DEPTH_BUFFER_BIT,
        Stencil = GL_STENCIL_BUFFER_BIT
    };

    inline buffer_t operator|( buffer_t lft, buffer_t rht )
    {
        return (buffer_t)( (int)lft | (int)rht );
    }
}

/*
 Drawing mode
 */
namespace Primitive
{
    enum primitive_t
    {
        Triangles = GL_TRIANGLES,
        Lines = GL_LINES,
        Points = GL_POINTS,
    };
}

/*
 Capabilities to enable/disable
 */
namespace Capability
{
    enum capability_t
    {
        DepthTest = GL_DEPTH_TEST,
        StencilTest = GL_STENCIL_TEST,
        CullFace = GL_CULL_FACE,
        RasterizerDiscard = GL_RASTERIZER_DISCARD,
        Blend = GL_BLEND
    };
}

namespace BlendFactor {
    enum blend_factor_t
    {
        ZERO = GL_ZERO,
        ONE = GL_ONE,
        SRC_COLOR = GL_SRC_COLOR,
        ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
        DST_COLOR = GL_DST_COLOR,
        ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
        SRC_ALPHA = GL_SRC_ALPHA,
        ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
        DST_ALPHA = GL_DST_ALPHA,
        ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
        CONSTANT_COLOR = GL_CONSTANT_COLOR,
        ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
        CONST_ALPHA = GL_CONSTANT_ALPHA,
        ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
        SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE,
        SRC1_COLOR = GL_SRC1_COLOR,
        ONE_MINUS_SRC1_COLOR = GL_ONE_MINUS_SRC1_COLOR,
        SRC1_ALPHA = GL_SRC1_ALPHA,
        ONE_MINUS_SRC1_ALPHA = GL_ONE_MINUS_SRC1_ALPHA
    };
}

/*
 Stencil test functions
 */
namespace TestFunction
{
    enum test_function_t
    {
        Never = GL_NEVER,
        Less = GL_LESS,
        LessEqual = GL_LEQUAL,
        Greater = GL_GREATER,
        GreaterEqual = GL_GEQUAL,
        Equal = GL_EQUAL,
        NotEqual = GL_NOTEQUAL,
        Always = GL_ALWAYS
    };
}

/*
 Stencil operation
 */
namespace StencilAction
{
    enum stencil_action_t
    {
        Keep = GL_KEEP,
        Zero = GL_ZERO,
        Replace = GL_REPLACE,
        Increase = GL_INCR,
        IncreaseWrap = GL_INCR_WRAP,
        Decrease = GL_DECR,
        DecreaseWrap = GL_DECR_WRAP,
        Invert = GL_INVERT
    };
}

// forward declaration
class Program;
class Texture;
class Framebuffer;
class VertexArray;
class Context;

typedef std::shared_ptr<Context> SPContext;

/*
 OpenGL context
 */
class Context
{
public:
//    void setVertifcalSync(bool enabled);

    void enable(Capability::capability_t capability);
    void disable(Capability::capability_t capability);

    void clearColor(const Color& col);
    void clear(Buffer::buffer_t buffers = Buffer::Color | Buffer::Depth);

    void blendFunc(BlendFactor::blend_factor_t sfactor, BlendFactor::blend_factor_t dfactor);

    void depthMask(bool writeEnabled);
    void stencilMask(bool writeEnabled);
    void stencilMask(unsigned int mask);

    void stencilFunc(TestFunction::test_function_t function, int reference, unsigned int mask = ~0);
    void stencilOp(StencilAction::stencil_action_t fail, StencilAction::stencil_action_t zfail, StencilAction::stencil_action_t pass);

    void useProgram( const SPProgram& program);

    void bindTexture(const SPTexture& texture, unsigned char unit);

    void bindFramebuffer( const Framebuffer& framebuffer);
    void bindFramebuffer();

    void beginTransformFeedback( Primitive::primitive_t mode);
    void endTransformFeedback();

    void drawArrays(const VertexArray& vao, Primitive::primitive_t mode, unsigned int offset, unsigned int count);
    void drawElements(const VertexArray& vao, Primitive::primitive_t mode, intptr_t offset, unsigned int count, unsigned int type);

    /*
     CPPGL always use a existing context.

     Please create the window and OpenGL context by your self,
     and the context version >= 3.2, you can use GLFW to do it.
     */
    static SPContext Create();

    ~Context();
private:
    Context();

//    Context(unsigned char color, unsigned char depth, unsigned char stencil, unsigned int antialias);
//    bool owned;
    GLint _defaultViewport[4];
};

NS_CPPGL_END

#endif /* defined(__lua2d_glfw__Context__) */
