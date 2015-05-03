//
//  cppgl.cpp
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/2.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "cppgl.h"

#include <GLFW/glfw3.h>
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
    int width = 800;
    int height = 600;

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
    auto context = Context::useExistingContext();
    Shader vert(ShaderType::Vertex, vertexSource);
    Shader freg(ShaderType::Fragment, fragmentSource);
    Program program(vert, freg);

    context.useProgram(program);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f
    };
    Image image{"shooting_arrow.png"};
    image.load();
    Texture texture{image, InternalFormat::RGBA};
    texture.setWrapping(Wrapping::Repeat, Wrapping::Repeat);
    texture.setFilters(Filter::Linear, Filter::Linear);

    context.bindTexture(texture, 0);
    VertexBuffer vbo(vertices, sizeof(vertices), BufferUsage::StaticDraw);
    VertexArray vao;
    vao.bindAttribute(program.getAttribute("position"), vbo, Type::Float, 2, 4*sizeof(float), NULL);
    vao.bindAttribute(program.getAttribute("texcoord"), vbo, Type::Float, 2, 4*sizeof(float), 2*sizeof(float));
    std::chrono::microseconds frameInterval{(long long)(1.0f/60.0f * 1000.0f * 1000.0f)};

    context.clearColor({0.5f, 0.0f, 0.0f, 1.0f});

    context.enable(Capability::Blend);
    context.blendFunc(BlendFactor::SRC_ALPHA, BlendFactor::ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(_glfwWindow))
    {
        auto last = std::chrono::steady_clock::now();
        context.clear();
        context.drawArrays(vao, Primitive::Triangles, 0, 6);
        glfwSwapBuffers(_glfwWindow);
        glfwPollEvents();

        auto now = std::chrono::steady_clock::now();

        std::this_thread::sleep_for(frameInterval - (now - last));
    }

    glfwDestroyWindow(_glfwWindow);
    glfwTerminate();
}

NS_CPPGL_END