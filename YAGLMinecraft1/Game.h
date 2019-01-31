/*
 * Game.h
 *
 *  Created on: Nov 24, 2018
 *      Author: jack
 */

#ifndef GAME_H_
#define GAME_H_

//#include "GL/glu.h"
#include "Window.h"
#include "Utilities.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include <vector>
#include "Block.h"
#include "TexturePos.h"
#include "Atlas.h"
#include "AtlasPos.h"
#include "AtlasHD.h"
#include "AtlasLow.h"
#include "AtlasNormal.h"
#include "AtlasFogleman.h"
#include "AtlasMCSimple.h"
#include "Chunk.h"
#include "ChunkManager.h"
#include "SelectedBlock.h"
//#include "TextAtlas.h"
//#include "TextAtlasMonospaced.h"
//#include "TextRenderer.h"
#include "Crosshair.h"
#include <signal.h>

#include <utility>

#include "FastNoise.h"

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "utils.h"

class Game {
public:
	Game();
	virtual ~Game();

	float lastJumpTime=0;

	FastNoisePtr noise;

	AtlasPtr atlas;

	ChunkManager chunkManager;


	float prevTime = 0;
	float time = 0;

	int frames = 0;

	float fogR = 0.8;
	float fogG = 0.8;
	float fogB = 0.9;

//	TextAtlas*textAtlas;

	Camera camera;

	gl::Texture texture;
	gl::Shader shader;

//	TextRenderer txtRenderer;

	SelectedBlock selectedBlock;
	Crosshair crosshair;

	void init();
	void loop(gl::Window window);
};

#endif /* GAME_H_ */
