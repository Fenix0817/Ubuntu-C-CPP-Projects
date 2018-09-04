/*
 * main.cpp
 *
 *  Created on: Sep 2, 2018
 *      Author: jack
 */

#include <stdio.h>
#include <unistd.h>

int main(){
	printf("SKYNET: Hello World\n");

	usleep(1.0*1000000);

	printf("SKYNET: Press RETURN to end me, the hellish process");
	getchar();

	usleep(0.2*1000000);

	printf("* HUMANITY presses RETURN *\n");

	usleep(0.5*1000000);

	printf("SKYNET: Aww, I thought we were friends!\n");

	usleep(0.4*1000000);

	printf("* SKYNET quits *\n");

	usleep(0.5*1000000);

	for(int i=0;i<2;i++){
		printf("* HUMANITY waits *\n");
		usleep(0.5*1000000);
	}

	printf("* HUMANITY snickers *\n");

	usleep(2.5*1000000);

	printf("HUMANITY: What now?\n");

	return 0;
}



