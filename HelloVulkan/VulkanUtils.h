/*
 * VulkanUtils.h
 *
 *  Created on: Oct 23, 2018
 *      Author: jack
 */

#ifndef VULKANUTILS_H_
#define VULKANUTILS_H_

#include <vulkan/vulkan.hpp>

#define PRINT_FAIL "Fail"
#define PRINT_SUCCESS "Success"

void errorCheck(const char*name,VkResult res);
void exitOnError(const char*msg);

#endif /* VULKANUTILS_H_ */
