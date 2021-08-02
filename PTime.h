/********************************************************************
* Page to display time definition
*********************************************************************/

#ifndef PTIME_H
#define PTIME_H

#include <Container.h>
#include <Page.h>
#include <Label.h>

class PTime : public Page {
	Label		*timelabel,
				*datelabel;

	Label		*version;

	lv_task_t	*upd_h_task;	// Task to update the Gui

	int 		daynum;		// number of the day of the year

public :
	PTime( lv_obj_t * );

	/* update field */
	void updateTime( void );

	/* Initialise automation
	 */
	void initAutomation( void );
};

#endif
