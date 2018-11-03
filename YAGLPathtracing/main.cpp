/*
 * main.cpp
 *
 *  Created on: Oct 27, 2018
 *      Author: jack
 */

#include "Window.h"
#include "Utilities.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include "Shader.h"

#include "utils.h"
#include "Pathtracing.h"
#include <vector>

void setBRDF(gl::Shader shader,BRDF brdf,std::string name){
	if(brdf.type==BRDF_LAMBERTIAN){
		shader.setInt(string_format("%s.type",name.c_str()),BRDF_LAMBERTIAN);
		shader.setFloat(string_format("%s.lambertian_intensity",name.c_str()),brdf.lambertian_intensity);
		shader.setVec3(string_format("%s.lambertian_color",name.c_str()),brdf.lambertian_color);
	}else if(brdf.type==BRDF_GLOSSY_SPECULAR){
		shader.setInt(string_format("%s.type",name.c_str()),BRDF_GLOSSY_SPECULAR);
		shader.setFloat(string_format("%s.glossy_specular_intensity",name.c_str()),brdf.glossy_specular_intensity);
		shader.setVec3(string_format("%s.glossy_specular_color",name.c_str()),brdf.glossy_specular_color);
		shader.setFloat(string_format("%s.glossy_specular_exp",name.c_str()),brdf.glossy_specular_exp);
	}
}

void setMaterial(gl::Shader shader,Material mat,std::string name){
	if(mat.type==MATERIAL_MATTE){
		shader.setInt(string_format("%s.type",name.c_str()),MATERIAL_MATTE);
		setBRDF(shader,mat.matte_ambient,string_format("%s.matte_ambient",name.c_str()));
		setBRDF(shader,mat.matte_diffuse,string_format("%s.matte_diffuse",name.c_str()));
	}else if(mat.type==MATERIAL_PHONG){
		shader.setInt(string_format("%s.type",name.c_str()),MATERIAL_PHONG);
		setBRDF(shader,mat.phong_ambient,string_format("%s.phong_ambient",name.c_str()));
		setBRDF(shader,mat.phong_diffuse,string_format("%s.phong_diffuse",name.c_str()));
		setBRDF(shader,mat.phong_specular,string_format("%s.phong_specular",name.c_str()));
	}
}

int main(){
	gl::init();

	gl::Window window;
	window.create();
	window.setSize(800,800);
	window.setTitle("YAGL Path Tracing");

	float posData[]={
			-1,-1,0,
			-1, 1,0,
			 1, 1,0,
			 1,-1,0
	};

	float uvData[]={
			0,0,
			0,1,
			1,1,
			1,0
	};

	unsigned int triData[]={
			0,1,2,
			0,2,3
	};

	window.bind();

	gl::VertexArray vao;
	vao.create();
	vao.bind();

	gl::VertexBuffer vboPos;
	vboPos.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboPos.setTarget(gl::VertexBufferTarget::Array);
	vboPos.setType(gl::Type::Float);
	vboPos.create();
	vboPos.bind();
	vboPos.setData(sizeof(posData),posData);
	vboPos.addVertexAttrib(0,3,false,3,(const GLvoid*)0);
	vboPos.unbind();

	gl::VertexBuffer vboUV;
	vboUV.setUsage(gl::VertexBufferUsage::StaticDraw);
	vboUV.setTarget(gl::VertexBufferTarget::Array);
	vboUV.setType(gl::Type::Float);
	vboUV.create();
	vboUV.bind();
	vboUV.setData(sizeof(uvData),uvData);
	vboUV.addVertexAttrib(1,2,false,2,(const GLvoid*)0);
	vboUV.unbind();

	gl::VertexBuffer ebo;
	ebo.setUsage(gl::VertexBufferUsage::StaticDraw);
	ebo.setTarget(gl::VertexBufferTarget::ElementArray);
	ebo.setType(gl::Type::UnsignedInt);
	ebo.create();
	ebo.bind();
	ebo.setData(sizeof(triData),triData);
	ebo.unbind();

	vao.unbind();

	gl::Shader shader;
	shader.create();
	shader.attachFile("Shaders/shader.vert",gl::ShaderType::Vertex);
	shader.attachFile("Shaders/shader.frag",gl::ShaderType::Fragment);
	shader.link();

	window.unbind();

	std::vector<Sphere>spheres;
	std::vector<Plane>planes;

	Material matte;
	matte.type=MATERIAL_MATTE;
	matte.matte_ambient.type=BRDF_LAMBERTIAN;
	matte.matte_ambient.lambertian_intensity=0;
	matte.matte_ambient.lambertian_color=glm::vec3(0,0,0);
	matte.matte_diffuse.type=BRDF_LAMBERTIAN;
	matte.matte_diffuse.lambertian_intensity=3;
	matte.matte_diffuse.lambertian_color=glm::vec3(1,1,1);

	Material phong;
	phong.type=MATERIAL_PHONG;
	phong.phong_ambient.type=BRDF_LAMBERTIAN;
	phong.phong_ambient.lambertian_intensity=0;
	phong.phong_ambient.lambertian_color=glm::vec3(0,0,0);
	phong.phong_diffuse.type=BRDF_LAMBERTIAN;
	phong.phong_diffuse.lambertian_intensity=2;
	phong.phong_diffuse.lambertian_color=glm::vec3(1,1,1);
	phong.phong_specular.type=BRDF_GLOSSY_SPECULAR;
	phong.phong_specular.glossy_specular_intensity=1;
	phong.phong_specular.glossy_specular_color=glm::vec3(1,1,1);
	phong.phong_specular.glossy_specular_exp=40;

//	spheres.push_back(Sphere(glm::vec3(0,0,0),1,phong));
//	spheres.push_back(Sphere(glm::vec3(2,0,0),1,phong));
	for(int i=0;i<50;i++){
		float x=((float)rand())/((float)RAND_MAX);
		float y=((float)rand())/((float)RAND_MAX);
		spheres.push_back(Sphere(glm::vec3(x*10-5,0,y*10-5),1,phong));
	}
	planes.push_back(Plane(glm::vec3(0,0,0),glm::vec3(0,1,0),matte));

	float startTime=gl::time();
	int frames=0;
	while(window.isOpen()){
		frames++;
		if(gl::time()-startTime>.3){
			float endTime=gl::time();
			float diffTime=endTime-startTime;

			printf("FPS: %f\n",frames/diffTime);

			frames=0;
			startTime=gl::time();
		}
		window.bind();

		gl::defaultViewport(window);
		gl::setClearColor(1,1,1);
		gl::clearScreen();

		shader.bind();

		shader.setVec2("windowSize",window.width,window.height);

		shader.setInt("numSpheres",spheres.size());
		for(int i=0;i<spheres.size();i++){
			shader.setVec3(string_format("spheres[%i].pos",i),spheres[i].pos);
			shader.setFloat(string_format("spheres[%i].rad",i),spheres[i].rad);

			setMaterial(shader,spheres[i].mat,string_format("sphereMaterials[%i]",i));
		}

		shader.setInt("numPlanes",planes.size());
		for(int i=0;i<planes.size();i++){
			shader.setVec3(string_format("planes[%i].pos",i),planes[i].pos);
			shader.setVec3(string_format("planes[%i].normal",i),planes[i].normal);

			setMaterial(shader,planes[i].mat,string_format("planeMaterials[%i]",i));
		}

		shader.setVec3("camPos",6,4,3);
		shader.setVec3("lookAt",0,-2,0);
		shader.setFloat("zoom",1);

		shader.setVec3("lightPos",3,2,2);

		vao.bind();
		ebo.bind();
		ebo.render();
		ebo.unbind();
		vao.unbind();
		shader.unbind();

		window.updateSize();
		window.unbind();
	}

	gl::end();
}
