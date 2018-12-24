/*
 * MenuBar.h
 *
 *  Created on: Nov 18, 2018
 *      Author: jack
 */

#ifndef GTKHPP_MENUBAR_H_
#define GTKHPP_MENUBAR_H_

#include "gtk_include.h"
#include "Container.h"
#include "Menu.h"

namespace gtk {

class MenuBar : public Container {
public:
	MenuBar();
	virtual ~MenuBar();

	void create();
	void addMenu(Menu*menu);
};

} /* namespace gtk */

#endif /* GTKHPP_MENUBAR_H_ */
