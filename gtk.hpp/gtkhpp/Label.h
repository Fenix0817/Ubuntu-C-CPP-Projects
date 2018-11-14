/*
 * Label.h
 *
 *  Created on: Nov 12, 2018
 *      Author: jack
 */

#ifndef LABEL_H_
#define LABEL_H_

#include "Widget.h"

namespace gtk {

class Label : public Widget {
public:
	Label();
	virtual ~Label();

	void create();
	void setText(std::string txt);
};

} /* namespace gtk */

#endif /* LABEL_H_ */
