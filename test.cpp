#include "gpio.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Usage: gpio_read <port>\n");
		return -1;
	}
	gpio line(argv[1]);
	line.wire(O_RDONLY);
	if (!line.isWired())
	{
		printf("[ERROR] Cannot wire gpio\n");
		return -1;
	}

	int hz = 10;
	int us = (1.0 / (double)hz) * 1e6;

	while (1)
	{
		int result = line.stat();
		printf("[INFO] gpio stat: %c\n", result);
		//usleep(us);
		int i = 1e8;
		while(--i);
	}

	line.cutoff();
	return 0;
}
