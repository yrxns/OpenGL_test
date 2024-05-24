# OpenGL

https://learnopengl-cn.github.io/

https://github.com/parallel101/opengltutor

https://docs.gl/

https://threejs.org/

https://github.com/ocornut/imgui

https://github.com/yocover/start-learning-opengl

##### 编译安装

[glfw](https://www.glfw.org/)

### assimp

[编译指南](https://github.com/assimp/assimp/blob/master/Build.md)

检查 CMakeLists.txt 中的`ASSIMP_BUILD_ZLIB` 选项是否开启，  ON

```shell
mkdir build && cd build
cmake ..
make -j9
```

获取 libassimp.a 和 libzlibstatic.a

```c++
target_link_libraries(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/libassimp.a)
target_link_libraries(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/libzlibstatic.a)
```



OpenGL仅当3D坐标在3个轴（x、y和z）上-1.0到1.0的范围内时才处理它。
所有在这个范围内的坐标叫做标准化设备坐标，此范围内的坐标最终显示在屏幕上。

一旦你的顶点坐标已经在顶点着色器中处理过，它们就应该是标准化设备坐标了，
标准化设备坐标是一个x、y和z值在-1.0到1.0的一小段空间。任何落在范围外的坐标都会被丢弃/裁剪，不会显示在你的屏幕上。


### 曲率运动

```c++
float rotate = glfwGetTime() * 0.2f;
glm::qua<float> qu = glm::qua<float>(glm::vec3(rotate, rotate, rotate));
model = glm::mat4_cast(qu);
```

开启模板缓冲

```c++
glEnable(GL_STENCIL_TEST);
```

清除模板缓冲

```c++
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
```

模板掩码

```c++
glStencilMask(0xFF); // 每一位写入模板缓冲时都保持原样
glStencilMask(0x00); // 每一位在写入模板缓冲时都会变成0（禁用写入）
```

模板函数

```c++
glStencilFunc(GLenum func, GLint ref, GLuint mask)
glStencilOp(GLenum sfail, GLenum dpfail, GLenum dppass)
```

