/********************************************************************
* Page settings definition
*********************************************************************/

#ifndef PSETTINGS_H
#define PSETTINGS_H

#include "MQTT_able.h"

#include <Page.h>
#include <Container.h>
#include <DropDown.h>
#include <Image.h>

class PSettings : public Page, public MQTT_able {

	Container	*poolCont;
	Image		*poolIcon;
	DropDown	*pool;

	Container	*homeCont;
	Image		*homeIcon;
	DropDown	*home;

public :
	PSettings( lv_obj_t * );
	bool handleMessages( const char *, const char * );
};

#endif
