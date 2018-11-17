/*
 * EntryBuffer.cpp
 *
 *  Created on: Nov 16, 2018
 *      Author: jack
 */

#include "EntryBuffer.h"

namespace gtk {

EntryBuffer::EntryBuffer() {
	// TODO Auto-generated constructor stub

}

EntryBuffer::~EntryBuffer() {
	// TODO Auto-generated destructor stub
}

void EntryBuffer::create(){
	buffer=gtk_entry_buffer_new("\0",strlen("\0"));
}
std::string EntryBuffer::getText(){
	return std::string(gtk_entry_buffer_get_text(buffer));
}
void EntryBuffer::setText(std::string s){
	gtk_entry_buffer_set_text(buffer,s.c_str(),s.length());
}
int EntryBuffer::getLength(){
	return gtk_entry_buffer_get_length(buffer);
}
int EntryBuffer::getMaxLength(){
	return gtk_entry_buffer_get_max_length(buffer);
}
void EntryBuffer::setMaxLength(int i){
	gtk_entry_buffer_set_max_length(buffer,i);
}
void EntryBuffer::insertText(int pos,std::string str){
	gtk_entry_buffer_insert_text(buffer,pos,str.c_str(),str.length());
}
void EntryBuffer::deleteText(int pos,int num){
	gtk_entry_buffer_delete_text(buffer,pos,num);
}
void EntryBuffer::addInsertListener(EntryBufferInsertCallback callback,gpointer userData){
	g_signal_connect(buffer,"inserted-text",G_CALLBACK(callback),userData);
}
void EntryBuffer::addDeleteListener(EntryBufferDeleteCallback callback,gpointer userData){
	g_signal_connect(buffer,"deleted-text",G_CALLBACK(callback),userData);
}


} /* namespace gtk */
