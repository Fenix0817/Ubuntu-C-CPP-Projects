/*
 * ButtonBox.cpp
 *
 *  Created on: Nov 13, 2018
 *      Author: jack
 */

#include "ButtonBox.h"

namespace gtk {

ButtonBox::ButtonBox() {
	// TODO Auto-generated constructor stub

}

ButtonBox::~ButtonBox() {
	// TODO Auto-generated destructor stub
}

void ButtonBox::create(GtkOrientation orientation){
	widget=gtk_button_box_new(orientation);
}

} /* namespace gtk */
