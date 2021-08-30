/********************************************************************
* Page to display time definition
*********************************************************************/

#ifndef PTIME_H
#define PTIME_H

#include "MQTT_able.h"

#include <Container.h>
#include <Page.h>
#include <Label.h>

class PTime : public Page, public MQTT_able {
	Label		*tDehors,
				*tSalon;

	Label		*timelabel,
				*datelabel;

	Label		*version;

	lv_task_t	*upd_h_task;	// Task to update the Gui

	int 		daynum;		// number of the day of the year

public :
	PTime( lv_obj_t * );

	/* update field */
	void updateTime( void );

	/* MQTT related */
	bool handleMessages( const char *, const char * );

	/* Initialise automation */
	void initAutomation( void );
};

#endif
