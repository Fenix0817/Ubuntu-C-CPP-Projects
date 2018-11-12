/*
 * main.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: jack
 */

#include <vulkan/vulkan.hpp>

const char*b2s(bool b){
	if(b)return "true\0";
	return "false\0";
}

const char*deviceTypeToString(vk::PhysicalDeviceType type){
	switch(type){
	case vk::PhysicalDeviceType::eCpu:return "CPU\0";
	case vk::PhysicalDeviceType::eDiscreteGpu:return "Discrete GPU\0";
	case vk::PhysicalDeviceType::eIntegratedGpu:return "Integrated GPU\0";
	case vk::PhysicalDeviceType::eOther:return "Other\0";
	case vk::PhysicalDeviceType::eVirtualGpu:return "Virtual GPU\0";
	}
	return "Unknown\0";
}

int main(){
	try{
	vk::ApplicationInfo appInfo("Hello Vulkan", 1, "Custom Engine", 1, VK_API_VERSION_1_1);
	vk::UniqueInstance instance=vk::createInstanceUnique(vk::InstanceCreateInfo({},&appInfo));
	std::vector<vk::PhysicalDevice>physicalDevices=instance->enumeratePhysicalDevices();
	assert(!physicalDevices.empty());
	for(int i=0;i<physicalDevices.size();i++){
		vk::PhysicalDevice device=physicalDevices[i];
		vk::PhysicalDeviceFeatures features=device.getFeatures();
		vk::PhysicalDeviceProperties props=device.getProperties();
		printf("Device name: %s\n",props.deviceName);
		printf("Device type: %s\n",deviceTypeToString(props.deviceType));
	}
	vk::PhysicalDevice physicalDevice=physicalDevices[0];
	std::vector<vk::QueueFamilyProperties>queueFamilyProperties=physicalDevice.getQueueFamilyProperties();
	size_t graphicsQueueFamilyIndex=std::distance(queueFamilyProperties.begin(),std::find_if(queueFamilyProperties.begin(),queueFamilyProperties.end(),[](vk::QueueFamilyProperties const&qfp){return qfp.queueFlags&vk::QueueFlagBits::eGraphics;}));
	float queuePriority=0;
	vk::DeviceQueueCreateInfo deviceQueueCreateInfo({}, static_cast<uint32_t>(graphicsQueueFamilyIndex), 1, &queuePriority);
	vk::UniqueDevice device = physicalDevice.createDeviceUnique(vk::DeviceCreateInfo({}, 1, &deviceQueueCreateInfo));
	}catch(vk::SystemError err){
		printf("vk::SystemError: %s\n",err.what());
	}catch(...){
		printf("Other error\n");
	}
	return 0;
}
