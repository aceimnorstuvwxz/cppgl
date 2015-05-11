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

#include "cppgl.h"

#ifdef _WIN32
#include "../GLFW/glfw3.h"
#endif
#ifdef __APPLE__
#include <GLFW/glfw3.h>
#endif

#include <iostream>
#include <chrono>
#include <thread>

NS_CPPGL_BEGIN

static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW error: " << description << std::endl;
}

static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
static GLFWwindow* _glfwWindow;
void makeContext()
{
    // using GLFW to generate window and GL context
    int width = 142;
    int height = 196;
		
    // init glfw window
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()){
        std::cerr << "GLFW init failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _glfwWindow = glfwCreateWindow(width, height, "cppgl_test", NULL, NULL);
    if (!_glfwWindow){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(_glfwWindow);
    glfwSwapInterval(1);

    glfwSetKeyCallback(_glfwWindow, glfw_key_callback);
}

static const char* vertexSource =
"#version 150\n"
"\n"
"in vec2 position;\n"
"in vec2 texcoord;\n"
"out vec2 Texcoord;\n"
"\n"
"\n"
"void main()\n"
"{\n"
"    Texcoord = vec2(texcoord.x, -texcoord.y);\n"
"    gl_Position = vec4(position.x, position.y, 0.0, 1.0);\n"
"}\n";

static const char* fragmentSource =
"#version 150\n"
"\n"
"in vec2 Texcoord;\n"
"\n"
"out vec4 outColor;\n"
"uniform sampler2D tex;\n"
"\n"
"void main()\n"
"{\n"
"    outColor = texture(tex, Texcoord);\n"
"}\n";

void cppgl_test()
{
    makeContext();
#ifdef _WIN32
	auto err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "%d, Error: %s\n", err, glewGetErrorString(err));
	}
#endif
    auto context = Context::Create();
    SPShader vert = Shader::create(ShaderType::Vertex, vertexSource);
    SPShader freg = Shader::create(ShaderType::Fragment, fragmentSource);
    SPProgram program = Program::create(vert, freg);
    context->useProgram(program);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f
    };
    auto image = Image::create("shooting_arrow.png");
    image->load();
    SPTexture texture = Texture::create(image, InternalFormat::RGBA);
    texture->setWrapping(Wrapping::Repeat, Wrapping::Repeat);
    texture->setFilters(Filter::Linear, Filter::Linear);

    context->bindTexture(texture, 0);
    SPVertexBuffer vbo = VertexBuffer::create(vertices, sizeof(vertices), BufferUsage::StaticDraw);
    SPVertexArray vao = VertexArray::create();
    vao->bindAttribute(program->getAttribute("position"), *vbo, Type::Float, 2, 4*sizeof(float), NULL);
    vao->bindAttribute(program->getAttribute("texcoord"), *vbo, Type::Float, 2, 4*sizeof(float), 2*sizeof(float));
    std::chrono::microseconds frameInterval{(long long)(1.0f/60.0f * 1000.0f * 1000.0f)};

    context->clearColor({1.0f, 1.0f, 1.0f, 1.0f});

    context->enable(Capability::Blend);
    context->blendFunc(BlendFactor::SRC_ALPHA, BlendFactor::ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(_glfwWindow))
    {
        auto last = std::chrono::steady_clock::now();
        context->clear();
        context->drawArrays(*vao, Primitive::Triangles, 0, 6);
        glfwSwapBuffers(_glfwWindow);
        glfwPollEvents();

        auto now = std::chrono::steady_clock::now();

        std::this_thread::sleep_for(frameInterval - (now - last));
    }

    glfwDestroyWindow(_glfwWindow);
    glfwTerminate();
}

NS_CPPGL_END