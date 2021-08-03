/********************************************************************
* Page settings 
*
* Application own settings
* Home preferences
*********************************************************************/

#include "Gui.h"
#include "PSettings.h"

LV_IMG_DECLARE(image_piscine_32px);

PSettings::PSettings( lv_obj_t *np ) : Page( np, true ){

		/* Pool mode */
	
	this->poolIcon = new Image( this->getMyself() );
	this->poolIcon->Align( LV_ALIGN_IN_TOP_LEFT );
	this->poolIcon->Set( &image_piscine_32px );
/*
	this->syncIcon->setClickable( true );
	this->syncIcon->attacheEventeHandler( syncTime );
*/

	this->pool = new DropDown( this->getMyself() );
	this->pool->addStyle( dropdownStyle );
	this->pool->setWidth( 160 );
	this->pool->setChoices( "Heures Creuses\nArret\nForce", true );
	this->pool->Align( LV_ALIGN_OUT_RIGHT_MID, this->poolIcon, 10 );
}
