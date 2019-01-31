/*
 * WorldGeneratorBasic.cpp
 *
 *  Created on: Jan 31, 2019
 *      Author: jack
 */

#include "WorldGeneratorBasic.h"

WorldGeneratorBasic::WorldGeneratorBasic() {
	// TODO Auto-generated constructor stub

}

WorldGeneratorBasic::~WorldGeneratorBasic() {
	// TODO Auto-generated destructor stub
}

void WorldGeneratorBasic::init(){
	zoom=1;
	fn=new FastNoise();
	fn->SetFractalOctaves(1);
	fn->SetFractalLacunarity(10);
	fn->SetFractalGain(0.1f);
	fn->SetFractalType(FractalTypeFBM);
}

void WorldGeneratorBasic::generateData(int ox,int oz,Block data[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE]){

//	for(int i=x;i<x+CHUNK_SIZE;i++){
//		for(int k=z;k<z+CHUNK_SIZE;k++){
//
//			float fh=CHUNK_HEIGHT/2+20*fn->GetSimplexFractal( zoom*i,zoom*k);
//			int h=(int)fh;
//
//			for(int j=0;j<CHUNK_HEIGHT;j++){
//				if(j<h-10)data[i][j][k]=blockStone;
//				else if(y<h)data[i][j][k]=blockDirt;
//				else if(y==h){
//					data[i][j][k]=blockGrass;
//				}
//				else data[i][j][k]=blockEmpty;
//			}
//
//		}
//	}

	for(int i=0;i<CHUNK_SIZE;i++){
		int x=i+ox;
		for(int k=0;k<CHUNK_SIZE;k++){
			int z=k+oz;

			float fh=CHUNK_HEIGHT/2+20*fn->GetSimplexFractal(zoom*x,zoom*z);
			int h=(int)fh;

			for(int j=0;j<CHUNK_HEIGHT;j++){
				if(j<h-10)data[i][j][k]=blockStone;
				else if(j<h)data[i][j][k]=blockDirt;
				else if(j==h)data[i][j][k]=blockGrass;
				else data[i][j][k]=blockEmpty;
			}

		}
	}

}

