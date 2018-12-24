/*
 *  main.cpp
 *
 *  Created on: Nov 18, 2018
 *      Author: jack
 */

#include "OpenDialog.h"


int main(int argc,char**argv){
	gtk::init(argc,argv);

	OpenDialog od;
	od.init();
	od.show();

	gtk::startMain();

	return 0;
}

