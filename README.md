# OpenGL

https://learnopengl-cn.github.io/

https://github.com/parallel101/opengltutor

https://docs.gl/

https://threejs.org/

https://github.com/ocornut/imgui

##### 编译安装

[glfw](https://www.glfw.org/)



OpenGL仅当3D坐标在3个轴（x、y和z）上-1.0到1.0的范围内时才处理它。
所有在这个范围内的坐标叫做标准化设备坐标，此范围内的坐标最终显示在屏幕上。

一旦你的顶点坐标已经在顶点着色器中处理过，它们就应该是标准化设备坐标了，
标准化设备坐标是一个x、y和z值在-1.0到1.0的一小段空间。任何落在范围外的坐标都会被丢弃/裁剪，不会显示在你的屏幕上。


###