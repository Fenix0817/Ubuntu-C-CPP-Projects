#version 450 core

layout (location=0) in vec2 vertPos;
layout (location=1) in vec2 vertUV;

out vec2 uv;

uniform mat4 matrix;

void main(){
    gl_Position=matrix*vec4(vertPos,0.0,1.0);
    uv=vertUV;
}