#version 330 core
out vec4 FragColor;
in vec2 outTexCoord;
in vec3 outNormal;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    if(gl_FragCoord.x < 400)
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    else
        FragColor = vec4(0.0, 1.0, 0.0, 1.0);  
}