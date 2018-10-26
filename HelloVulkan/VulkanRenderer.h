/*
 * VulkanRenderer.h
 *
 *  Created on: Oct 23, 2018
 *      Author: jack
 */

#ifndef VULKANRENDERER_H_
#define VULKANRENDERER_H_

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

class VulkanRenderer {
public:
	VulkanRenderer();
	virtual ~VulkanRenderer();

	void init();
	void render();
	void end();

	const char*applicationName;
	const char*engineName;

	VkInstance instance;

	void setApplicationName(std::string an);
	void setEngineName(std::string en);
};

#endif /* VULKANRENDERER_H_ */
