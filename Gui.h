/********************************************************************
* GUI's root interface
*********************************************************************/
#ifndef GUI_H
#define GUI_H

#include <Arduino.h>
#include <lvgl/lvgl.h>

#include <Page.h>

class Gui {

	Page *pg;

public:
	Gui( void );
};

extern class Gui *gui;

#endif
