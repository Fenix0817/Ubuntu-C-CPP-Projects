/*
 * Box.h
 *
 *  Created on: Nov 13, 2018
 *      Author: jack
 */

#ifndef BOX_H_
#define BOX_H_

#include "Container.h"

namespace gtk {

class Box : public Container {
public:
	Box();
	virtual ~Box();

	void create(GtkOrientation orientation,int spacing);
};

} /* namespace gtk */

#endif /* BOX_H_ */
