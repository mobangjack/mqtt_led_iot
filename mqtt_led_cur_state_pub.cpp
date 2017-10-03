#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include "mqtt_led_cur_state_pub.h"
#include <mosquittopp.h>
#include <string.h>

mqtt_led_cur_state_pub::mqtt_led_cur_state_pub(const char *id, const char *topic, const char *device) : mosquittopp(id), m_topic(topic), m_led(device)
{
	m_led.wire(O_RDONLY);
	if (!m_led.isWired())
	{
		printf("[ERROR] Cannot wire led\n");
	}
};

mqtt_led_cur_state_pub::~mqtt_led_cur_state_pub()
{
	if (m_led.isWired())
	{
		m_led.cutoff();
	}
}

void mqtt_led_cur_state_pub::on_connect(int rc)
{
	printf("Connected with code %d.\n", rc);
//	if(rc == 0){
		/* Only attempt to subscribe on a successful connect. */
//		subscribe(NULL, m_topic.c_str());
//	}
}

void mqtt_led_cur_state_pub::on_message(const struct mosquitto_message *message)
{
//	char buf[2];

//	if(!strcmp(message->topic, "led/brightness")){
//		memset(buf, 0, 2*sizeof(char));
		/* Copy N-1 bytes to ensure always 0 terminated. */
//		memcpy(buf, message->payload, 1*sizeof(char));
			
//	}
}

void mqtt_led_cur_state_pub::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
	printf("Subscription succeeded.\n");
}

void mqtt_led_cur_state_pub::advertise()
{
	if (m_led.isWired())
	{
		int state = m_led.stat();
		if (state == -1)
		{
			printf("[WARN] Led stat exception (would not be published)\n");
			return;
		}
		char buf[2];
		memset(buf, 0, 2 * sizeof(char));
		sprintf( buf,"%c",  state);
		publish(NULL, m_topic.c_str(), 2, buf);
	}
}

void mqtt_led_cur_state_pub::spin(int hz)
{
	int us = (1.0 / (double)hz) * 1e6;
	while (1)
	{
		advertise();
		usleep(us);
	}
}

