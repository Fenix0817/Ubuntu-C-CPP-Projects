/*
 * Container.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#include "Container.h"

namespace gui {

Container::Container() {
	// TODO Auto-generated constructor stub

}

Container::~Container() {
	// TODO Auto-generated destructor stub
}

void Container::add(Widget w){
	gtk_container_add(GTK_CONTAINER(widget),w.widget);
}

void Container::remove(Widget w){
	gtk_container_remove(GTK_CONTAINER(widget),w.widget);
}

} /* namespace gui */
