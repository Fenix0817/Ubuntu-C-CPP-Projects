/*
 * MenuItem.cpp
 *
 *  Created on: Nov 18, 2018
 *      Author: jack
 */

#include <gtkhpp/MenuItem.h>

namespace gtk {

MenuItem::MenuItem() {
	// TODO Auto-generated constructor stub

}

MenuItem::~MenuItem() {
	// TODO Auto-generated destructor stub
}

void MenuItem::create(){
	widget=gtk_menu_item_new();
}

void MenuItem::setRightJustified(bool b){
	gtk_menu_item_set_right_justified(GTK_MENU_ITEM(widget),b);
}

void MenuItem::setSubMenu(Widget*m){
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(widget),m->widget);
}

} /* namespace gtk */
