/********************************************************************
* Page settings definition
*********************************************************************/

#ifndef PSETTINGS_H
#define PSETTINGS_H

#include <Page.h>
#include <Container.h>
#include <DropDown.h>
#include <Image.h>

class PSettings : public Page {

	Container	*poolCont;
	Image		*poolIcon;
	DropDown	*pool;

public :
	PSettings( lv_obj_t * );
};

#endif
