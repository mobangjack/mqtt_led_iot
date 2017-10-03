#ifndef MQTT_LED_CUR_STATE_PUB_H
#define MQTT_LED_CUR_STATE_PUB_H

#include <mosquittopp.h>
#include "gpio.h"

class mqtt_led_cur_state_pub : public mosqpp::mosquittopp
{
	public:
		mqtt_led_cur_state_pub(const char *id, const char *topic, const char *device);
		~mqtt_led_cur_state_pub();

		void on_connect(int rc);
		void on_message(const struct mosquitto_message *message);
		void on_subscribe(int mid, int qos_count, const int *granted_qos);
		void advertise();
		void spin(int hz);
	protected:
		std::string m_topic;
		gpio m_led;
};

#endif
