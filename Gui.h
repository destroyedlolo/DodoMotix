/********************************************************************
* GUI's root interface
*********************************************************************/
#ifndef GUI_H
#define GUI_H

#include <Arduino.h>
#include <lvgl/lvgl.h>

#include <TabView.h>

class Gui {

	TabView *tv;

public:
	Gui( void );
};

extern class Gui *gui;

#endif
