/*
 * Container.h
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "Widget.h"

namespace gtk {

class Container : public Widget {
public:
	Container();
	virtual ~Container();

	void create();
	void add(Widget*w);
	void remove(Widget*w);

//	std::vector<Widget>comps;
};

} /* namespace gtk */

#endif /* CONTAINER_H_ */
