#version 450 core

in vec2 uv;

uniform sampler2D tex;

out vec4 fragColor;

void main(){
    fragColor=vec4(texture(tex,uv).xyz,1.0);
    if(fragColor.xyz==vec3(1.0))discard;
//    fragColor=vec4(uv,0.0,1.0);
}