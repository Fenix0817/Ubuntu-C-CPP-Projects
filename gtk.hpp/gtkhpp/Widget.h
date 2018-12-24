/*
 * Widget.h
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#ifndef WIDGET_H_
#define WIDGET_H_

#include "gtk_include.h"

namespace gtk {

class Widget {
public:
	Widget();
	virtual ~Widget();

	GtkWidget*widget;

	void showAll();
	void destroy();
};

} /* namespace gtk */

#endif /* WIDGET_H_ */
