/*
 * Button.cpp
 *
 *  Created on: Nov 13, 2018
 *      Author: jack
 */

#include "Button.h"

namespace gtk {

Button::Button() {
	// TODO Auto-generated constructor stub

}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

void Button::create(){
	widget=gtk_button_new();
}

void Button::addLabel(std::string s){
	Label*w=new Label();
	w->create();
	w->setText(s);
	add(w);
}

} /* namespace gtk */
