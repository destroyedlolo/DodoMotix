/********************************************************************
* GUI's root interface
*********************************************************************/

#include "Gui.h"

#include <Page.h>

	/*****
	 * objects
	 *****/
	
Gui *gui;
Style *mainStyle, *dropdownStyle;

	/**** 
	 * Build the GUI
	 *****/

Gui::Gui( void ){
		/* Styles */
	mainStyle = new Style();
	mainStyle->setBgColor( LV_COLOR_BLACK );
	mainStyle->setBgGradStart( 50 );
	mainStyle->setBgGradColor( LV_COLOR_NAVY );
	mainStyle->setBgGradDir( LV_GRAD_DIR_VER );
	mainStyle->setTextColor( LV_COLOR_WHITE );
	mainStyle->seTexttFont( &lv_font_montserrat_28 );

	dropdownStyle = new Style();
	dropdownStyle->copyStyle( mainStyle );
	dropdownStyle->setRadius( 5 );
	dropdownStyle->setBgOpacity( LV_OPA_70 );
	dropdownStyle->setBorderWidth( 1 );
	
	this->tv = new TabView( lv_scr_act() );	// Create the TabView
	this->tv->addStyle( mainStyle );

		/* Add styles to tab */
	this->tv->setBgColor( LV_COLOR_NAVY, LV_TABVIEW_PART_TAB_BG );
	this->tv->setBgGradColor( LV_COLOR_BLACK, LV_TABVIEW_PART_TAB_BG );
	this->tv->setBgGradDir( LV_GRAD_DIR_VER, LV_TABVIEW_PART_TAB_BG );
	this->tv->seTexttFont( &lv_font_montserrat_22, LV_TABVIEW_PART_TAB_BG );
	this->tv->setTextColor( LV_COLOR_SILVER, LV_TABVIEW_PART_TAB_BG  );	// Unselected tab
	this->tv->setPadding( 5,5,5,5, LV_TABVIEW_PART_TAB_BTN  );	// Reduce space took
	this->tv->setTextColor( LV_COLOR_YELLOW, LV_TABVIEW_PART_TAB_BTN, LV_STATE_CHECKED ); // Selected tab

	this->pstn = new PSettings( tv->AddTab( LV_SYMBOL_SETTINGS " Param" ) );
	this->ptime = new PTime( tv->AddTab( LV_SYMBOL_BELL " Horloge" ) );
	this->pnrj = new PEnergy( tv->AddTab( LV_SYMBOL_CHARGE " Energie" ) );

		/* The GUI is initialised,
		 * ready to launch automation
		 */
	this->initAutomation();	// Launch automation

		/* Set the default tab (hour) */
	this->tv->setActiveTab(1, LV_ANIM_OFF);
}

void Gui::initAutomation( void ){
	this->ptime->initAutomation();
}

