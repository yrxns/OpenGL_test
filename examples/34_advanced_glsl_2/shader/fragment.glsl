#version 330 core
out vec4 FragColor;
in vec2 outTexCoord;
in vec3 outNormal;

uniform sampler2D frontTexture;
uniform sampler2D backTexture;

void main() {
    if(gl_FrontFacing)
        FragColor = texture(frontTexture, outTexCoord);
    else
        FragColor = texture(backTexture, outTexCoord); 
}