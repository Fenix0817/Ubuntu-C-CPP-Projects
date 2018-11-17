/*
 * Entry.cpp
 *
 *  Created on: Nov 16, 2018
 *      Author: jack
 */

#include "Entry.h"

namespace gtk {

Entry::Entry() {
	// TODO Auto-generated constructor stub

}

Entry::~Entry() {
	// TODO Auto-generated destructor stub
}

void Entry::create(){
	buffer=new EntryBuffer();
	buffer->create();

	widget=gtk_entry_new_with_buffer(buffer->buffer);
}

void Entry::setText(std::string s){
	buffer->setText(s);
}
std::string Entry::getText(){
	return buffer->getText();
}

int Entry::getTextLength(){
	return buffer->getLength();
}


} /* namespace gtk */
