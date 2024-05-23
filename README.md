# OpenGL

https://learnopengl-cn.github.io/

https://github.com/parallel101/opengltutor

https://docs.gl/

https://threejs.org/

https://github.com/ocornut/imgui

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

### 环境光

```c++
void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);
}
```

### 漫反射
```c++
#version 330 core
out vec4 FragColor;
in vec3 outNormal;//法向量
in vec3 outFragPos; // 片元位置

uniform vec3 lightPos;//光照位置
uniform vec3 viewPos; // 视线方向
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // 环境光常量
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
		
    vec3 norm = normalize(outNormal); // 法向量单位化
    vec3 lightDir = normalize(lightPos - outFragPos); // 片元位置指向光照方向

    float diff = max(dot(norm, lightDir), 0.0); // 漫反射分量
    vec3 diffuse = diff * lightColor; // 漫反射
	
    vec3 result = (ambient + diffuse) * objectColor;
    
    FragColor = vec4(result, 1.0);
}
```

### 镜面光

```c++
#version 330 core
out vec4 FragColor;
in vec2 outTexCoord;
in vec3 outNormal;
in vec3 outFragPos;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos; // 相机位置

uniform float ambientStrength;
uniform float specularStrength;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {

  vec4 objectColor = mix(texture(texture1, outTexCoord), texture(texture2, outTexCoord), 0.1);
  //vec4 objColor = vec4(1.0f, 0.5f, 0.31f, 1.0f);

  vec3 ambient = ambientStrength * lightColor; // 环境光

  vec3 norm = normalize(outNormal);
  vec3 lightDir = normalize(lightPos - outFragPos);

  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor; // 漫反射

  vec3 viewDir = normalize(viewPos - outFragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
  vec3 specular = specularStrength * spec * lightColor; // 镜面光

  vec3 result = (ambient + diffuse + specular) * vec3(objectColor);

  FragColor = vec4(result, 1.0);
}
```

