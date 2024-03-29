/********************************************************************
* GUI's root interface
*********************************************************************/
#ifndef GUI_H
#define GUI_H

#include <Arduino.h>
#include <lvgl/lvgl.h>
#include <AsyncMqttClient.h>

#include <Page.h>
#include <TabView.h>

#include "PSettings.h"
#include "PTime.h"
#include "PEnergy.h"

class Gui {

	TabView *tv;
	PSettings *pstn;
	PTime *ptime;
	PEnergy *pnrj;

public:
	Gui( void );

	/* Launch automation tasks.
	 * Has to be called ONLY when everything is initialised
	 */
	void initAutomation( void );

	/* Register MQTT topics 
	 *	-> MQTT client
	 */
	void registerMQTT( AsyncMqttClient & );

	/* Handle incomming topics 
	 * 	-> topic
	 * 	-> payload
	 * 	<- true if the topic has been consumed
	 */
	bool handleMessages( const char *, const char * );

};

extern class Gui *gui;

extern Style *mainStyle,
			*containerStyle,
			*dropdownStyle;

#endif
