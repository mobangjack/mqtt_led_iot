#include "mqtt_led_cur_state_pub.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void help()
{
	printf("Usage: mqtt_led_cur_state_pub_main <id> <topic> <device> <host> <port> <keepalive> <hz>\n");
}

int main(int argc, char *argv[])
{
	if (argc < 8)
	{
		help();
		return -1;
	}

	const char* id = argv[1];
	const char* topic = argv[2];
	const char* device = argv[3];
	const char* host = argv[4];
	const int port = atoi(argv[5]);
	const int keepalive = atoi(argv[6]);
	const int hz = atoi(argv[7]);
	mqtt_led_cur_state_pub led_cur_state_pub(id, topic, device);
	led_cur_state_pub.connect(host, port, keepalive);

//	int hz = 1;
//	int us = (1.0 / (double)hz) * 1e6;

//	int rc;

	mosqpp::lib_init();

	led_cur_state_pub.spin(hz);
//	while(1){
//		rc = led_cur_state_pub.loop();
//		if(rc){
//			led_cur_state_pub.reconnect();
//		}
//		led_cur_state_pub.advertise();
//		usleep(us);
//	}

	mosqpp::lib_cleanup();

	return 0;
}

