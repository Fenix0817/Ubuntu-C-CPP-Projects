/*
 * Entry.h
 *
 *  Created on: Nov 16, 2018
 *      Author: jack
 */

#ifndef ENTRY_H_
#define ENTRY_H_

#include "gtk_include.h"
#include "Widget.h"
#include "EntryBuffer.h"

namespace gtk {

class Entry : public Widget {
public:
	Entry();
	virtual ~Entry();

	EntryBuffer*buffer;

	void create();

	void setText(std::string s);
	std::string getText();

	int getTextLength();

};

} /* namespace gtk */

#endif /* ENTRY_H_ */
