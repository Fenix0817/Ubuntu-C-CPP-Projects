/*
 * Container.h
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "Widget.h"

namespace gui {

class Container : public Widget {
public:
	Container();
	virtual ~Container();

	void add(Widget w);
	void remove(Widget w);
};

} /* namespace gui */

#endif /* CONTAINER_H_ */
