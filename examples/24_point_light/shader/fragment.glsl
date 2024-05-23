#version 330 core
out vec4 FragColor;
in vec2 outTexCoord;
in vec3 outNormal;
in vec3 outFragPos;

// 定义材质结构体
struct Material {
  sampler2D diffuse; // 漫反射贴图
  sampler2D specular; // 镜面光贴图
  float shininess; // 高光指数
};

// 光源属性
struct Light {
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float constant; // 常数项
  float linear; // 一次项
  float quadratic; // 二次项
};

uniform vec3 viewPos; // 相机位置
uniform Material material;
uniform Light light;

void main() {

  // ambient
  vec3 ambient = light.ambient * texture(material.diffuse, outTexCoord).rgb;

  // diffuse
  vec3 norm = normalize(outNormal);
  vec3 lightDir = normalize(light.position - outFragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.diffuse * diff * texture(material.diffuse, outTexCoord).rgb;

  // specular
  vec3 viewDir = normalize(viewPos - outFragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = light.specular * spec * texture(material.specular, outTexCoord).rgb; // 镜面光

  // 计算衰减值
  float distance = length(light.position - outFragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2.0));

  // 将环境光、漫反射、镜面光分别乘以衰减距离
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  vec3 result = ambient + diffuse + specular;
  FragColor = vec4(result, 1.0);
}