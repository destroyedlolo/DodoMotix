/************************************************
*	DodoMotix
*
*	My smart home control from a LilyPI
*
*	Copyright 2020 Laurent Faillie (destroyedlolo)
*
*	Follow me on twitter : @DestroyedLolo
 ************************************************/

#include "config.h"

#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <esp_task_wdt.h>	// Watchdog
#include <rom/rtc.h>	// RTC wakeup code
#include <soc/rtc.h>	// RTC interface

#include <esp_task_wdt.h>	// Watchdog

#include <WiFi.h>
#include <AsyncMqttClient.h>

#include "Version.h"
#include "Gui.h"

	/* 
	 * Include my own home network definition 
	 * ...
	 */
/*
#if defined __has_include
#	if __has_include(<Maison.h>)
#		include <Maison.h>
#	endif
#endif
*/

/* well, __has_include() seems not working with Arduino IDE.
 * comment tout this include and define your granting bellow
 */
#include <Maison.h>

	/*
	 * ... otherwise, define yours
	 */
#ifndef WIFI_SSID
#	define WIFI_SSID "YourSSID"
#	define WIFI_PASSWORD "YourPassword"

#	define BROKER_HOST "Broker_Host_OrIP"
#	define BROKER_PORT 1883
#endif

	/* DEV DEV DEV DEV */
#define BROKER_HOST	"torchwood.chez.moi"

	/****
	* Shared object
	*****/

TTGOClass *ttgo;

	/****
	 * Network
	 ****/
	
AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

void WiFiEvent(WiFiEvent_t event) {
	Serial.printf("[WiFi-event] event: %d\n", event);
	switch(event) {
	case SYSTEM_EVENT_STA_GOT_IP:
		Serial.println("WiFi connected");
		Serial.println("IP address: ");
		Serial.println(WiFi.localIP());
		connectToMqtt();
		break;
	case SYSTEM_EVENT_STA_DISCONNECTED:
		Serial.println("WiFi lost connection");
		xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
		xTimerStart(wifiReconnectTimer, 0);
		break;
	default :
		break;
	}
}

void connectToWifi(){
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void connectToMqtt(){
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void onMqttConnect(bool ){
		/* Register home's topics */
	Serial.println("Registering MQTT :");
	gui->registerMQTT(mqttClient);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason){
  Serial.println("Disconnected from MQTT.");

  if (WiFi.isConnected())
    xTimerStart(mqttReconnectTimer, 0);
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total){
	char t[len+1];
	strncpy(t, payload, len);
	t[len] = 0;

	Serial.print("topic: ");
	Serial.print(topic);
	Serial.print(" > ");
	Serial.println(t);

		/* Handle messaging processing */
	gui->handleMessages( topic, t );
}

void time_synchronized(struct timeval *tv){
	Serial.println("time synchronized");
	ttgo->rtc->syncToRtc();
}

void setup(){
	Serial.begin(115200);

	Serial.println("starting DpdpMotix v" VERSION_H);
	Serial.printf("Configure watchdog to 30s: %d\n", esp_task_wdt_init( 30, true ) );
	Serial.print("Wakeup raison : ");
	switch( rtc_get_reset_reason(0) ){
	case POWERON_RESET :
		Serial.println("Power on");
		break;
	case SW_RESET :
		Serial.println("Software");
		break;
	case OWDT_RESET :
		Serial.println("Legacy Watch dog");
		break;
	case DEEPSLEEP_RESET :
		Serial.println("Deep Sleep");
		break;
	case SDIO_RESET :
		Serial.println("SLC");
		break;
	case TG0WDT_SYS_RESET :
		Serial.println("Timer Group0 Watch dog");
		break;
	case TG1WDT_SYS_RESET :
		Serial.println("Timer Group1 Watch dog");
		break;
	case RTCWDT_SYS_RESET :
		Serial.println("RTC Watch dog digital");
		break;
	case INTRUSION_RESET :
		Serial.println("Instrusion tested to reset");
		break;
	case TGWDT_CPU_RESET :
		Serial.println("Time Group");
		break;
	case SW_CPU_RESET :
		Serial.println("Software");
		break;
	case RTCWDT_CPU_RESET :
		Serial.println("RTC Watch dog");
		break;
	case EXT_CPU_RESET :
		Serial.println("reseted by PRO CPU");
		break;
	case RTCWDT_BROWN_OUT_RESET :
		Serial.println("vdd voltage is not stable");
		break;
	case RTCWDT_RTC_RESET :
		Serial.println("RTC Watch dog reset digital core and rtc module");
		break;
	default :
		Serial.println("Who know ...");
	}


		/****
		* Handle the watch
		*****/

	ttgo = TTGOClass::getWatch();
	ttgo->begin();	// start peripherals

		/****
		* restore the time
		*****/

	Serial.println("Reading RTC ...");

	setenv("TZ", "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00", 1);
	tzset();

	ttgo->rtc->check();			// Ensure the RTC is valid (if not use compilation time)
	ttgo->rtc->syncToSystem();	// sync with ESP32

		/****
		* WiFi initialisation
		*****/

	WiFi.persistent(false);		// Don't store anything b/w session as it's useless on a mobile device

		/****
		* Start the GUI
		*****/

	Serial.println("Starting GUI");

	ttgo->begin();			// start peripherals
	ttgo->lvgl_begin();
	ttgo->lvgl_whirling(3);	// power connector is on top

	gui = new Gui();	// Initialize the GUI with the screen is still off

	ttgo->openBL();	// Turn on the backlight

		/****
		* Start the Network
		*****/

	mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
	wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));
	WiFi.onEvent(WiFiEvent);

	mqttClient.onConnect(onMqttConnect);
	mqttClient.onDisconnect(onMqttDisconnect);
  	mqttClient.onMessage(onMqttMessage);
	mqttClient.setServer(BROKER_HOST, BROKER_PORT);
	
	connectToWifi();

	Serial.println("Time synchronisation requested");
	sntp_set_time_sync_notification_cb( time_synchronized );
	configTzTime("CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00", "pool.ntp.org");
/* the time synchronisation is asynchronous
 * so calling here RTC updating here is void
	ttgo->rtc->syncToRtc();
*/

		/****
		* Completed
		*****/

	Serial.printf("Total heap: %d\n", ESP.getHeapSize());
    Serial.printf("Free heap: %d\n", ESP.getFreeHeap());
    Serial.printf("Total PSRAM: %d\n", ESP.getPsramSize());
    Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram());

	Serial.println("\nInitialisation completed");
}

void loop(){
    lv_task_handler();
    delay(5);
}

