/**********************************************************
 * Derivate objects is able to handle MQTT
 **********************************************************/

#include "MQTT_able.h"

#include <Arduino.h>

void MQTT_able::registerMQTT( AsyncMqttClient &mqttClient ){
	for( int i=0; this->topics[i]; i++){
		Serial.println(this->topics[i]);
		mqttClient.subscribe(this->topics[i], 0);
	}
}
