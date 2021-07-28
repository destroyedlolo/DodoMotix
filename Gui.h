/********************************************************************
* GUI's root interface
*********************************************************************/
#ifndef GUI_H
#define GUI_H

#include <Arduino.h>
#include <lvgl/lvgl.h>

#include <Page.h>
#include <TabView.h>

#include "PSettings.h"
#include "PEnergy.h"

class Gui {

	Style *mainStyle;

	TabView *tv;
	PSettings *pstn;
	PEnergy *pnrj;

public:
	Gui( void );
};

extern class Gui *gui;

#endif
