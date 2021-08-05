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

static void poolChanged(lv_obj_t * obj, lv_event_t event){
	static const char *val[]={ "Heures Creuses", "Arret", "Forcé" };

	if(event == LV_EVENT_VALUE_CHANGED){
		Serial.printf( "Pool changed to : %d (%s)\n", lv_dropdown_get_selected(obj), val[lv_dropdown_get_selected(obj)]);
		mqttClient.publish( MAJORDOME "/Mode/Piscine", 0, true, val[lv_dropdown_get_selected(obj)], strlen( val[lv_dropdown_get_selected(obj)] ));
	}
}

static void homeChanged(lv_obj_t * obj, lv_event_t event){
	static const char *val[]={ "Auto", "Manuel", "Travail", "Vacances", "Absent" };

	if(event == LV_EVENT_VALUE_CHANGED){
		Serial.printf( "Home changed to : %d (%s)\n", lv_dropdown_get_selected(obj), val[lv_dropdown_get_selected(obj)]);
		mqttClient.publish( MAJORDOME "/Mode/Force", 0, true, val[lv_dropdown_get_selected(obj)], strlen( val[lv_dropdown_get_selected(obj)] ));
	}
}

PSettings::PSettings( lv_obj_t *np ) : Page( np, true ){

	static const char *tpc[] = { MAJORDOME "/Mode/Force", MAJORDOME "/Mode/Piscine", NULL };
	this->topics = tpc;

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
	this->pool->setShow( true );
	this->pool->Align( LV_ALIGN_OUT_RIGHT_MID, this->poolIcon, 10 );

	this->pool->attacheEventeHandler( poolChanged );

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
	this->home->setShow( true );
	this->home->Align( LV_ALIGN_OUT_RIGHT_MID, this->homeIcon, 10 );

	this->home->attacheEventeHandler( homeChanged );
}

bool PSettings::handleMessages( const char *t, const char *p ){
	if(!strcmp(t, MAJORDOME "/Mode/Force")){
		if(!strcmp(p,"Auto"))
			this->home->setSelected(0);
		else if(!strcmp(p,"Manuel"))
			this->home->setSelected(1);
		else if(!strcmp(p,"Travail"))
			this->home->setSelected(2);
		else if(!strcmp(p,"Vacances"))
			this->home->setSelected(3);
		else if(!strcmp(p,"Absent"))
			this->home->setSelected(4);

		this->home->setShow( true );
	} else if(!strcmp(t, MAJORDOME "/Mode/Piscine")){
		if(!strcmp(p,"Heures Creuses"))
			this->pool->setSelected(0);
		else if(!strcmp(p,"Arret"))
			this->pool->setSelected(1);
		else if(!strcmp(p,"Forcé"))
			this->pool->setSelected(2);

		this->pool->setShow( true );
	} else {
		Serial.println(">>>> NON !");
		return false;
	}

	Serial.println(">>>> Trouvé");
	return true;
}
