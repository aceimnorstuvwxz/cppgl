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

#include "Context.h"
#include <chrono>
#include <thread>

NS_CPPGL_BEGIN

//void activate();
//void setVertifcalSync(bool enabled);

void Context::enable(Capability::capability_t capability)
{
    glEnable(capability);
}

void Context::disable(Capability::capability_t capability)
{
    glDisable(capability);
}

void Context::clearColor(const Color& col)
{
    glClearColor(col.r, col.g, col.b, col.a);
}

void Context::clear(Buffer::buffer_t buffers)
{
    glClear(buffers);
}

void Context::blendFunc(BlendFactor::blend_factor_t sfactor, BlendFactor::blend_factor_t dfactor)
{
    glBlendFunc(sfactor, dfactor);
}

void Context::depthMask(bool writeEnabled)
{
    glDepthMask(writeEnabled);
}

void Context::stencilMask(bool writeEnabled)
{
    glStencilMask(writeEnabled);
}
void Context::stencilMask(unsigned int mask)
{
    glStencilMask(mask);
}

void Context::stencilFunc(TestFunction::test_function_t function, int reference, unsigned int mask)
{
    glStencilFunc(function, reference, mask);
}
void Context::stencilOp(StencilAction::stencil_action_t fail, StencilAction::stencil_action_t zfail, StencilAction::stencil_action_t pass)
{
    glStencilOp(fail, zfail, pass);
}

void Context::useProgram( const SPProgram& program)
{
    assert(program->isLinked());
    glUseProgram(*program);
}

void Context::bindTexture(const SPTexture& texture, unsigned char unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, *texture);
}

void Context::bindFramebuffer( const Framebuffer& framebuffer)
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

    // set viewport to frame buffer size
    GLint obj, width, height;
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &obj);

    GLint res;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &res);
    glBindTexture(GL_TEXTURE_2D, obj);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 9, GL_TEXTURE_HEIGHT, &height);
    glBindTexture(GL_TEXTURE_2D, res);

    glViewport(0, 0, width, height);
}
void Context::bindFramebuffer()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glViewport(_defaultViewport[0], _defaultViewport[1], _defaultViewport[2], _defaultViewport[3]);
}

void Context::beginTransformFeedback( Primitive::primitive_t mode)
{
    glBeginTransformFeedback(mode);
}
void Context::endTransformFeedback()
{
    glEndTransformFeedback();
}

void Context::drawArrays(const VertexArray& vao, Primitive::primitive_t mode, unsigned int offset, unsigned int count)
{
    glBindVertexArray(vao);
    glDrawArrays(mode, offset, count);
}
void Context::drawElements(const VertexArray& vao, Primitive::primitive_t mode, intptr_t offset, unsigned int count, unsigned int type)
{
    glBindVertexArray(vao);
    glDrawElements(mode, count,  type, (const GLvoid*)offset);
}

SPContext Context::Create()
{

//    return std::make_shared<Context>();//? why dont work
    return  std::shared_ptr<Context>(new Context());
}

Context::~Context()
{
}

Context::Context()
{
    // do nothing.
}

NS_CPPGL_END