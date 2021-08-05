/**********************************************************
 * Derivate objects is able to handle MQTT
 **********************************************************/

#ifndef MQTT_ABLE_H
#define MQTT_ABLE_H

#include <AsyncMqttClient.h>

#define MAJORDOME "Majordome.dev"

extern AsyncMqttClient mqttClient;

class MQTT_able {
protected :
	const char **topics;

public:
	void registerMQTT( AsyncMqttClient & );
	bool handleMessages( const char *, const char * );
};

#endif
