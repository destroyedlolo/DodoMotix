/********************************************************************
* Page settings 
*
* Application own settings
* Home preferences
*********************************************************************/

#include "Gui.h"
#include "PSettings.h"

LV_IMG_DECLARE(image_piscine_32px);
LV_IMG_DECLARE(image_maison_32px);

PSettings::PSettings( lv_obj_t *np ) : Page( np, true ){

		/* Pool mode */
	this->poolCont = new Container( containerStyle, this->getMyself() );
	this->poolCont->setBgOpacity(0);
	this->poolCont->Align( LV_ALIGN_IN_TOP_LEFT, (const lv_obj_t *)NULL, 0,5 );
	this->poolCont->setFit( LV_FIT_TIGHT );	// Its size is the one of it's child
	this->poolCont->AutoRealign();	// otherwise the icon is shifted
	this->poolCont->setPadding(0);
	this->poolCont->setClickable( false);

	this->poolIcon = new Image( this->poolCont );
	this->poolIcon->Set( &image_piscine_32px );
	this->poolIcon->Align( LV_ALIGN_IN_LEFT_MID );
	this->poolIcon->setClickable( false );

	this->pool = new DropDown( this->poolCont );
	this->pool->addStyle( dropdownStyle );
	this->pool->setWidth( 160 );
	this->pool->setChoices( "Heures Creuses\nArret\nForce", true );
	this->pool->Align( LV_ALIGN_OUT_RIGHT_MID, this->poolIcon, 10 );

		/* Home mode */
	this->homeCont = new Container( containerStyle, this->getMyself() );
	this->homeCont->setBgOpacity(0);
	this->homeCont->Align( LV_ALIGN_OUT_BOTTOM_MID, this->poolCont->getMyself(), 0,5 );
	this->homeCont->setFit( LV_FIT_TIGHT );	// Its size is the one of it's child
	this->homeCont->AutoRealign();	// otherwise the icon is shifted
	this->homeCont->setPadding(0);
	this->homeCont->setClickable( false);

	this->homeIcon = new Image( this->homeCont );
	this->homeIcon->Set( &image_maison_32px );
	this->homeIcon->Align( LV_ALIGN_IN_LEFT_MID );
	this->homeIcon->setClickable( false );

	this->home = new DropDown( this->homeCont );
	this->home->addStyle( dropdownStyle );
	this->home->setWidth( 160 );
	this->home->setChoices( "Auto\nManuel\nTravail\nVacances\nAbsent", true );
	this->home->Align( LV_ALIGN_OUT_RIGHT_MID, this->homeIcon, 10 );

}
