/********************************************************************
* GUI's root interface
*********************************************************************/

#include "Gui.h"

#include <Page.h>

	/*****
	 * objects
	 *****/
	
Gui *gui;

	/**** 
	 * Build the GUI
	 *****/

Gui::Gui( void ){
	this->mainStyle = new Style();
	this->mainStyle->setBgColor( LV_COLOR_BLACK );
	this->mainStyle->setBgGradStart( 50 );
	this->mainStyle->setBgGradColor( LV_COLOR_NAVY );
	this->mainStyle->setBgGradDir( LV_GRAD_DIR_VER );
	this->mainStyle->setTextColor( LV_COLOR_WHITE );
	this->mainStyle->seTexttFont( &lv_font_montserrat_28 );

	this->tv = new TabView( lv_scr_act() );	// Create the TabView
	tv->addStyle( mainStyle );

	this->pstn = new PSettings( tv->AddTab( LV_SYMBOL_SETTINGS " Param" ) );
	this->pnrj = new PEnergy( tv->AddTab( LV_SYMBOL_SETTINGS " Param" ) );
}

