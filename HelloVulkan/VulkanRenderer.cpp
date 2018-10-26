/*
 * VulkanRenderer.cpp
 *
 *  Created on: Oct 23, 2018
 *      Author: jack
 */

#include "VulkanRenderer.h"

VulkanRenderer::VulkanRenderer() {
	// TODO Auto-generated constructor stub

}

VulkanRenderer::~VulkanRenderer() {
	// TODO Auto-generated destructor stub
}

void VulkanRenderer::init(){
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = NULL;
	appInfo.pApplicationName = applicationName;
	appInfo.pEngineName = engineName;
	appInfo.apiVersion = VK_MAKE_VERSION(1,0,0);

	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pNext = NULL;
	instanceCreateInfo.flags = 0;
	instanceCreateInfo.pApplicationInfo = &appInfo;

//	std::vector<char*> enabledExtensions;
//
//	instanceCreateInfo.enabledExtensionCount = enabledExtensions.size();
//	instanceCreateInfo.ppEnabledExtensionNames = enabledExtensions.data();
//
//	std::vector<char*> enabledLayers;
//
//	instanceCreateInfo.enabledLayerCount = enabledLayers.size();
//	instanceCreateInfo.ppEnabledLayerNames = enabledLayers.data();

	vkCreateInstance(&instanceCreateInfo,NULL,&instance);


}

void VulkanRenderer::render(){

}

void VulkanRenderer::end(){
	vkDestroyInstance(instance,NULL);
}

void VulkanRenderer::setApplicationName(std::string an){
	applicationName=an.c_str();
}
void VulkanRenderer::setEngineName(std::string en){
	engineName=en.c_str();
}
