/*
 * EntryBuffer.h
 *
 *  Created on: Nov 16, 2018
 *      Author: jack
 */

#ifndef ENTRYBUFFER_H_
#define ENTRYBUFFER_H_

#include "gtk_include.h"

namespace gtk {

typedef void (*EntryBufferInsertCallback)(GtkEntryBuffer*buffer,int pos,gchar*chars,guint n_chars,gpointer user_data);
typedef void (*EntryBufferDeleteCallback)(GtkEntryBuffer*buffer,int pos,guint n_chars,gpointer user_data);

class EntryBuffer {
public:
	EntryBuffer();
	virtual ~EntryBuffer();

	GtkEntryBuffer*buffer;

	void create();
	std::string getText();
	void setText(std::string s);
	int getLength();
	int getMaxLength();
	void setMaxLength(int i);
	void insertText(int pos,std::string str);
	void deleteText(int pos,int num);

	void addInsertListener(EntryBufferInsertCallback callback,gpointer userData);
	void addDeleteListener(EntryBufferDeleteCallback callback,gpointer userData);

};

} /* namespace gtk */

#endif /* ENTRYBUFFER_H_ */
