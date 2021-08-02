/********************************************************************
* Page settings 
*
* Application own settings
* Home preferences
*********************************************************************/

#include "Gui.h"
#include "PSettings.h"

PSettings::PSettings( lv_obj_t *np ) : Page( np, true ){

		/* Pool mode */
	this->pool = new DropDown( this->getMyself() );

	this->addStyle( dropdownStyle );
	this->pool->setChoices( "Heures Creuses\nArret\nForce", true );
	this->pool->Align(LV_ALIGN_IN_TOP_LEFT);
}
