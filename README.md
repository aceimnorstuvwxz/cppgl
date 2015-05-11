## cppgl 
a C++ wrapper for modern OpenGL

#####Style:

```c++
auto context = Context::Create();
SPShader vert = Shader::create(ShaderType::Vertex, vertexSource);
auto freg = Shader::create(ShaderType::Fragment, fragmentSource);
auto program = Program::create(vert, freg);
context->useProgram(program);

auto texture = Texture::create(image, InternalFormat::RGBA);
texture->setWrapping(Wrapping::Repeat, Wrapping::Repeat);
texture->setFilters(Filter::Linear, Filter::Linear);

context->bindTexture(texture, 0);
SPVertexBuffer vbo = VertexBuffer::create(vertices, sizeof(vertices), BufferUsage::StaticDraw);
SPVertexArray vao = VertexArray::create();
vao->bindAttribute(program->getAttribute("position"), *vbo, Type::Float, 2, 4*sizeof(float), NULL);
vao->bindAttribute(program->getAttribute("texcoord"), *vbo, Type::Float, 2, 4*sizeof(float), 2*sizeof(float));
    
```

#####[Example](https://github.com/iichenbf/cppgl/blob/master/cppgl/cppgl.cpp):

![](./cppgl_test_result.png)

#####A more complex example in [Lua2d](https://github.com/iichenbf/lua2d):
![](./mesh.png)


#####Changes:

- 20150504 use shared_ptr<> instead of GC.
- 20150512 add mesh support.

#####TODO:

- add EBO