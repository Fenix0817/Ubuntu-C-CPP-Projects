/*
 * Grid.h
 *
 *  Created on: Nov 14, 2018
 *      Author: jack
 */

#ifndef GTKHPP_GRID_H_
#define GTKHPP_GRID_H_

#include "Widget.h"
#include "Container.h"

namespace gtk {

class Grid : public Container {
public:
	Grid();
	virtual ~Grid();

	void create();
	void add(Widget*wi,int x,int y,int w,int h);
};

} /* namespace gtk */

#endif /* GTKHPP_GRID_H_ */
