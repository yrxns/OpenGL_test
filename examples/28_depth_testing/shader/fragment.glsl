#version 330 core
out vec4 FragColor;
in vec2 outTexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
  FragColor = texture(texture1, outTexCoord);
}

// #version 330 core
// out vec4 FragColor;
// in vec2 outTexCoord;

// uniform sampler2D texture1;
// uniform sampler2D texture2;

// float near = 0.1; 
// float far  = 100.0; 

// float LinearizeDepth(float depth) 
// {
//     float z = depth * 2.0 - 1.0; // back to NDC 
//     return (2.0 * near * far) / (far + near - z * (far - near));    
// }

// void main() {
//     float depth = LinearizeDepth(gl_FragCoord.z) / far; // 为了演示除以 far
//   FragColor = vec4(vec3(depth), 1.0);
// }