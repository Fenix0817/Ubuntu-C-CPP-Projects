/*
 * Menu.cpp
 *
 *  Created on: Nov 18, 2018
 *      Author: jack
 */

#include <gtkhpp/Menu.h>

namespace gtk {

Menu::Menu() {
	// TODO Auto-generated constructor stub

}

Menu::~Menu() {
	// TODO Auto-generated destructor stub
}

void Menu::create(){
	widget=gtk_menu_new();
}

} /* namespace gtk */
