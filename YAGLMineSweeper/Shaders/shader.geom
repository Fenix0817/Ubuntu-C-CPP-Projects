#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices=6) out;

out vec2 uv;

//Grid position
uniform float tileX;
uniform float tileY;
uniform float gridW;
uniform float gridH;

//Sprite settings
uniform float spriteX;//coord in spritesheet
uniform float spriteY;//coord in spritesheet
uniform float spriteW;//size in spritesheet
uniform float spriteH;//size in spritesheet
uniform float sheetW;//size of spritesheet
uniform float sheetH;//size of spritesheet

vec2 gridToWorld(vec2 v){
	return v/vec2(gridW,gridH);
}

vec2 uvToSprite(vec2 v){
	v*=vec2(spriteW,spriteH);
	v+=vec2(spriteX,spriteY);
	v/=vec2(sheetW,sheetH);
	return v;
}

vec2 spriteToWorld(vec2 v){
	return v/vec2(spriteW,spriteH);
}

void emit(float x,float y){
	float gx=tileX+x;
	float gy=tileY+y;
	uv=uvToSprite(vec2(x,y));
	gl_Position=vec4(gridToWorld(vec2(gx,gy))*2.0-1.0,0.0,1.0);
	EmitVertex();
}

void end(){
	EndPrimitive();
}

void main(){
	emit(0.0,0.0);
	emit(1.0,0.0);
	emit(0.0,1.0);
	end();

	emit(1.0,0.0);
	emit(0.0,1.0);
	emit(1.0,1.0);
	end();
}