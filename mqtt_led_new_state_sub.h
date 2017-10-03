#ifndef MQTT_LED_NEW_STATE_SUB_H
#define MQTT_LED_NEW_STATE_SUB_H

#include <mosquittopp.h>
#include <string>
#include "gpio.h"

class mqtt_led_new_state_sub : public mosqpp::mosquittopp
{
	public:
		mqtt_led_new_state_sub(const char *id, const char *topic, const char *device);
		~mqtt_led_new_state_sub();

		void on_connect(int rc);
		void on_message(const struct mosquitto_message *message);
		void on_subscribe(int mid, int qos_count, const int *granted_qos);
		
	protected:
		std::string m_topic;
		gpio m_led;
};

#endif
