/*
 * Box.cpp
 *
 *  Created on: Nov 13, 2018
 *      Author: jack
 */

#include "Box.h"

namespace gtk {

Box::Box() {
	// TODO Auto-generated constructor stub

}

Box::~Box() {
	// TODO Auto-generated destructor stub
}

void Box::create(GtkOrientation orientation,int spacing){
	widget=gtk_box_new(orientation,spacing);
}

} /* namespace gtk */
