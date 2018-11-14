/*
 * Label.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#include "Label.h"

namespace gtk {

Label::Label() {
	// TODO Auto-generated constructor stub

}

Label::~Label() {
	// TODO Auto-generated destructor stub
}

void Label::create(){
	widget=gtk_label_new("");
}

void Label::setText(std::string s){
	gtk_label_set_text(GTK_LABEL(widget),s.c_str());
}

} /* namespace gtk */
