#include "mqtt_led_new_state_sub.h"
#include <stdio.h>
#include <stdlib.h>

void help()
{
	printf("Usage: mqtt_led_new_state_sub_main <id> <topic> <device> <host> <port> <keepalive>\n");
}

int main(int argc, char *argv[])
{
	if (argc < 7)
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

	mqtt_led_new_state_sub led_new_state_sub(id, topic, device);
	led_new_state_sub.connect(host, port, keepalive);

	int rc;

	mosqpp::lib_init();

	while(1){
		rc = led_new_state_sub.loop();
		if(rc){
			led_new_state_sub.reconnect();
		}
	}

	mosqpp::lib_cleanup();

	return 0;
}

