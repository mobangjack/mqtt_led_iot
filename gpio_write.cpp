#include "gpio.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("Usage: gpio_write <port> <value>\n");
		return -1;
	}
	gpio line(argv[1]);
	line.wire(O_WRONLY);
	if (!line.isWired())
	{
		printf("[ERROR] Unable to wire gpio\n");
		return -1;
	}
	line.assign(argv[2][0]);
	line.cutoff();
	return 0;
}
