/*
 * Utils.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#include "../gtkhpp/Utils.h"

namespace gtk {

void init(int argc,char**argv){
	gtk_init(&argc,&argv);
}

void startMain(){
	gtk_main();
}

} /* namespace gtk */
