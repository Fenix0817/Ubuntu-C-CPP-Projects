/*
 * Menu.h
 *
 *  Created on: Nov 18, 2018
 *      Author: jack
 */

#ifndef GTKHPP_MENU_H_
#define GTKHPP_MENU_H_

#include "gtk_include.h"
#include "Container.h"
#include "MenuItem.h"

namespace gtk {

class Menu : public Container {
public:
	Menu();
	virtual ~Menu();

	void create();
	void addItem(MenuItem*mi);
};

} /* namespace gtk */

#endif /* GTKHPP_MENU_H_ */
