#version 450 core

out vec4 fragColor;

in vec2 uv;

uniform float margin;

void main(){
	//if(uv.x<margin||uv.x>1.0-margin||uv.y<margin||uv.y>1.0-margin)
		fragColor=vec4(0.0,0.0,0.0,1.0);
	//else discard;
}