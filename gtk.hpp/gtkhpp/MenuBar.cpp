/*
 * MenuBar.cpp
 *
 *  Created on: Nov 18, 2018
 *      Author: jack
 */

#include <gtkhpp/MenuBar.h>

namespace gtk {

MenuBar::MenuBar() {
	// TODO Auto-generated constructor stub

}

MenuBar::~MenuBar() {
	// TODO Auto-generated destructor stub
}

void MenuBar::create(){
	widget=gtk_menu_bar_new();
}

void MenuBar::addMenu(Menu*menu){
	gtk_menu_shell_append(GTK_MENU_SHELL(widget),menu->widget);
}

} /* namespace gtk */
