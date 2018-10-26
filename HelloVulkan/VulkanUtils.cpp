/*
 * VulkanUtils.cpp
 *
 *  Created on: Oct 23, 2018
 *      Author: jack
 */

#include "VulkanUtils.h"

void errorCheck(const char*name,VkResult res){
	if(res!=VK_SUCCESS)printf("%s: %s\n",PRINT_FAIL,name);
	else printf("%s: %s\n",PRINT_SUCCESS,name);
	fflush(stdout);
}

void exitOnError(const char*msg){
	printf("ERROR: %s\n",msg);
	fflush(stdout);
	exit(EXIT_FAILURE);
}
