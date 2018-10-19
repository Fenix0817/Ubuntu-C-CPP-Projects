/*
 * main.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: jack
 */

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

#include <vector>
#include <stdlib.h>
#include <string.h>

char* concat(const char *s1, const char *s2)
{
    char *result = (char*)malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

#define PRINT_FAIL "Fail"
#define PRINT_SUCCESS "Success"

void errorCheck_res(char*name,VkResult res){
	if(res!=VK_SUCCESS)printf("%s: %s\n",PRINT_FAIL,name);
	else printf("%s: %s\n",PRINT_SUCCESS,name);
}

void errorCheck_bool(char*name,bool b){
	if(!b)printf("%s: %s\n",PRINT_FAIL,name);
	else printf("%s: %s\n",PRINT_SUCCESS,name);
}

void errorCheck_bool(const char*name,bool b){
	if(!b)printf("%s: %s\n",PRINT_FAIL,name);
	else printf("%s: %s\n",PRINT_SUCCESS,name);
}

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr,
			nullptr);

	VkInstance instance;

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	createInfo.enabledLayerCount = 0;

	errorCheck_res("Create instance", vkCreateInstance(&createInfo, nullptr, &instance));

	uint32_t extensionsCount=0;
	errorCheck_res("Get extension count",vkEnumerateInstanceExtensionProperties(nullptr,&extensionsCount,nullptr));

	std::vector<VkExtensionProperties>availableExtensions(extensionsCount);
	errorCheck_res("Get available extensions",vkEnumerateInstanceExtensionProperties(nullptr,&extensionsCount,availableExtensions.data()));

//	printf("Extension count: %i, %i\n",extensionsCount,availableExtensions.size());

	std::vector<const char*>requiredExtensions={
			VK_KHR_SURFACE_EXTENSION_NAME
#if defined(VK_USE_PLATFORM_WIN32_KHR)
			VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#elif defined(VK_USE_PLATFORM_XCB_KHR)
			VK_KHR_XCB_SURFACE_EXTENSION_NAME
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
			VK_KHR_XLIB_SURFACE_EXTENSION_NAME
#endif
	};

	for(int i=0;i<requiredExtensions.size();i++){
		bool available=false;
		for(uint j=0;j<availableExtensions.size();j++){
			if(strcmp(availableExtensions[j].extensionName,requiredExtensions[i]))available=true;
		}
		errorCheck_bool(requiredExtensions[i],available);
	}

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	uint32_t deviceCount = 0;
	errorCheck_res("Get physical device count", vkEnumeratePhysicalDevices(instance,&deviceCount,nullptr));

	std::vector<VkPhysicalDevice>devices(deviceCount);
	errorCheck_res("Get physical devices", vkEnumeratePhysicalDevices(instance,&deviceCount,devices.data()));

	for(int i=0;i<devices.size();i++){
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(devices[i],&properties);

		VkPhysicalDeviceFeatures features;
		vkGetPhysicalDeviceFeatures(devices[i],&features);

		printf("DEVICE %i\n",i+1);
		if(devices[i]==VK_NULL_HANDLE)printf("DEVICE %i is null\n",i+1);

		printf("\tDevice ID: %i\n",properties.deviceID);
		printf("\tVendor ID: %i\n",properties.vendorID);
		printf("\tDevice name: %s\n",properties.deviceName);

		VkPhysicalDeviceType type=properties.deviceType;
		char*strType;
		switch(type){
		case VK_PHYSICAL_DEVICE_TYPE_OTHER: strType="OTHER"; break;
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: strType="INTEGRATED GPU"; break;
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: strType="DISCRETE GPU"; break;
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: strType="VIRTUAL GPU"; break;
		case VK_PHYSICAL_DEVICE_TYPE_CPU: strType="CPU"; break;
		}
		printf("\tDevice type: %s\n",strType);
		printf("\tAPI Version: %i\n",properties.apiVersion);
		printf("\tAPI Version Major: %i\n",VK_VERSION_MAJOR(properties.apiVersion));
		printf("\tAPI Version Minor: %i\n",VK_VERSION_MINOR(properties.apiVersion));
		printf("\tAPI Version Patch: %i\n",VK_VERSION_PATCH(properties.apiVersion));
		printf("\tDriver Version: %i\n",properties.driverVersion);
		printf("\tDriver Version Major: %i\n",VK_VERSION_MAJOR(properties.driverVersion));
		printf("\tDriver Version Minor: %i\n",VK_VERSION_MINOR(properties.driverVersion));
		printf("\tDriver Version Patch: %i\n",VK_VERSION_PATCH(properties.driverVersion));
	}

	physicalDevice=devices[0];

	uint32_t queueFamiliesCount=0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice,&queueFamiliesCount,nullptr);

	std::vector<VkQueueFamilyProperties>queueFamilyProperties(queueFamiliesCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice,&queueFamiliesCount,queueFamilyProperties.data());

	int selectedQueueFamilyIndex=0;
	for(int i=0;i<queueFamiliesCount;i++){
		if(queueFamilyProperties[i].queueCount>0&&(queueFamilyProperties[i].queueFlags&VK_QUEUE_GRAPHICS_BIT)){
			selectedQueueFamilyIndex=i;
		}
	}

	std::vector<float>queuePriorities={1};

	VkDeviceQueueCreateInfo queueCreateInfo = {
			VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			nullptr,
			0,
			selectedQueueFamilyIndex,
			(uint32_t)queuePriorities.size(),
			&queuePriorities[0]
	};

	VkDeviceCreateInfo deviceCreateInfo = {
			VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			nullptr,
			0,
			1,
			&queueCreateInfo,
			0,
			nullptr,
			0,
			nullptr,
			nullptr
	};

	VkDevice device;
	errorCheck_res("Device creation",vkCreateDevice(physicalDevice,&deviceCreateInfo,nullptr,&device));

	VkQueue queue;
	vkGetDeviceQueue(device,selectedQueueFamilyIndex,0,&queue);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	vkDeviceWaitIdle(device);
	vkDestroyDevice(device,nullptr);
	vkDestroyInstance(instance,nullptr);

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
