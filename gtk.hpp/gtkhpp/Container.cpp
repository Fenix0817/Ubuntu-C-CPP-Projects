/*
 * Container.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#include "../gtkhpp/Container.h"

namespace gtk {

Container::Container() {
	// TODO Auto-generated constructor stub

}

Container::~Container() {
	// TODO Auto-generated destructor stub
}

void Container::add(Widget*w){
	gtk_container_add(GTK_CONTAINER(widget),w->widget);
//	comps.push_back(w);
}

void Container::remove(Widget*w){
	gtk_container_remove(GTK_CONTAINER(widget),w->widget);
//	comps.erase(std::remove(comps.begin(),comps.end(),w),comps.end());
}

} /* namespace gtk */
