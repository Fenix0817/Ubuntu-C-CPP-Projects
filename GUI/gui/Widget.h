/*
 * Widget.h
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#ifndef WIDGET_H_
#define WIDGET_H_

#include "gtk_include.h"

namespace gui {

class Widget {
public:
	Widget();
	virtual ~Widget();

	GtkWidget*widget;

	void showAll();
};

} /* namespace gui */

#endif /* WIDGET_H_ */
