/*
 * Widget.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#include "../gtkhpp/Widget.h"

namespace gtk {

Widget::Widget() {
	// TODO Auto-generated constructor stub

}

Widget::~Widget() {
	// TODO Auto-generated destructor stub
}

void Widget::showAll(){
	gtk_widget_show_all(widget);
}

} /* namespace gtk */
