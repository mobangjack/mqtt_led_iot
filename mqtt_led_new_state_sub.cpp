#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include "mqtt_led_new_state_sub.h"
#include <mosquittopp.h>

mqtt_led_new_state_sub::mqtt_led_new_state_sub(const char *id, const char *topic, const char *device) : mosquittopp(id), m_topic(topic), m_led(device)
{
	m_led.wire(O_WRONLY);
	if (!m_led.isWired())
	{
		printf("[ERROR] Cannot wire led\n");
	}
};

mqtt_led_new_state_sub::~mqtt_led_new_state_sub()
{
	if (m_led.isWired())
	{
		m_led.cutoff();
	}
}

void mqtt_led_new_state_sub::on_connect(int rc)
{
	printf("Connected with code %d.\n", rc);
	if(rc == 0){
		/* Only attempt to subscribe on a successful connect. */
		subscribe(NULL, m_topic.c_str());
	}
}

void mqtt_led_new_state_sub::on_message(const struct mosquitto_message *message)
{
	char buf[2];

	if(!strcmp(message->topic, m_topic.c_str())){
		memset(buf, 0, 2*sizeof(char));
		/* Copy N-1 bytes to ensure always 0 terminated. */
		memcpy(buf, message->payload, 1*sizeof(char));
		bool success = false;
		if (m_led.isWired())
		{
			success = m_led.assign(buf[0]);
			printf("[INFO] Assign led to %c\n: %d", buf[0], success);
		}
		else
		{
			printf("[WARN] Led not wired, io operation was not available\n");
		}
	}
}

void mqtt_led_new_state_sub::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
	printf("Subscription succeeded.\n");
}

