/*
 * Widget.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#include "Widget.h"

namespace gui {

Widget::Widget() {
	// TODO Auto-generated constructor stub

}

Widget::~Widget() {
	// TODO Auto-generated destructor stub
}

void Widget::showAll(){
	gtk_widget_show_all(widget);
}

} /* namespace gui */
