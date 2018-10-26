/*
 * main.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: jack
 */

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

#include <vector>
#include <stdlib.h>
#include <string>
#include <xcb/xcb.h>

#include "XWindow.h"
#include "VulkanRenderer.h"

int main() {

	XWindow window;

	window.beginSetup();
	window.createWindow(500,500);
	window.setTitle("HelloVulkan + XCB");
	window.endSetup();

	VulkanRenderer vk;

	vk.init();

	window.beginLoop();
	while(window.isLoopRunning()){
		window.beginLoopIteration();
		vk.render();
		window.endLoopIteration();
	}
	vk.end();
	window.endLoop();


	return 0;
}
