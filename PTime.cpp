/********************************************************************
* Page settings 
*
* Application own settings
* Home preferences
*********************************************************************/

#include "PTime.h"
#include "Version.h"

PTime::PTime( lv_obj_t *np ) : Page( np, true ), daynum( -1 ){
	this->SetScrollbarMode( LV_SCRLBAR_MODE_OFF );

	static const char *tpc[] = {
		"maison/Temperature/Dehors",
		"maison/Temperature/Salon",
		NULL
	};
	this->topics = tpc;

		/* Temperatures */
	this->tDehors = new Label( this->getMyself() );
	this->tDehors->seTexttFont( &lv_font_montserrat_28 );
	this->tDehors->setText( "+??.?" );
	this->tDehors->Align( LV_ALIGN_IN_TOP_LEFT );
//	this->tDehors->AutoRealign();

	this->tSalon = new Label( this->getMyself() );
	this->tSalon->seTexttFont( &lv_font_montserrat_28 );
	this->tSalon->setText( "+??.?" );
	this->tSalon->Align( LV_ALIGN_IN_TOP_RIGHT );
//	this->tSalon->AutoRealign();

		/* Display time */
	this->timelabel = new Label( this->getMyself() );
	this->timelabel->seTexttFont( &lv_font_montserrat_48 );
	this->timelabel->setText( "??:??:??" );
	this->timelabel->Align( LV_ALIGN_IN_TOP_MID, (const lv_obj_t *)NULL, 0,15 );
	this->timelabel->AutoRealign();

		/* and date */
	this->datelabel = new Label( this->getMyself() );
	this->datelabel->seTexttFont( &lv_font_montserrat_16 );
	this->datelabel->setText( "??.???? ????" );
	this->datelabel->Align( LV_ALIGN_OUT_BOTTOM_MID, this->timelabel );
	this->datelabel->AutoRealign();

		/* Version */
	this->version = new Label( this->getMyself() );
	this->version->seTexttFont( &lv_font_montserrat_10 );
	this->version->setText( "DodoMotix V" VERSION_H );
	this->version->Align( LV_ALIGN_IN_BOTTOM_MID );
	this->version->AutoRealign();
}

void PTime::updateTime( void ){
	time_t now;
	struct tm  info;
	char buf[64];

	time( &now );
	localtime_r( &now, &info );

	strftime( buf, sizeof(buf), "%H:%M:%S", &info );
	this->timelabel->setText( buf );

	if(info.tm_yday != this->daynum){
		this->daynum = info.tm_yday;
		strftime( buf, sizeof(buf), "%a %d %b %Y", &info );
		this->datelabel->setText( buf );
	}
}

static void cbUpdTime( lv_task_t *tsk ){
	((PTime *)(tsk->user_data))->updateTime();
}

bool PTime::handleMessages( const char *t, const char *p ){
	char s[8];

#if 0
	if(!strcmp(t, "maison/Temperature/Dehors")){
		sprintf(s, "%4.1f", atof(p));
		this->tDehors->setText( s );
	} else if(!strcmp(t, "maison/Temperature/Salon")){
		sprintf(s, "%4.1f", atof(p));
		this->tSalon->setText( s );
#endif
	} else
		return false;

	return true;
}

void PTime::initAutomation( void ){
	this->upd_h_task = lv_task_create( cbUpdTime, 500, LV_TASK_PRIO_MID, this );
}
