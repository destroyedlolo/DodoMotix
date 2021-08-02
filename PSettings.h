/********************************************************************
* Page settings definition
*********************************************************************/

#ifndef PSETTINGS_H
#define PSETTINGS_H

#include <Page.h>
#include <DropDown.h>

class PSettings : public Page {
	DropDown	*pool;

public :
	PSettings( lv_obj_t * );
};

#endif
