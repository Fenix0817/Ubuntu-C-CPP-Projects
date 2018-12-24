/*
 * MenuItem.h
 *
 *  Created on: Nov 18, 2018
 *      Author: jack
 */

#ifndef GTKHPP_MENUITEM_H_
#define GTKHPP_MENUITEM_H_

#include "gtk_include.h"
#include "Container.h"

namespace gtk {

class MenuItem : public Container {
public:
	MenuItem();
	virtual ~MenuItem();

	void create();

	void setRightJustified(bool b);

	void setSubMenu(Widget*m);
};

} /* namespace gtk */

#endif /* GTKHPP_MENUITEM_H_ */
