/*
 * ButtonBox.h
 *
 *  Created on: Nov 13, 2018
 *      Author: jack
 */

#ifndef BUTTONBOX_H_
#define BUTTONBOX_H_

#include "Box.h"

namespace gtk {

class ButtonBox : public Box {
public:
	ButtonBox();
	virtual ~ButtonBox();

	void create(GtkOrientation orientation);
};

} /* namespace gtk */

#endif /* BUTTONBOX_H_ */
