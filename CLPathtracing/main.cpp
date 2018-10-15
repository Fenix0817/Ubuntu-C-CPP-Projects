/*
 * main.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: jack
 */

#include <CL/cl.hpp>
#include <fstream>
#include <string>

#include "ppm.h"

//https://stackoverflow.com/a/2912614/9609025
std::string loadFile(std::string fn){
	std::ifstream ifs(fn);
	  std::string content( (std::istreambuf_iterator<char>(ifs) ),
	                       (std::istreambuf_iterator<char>()    ) );
	  return content;
}

const int IMG_W=500;
const int IMG_H=500;

struct Sphere {
	cl_float radius;
	cl_float3 pos;
};

struct Plane {
	cl_float3 pos;
	cl_float3 normal;
};

int main(){
	printf("Starting\n");
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	cl::Platform platform=platforms[0];

	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_GPU,&devices);

	cl::Device device=devices[0]; // First GPU

	std::vector<cl::Device> usedDevices;
	usedDevices.push_back(device);

	cl::Context context(usedDevices);

	std::string code=loadFile("kernel.cl");

	cl::Program::Sources sources;
	sources.push_back({code.c_str(),code.length()});

	cl::Program program(context,sources);

	printf("About to build\n");

	if(program.build({device})!=CL_SUCCESS){
		printf("ERROR!!\n");
		printf("%s\n",program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device).c_str());
	}

	printf("Built\n");

	printf("Initializing Command Queue\n");
	cl::CommandQueue cq(context,device);

	std::vector<Sphere>spheres;
	std::vector<Plane>planes;

	spheres.push_back((Sphere){ 1,{0,0,0} } );
	planes.push_back((Plane){ {0,0,0},  {0,1,0} });

	cl::Buffer bufferSpheres(context,CL_MEM_READ_WRITE,spheres.size());
	cl::Buffer bufferPlanes(context,CL_MEM_READ_WRITE,planes.size());

	cq.enqueueWriteBuffer(bufferSpheres,CL_TRUE,0,spheres.size(),spheres.data());
	cq.enqueueWriteBuffer(bufferPlanes,CL_TRUE,0,planes.size(),planes.data());
	cq.flush();

	printf("Objects written\n");

	cl::Buffer bufferR(context,CL_MEM_READ_WRITE,sizeof(float)*IMG_W*IMG_H);
	cl::Buffer bufferG(context,CL_MEM_READ_WRITE,sizeof(float)*IMG_W*IMG_H);
	cl::Buffer bufferB(context,CL_MEM_READ_WRITE,sizeof(float)*IMG_W*IMG_H);

	float *arrayR=(float*)malloc(sizeof(float)*IMG_W*IMG_H);
	float *arrayG=(float*)malloc(sizeof(float)*IMG_W*IMG_H);
	float *arrayB=(float*)malloc(sizeof(float)*IMG_W*IMG_H);

	for(int i=0;i<IMG_W*IMG_H;i++){
		arrayR[i]=0;
		arrayG[i]=0;
		arrayB[i]=0;
	}

	cq.enqueueWriteBuffer(bufferR,CL_TRUE,0,sizeof(float)*IMG_W*IMG_H,arrayR);
	cq.enqueueWriteBuffer(bufferG,CL_TRUE,0,sizeof(float)*IMG_W*IMG_H,arrayG);
	cq.enqueueWriteBuffer(bufferB,CL_TRUE,0,sizeof(float)*IMG_W*IMG_H,arrayB);
	cq.flush();

	printf("Buffers written\n");

	cl::Kernel kernel(program,"createImage");
	kernel.setArg(0,IMG_W);
	kernel.setArg(1,IMG_H);
	kernel.setArg(2,bufferR);
	kernel.setArg(3,bufferG);
	kernel.setArg(4,bufferB);
	kernel.setArg(5,bufferSpheres);
	kernel.setArg(6,bufferPlanes);
	kernel.setArg(7,spheres.size());
	kernel.setArg(8,planes.size());

	cq.enqueueNDRangeKernel(kernel,cl::NullRange,cl::NDRange(IMG_W,IMG_H));
	cq.flush();

	printf("Kernel ran\n");

	cq.enqueueReadBuffer(bufferR,CL_TRUE,0,sizeof(float)*IMG_W*IMG_H,arrayR);
	cq.enqueueReadBuffer(bufferG,CL_TRUE,0,sizeof(float)*IMG_W*IMG_H,arrayG);
	cq.enqueueReadBuffer(bufferB,CL_TRUE,0,sizeof(float)*IMG_W*IMG_H,arrayB);
	cq.flush();

	printf("Buffers read\n");

	ppm img;
	img.setSize(IMG_W,IMG_H);
	img.allocMem();

//	img.rComp=arrayR;
//	img.gComp=arrayG;
//	img.bComp=arrayB;

	for(int x=0;x<IMG_W;x++){
		for(int y=0;y<IMG_H;y++){
			int i=img.getInd(x,y);
			img.setPixel(x,y,arrayR[i],arrayG[i],arrayB[i]);
		}
	}

	img.clamp();
	img.save("pathtraced.ppm");
	img.dealloc();

	printf("Image written\n");

	delete[] arrayR;
	delete[] arrayG;
	delete[] arrayB;

	return 0;
}
