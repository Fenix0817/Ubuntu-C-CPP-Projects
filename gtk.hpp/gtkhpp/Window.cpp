/*
 * Window.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#include "../gtkhpp/Window.h"

namespace gtk {

Window::Window() {
	// TODO Auto-generated constructor stub

}

Window::~Window() {
	// TODO Auto-generated destructor stub
}

void Window::create(GtkWindowType type){
	widget=gtk_window_new(type);
}
void Window::setPosition(GtkWindowPosition pos){
	gtk_window_set_position(GTK_WINDOW(widget),pos);
}
void Window::setSize(int w,int h){
	gtk_window_set_default_size(GTK_WINDOW(widget),w,h);
}
void Window::setTitle(const char*title){
	gtk_window_set_title(GTK_WINDOW(widget),title);
}

void Window::enableQuitOnExit(){
	g_signal_connect(G_OBJECT(widget),"destroy",G_CALLBACK(gtk_main_quit),NULL);
}

int Window::getWidth(){
	int w,h;
	gtk_window_get_size(GTK_WINDOW(widget),&w,&h);
	return w;
}
int Window::getHeight(){
	int w,h;
	gtk_window_get_size(GTK_WINDOW(widget),&w,&h);
	return h;
}

} /* namespace gtk */
