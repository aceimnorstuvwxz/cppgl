#### cppgl 
:loop:a C++ wrapper for modern OpenGL

#####:loop:[Example code](https://github.com/iichenbf/cppgl/blob/master/cppgl/cppgl.cpp):

![](./cppgl_test_result.png)

```c++
#include "cppgl.h"

#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>


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

    context->clearColor({0.5f, 0.0f, 0.0f, 1.0f});

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

```

#####:loop:Changes:

- 2015-05-04 use shared_ptr<> instead of GC

#####:loop:TODO:

- add EBO
- more tests