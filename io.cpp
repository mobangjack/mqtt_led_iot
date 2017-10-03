#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>   //define O_WRONLY and O_RDONLY

void help()
{
	printf("Usage: io <file> <r/w? <value>\n");
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		help();
		return -1;
	}

	char* file = argv[1];
	char input = 0;
	char* value = 0;

	if (strcmp(argv[2], "w") == 0)
	{
		if (argc < 4)
		{
			help();
			return -1;
		}
		else
		{
			input = 1;
			value = argv[3];
		}
	}
	else if (strcmp(argv[2], "r") == 0)
	{
		input = 0;
	}
	else
	{
		help();
		return -1;
	}

	int fd = -1;
	if (input)
	{
		fd = open(file, O_WRONLY);
	}
	else
	{
		fd = open(file, O_RDONLY);
	}
	if (fd == -1)
	{
		printf("[ERROR] Cannot open file\n");
		return -1;
	}

	if (input)
	{
		write(fd, value, 1);
		printf("Write val: %c\n", value[0]);
	}
	else
	{
		char buf[2];
		memset(buf, 0, 2 * sizeof(char));
		read(fd, buf, 1);
		printf("Read val: %c\n", buf[0]);
	}
	close(fd);
	fd = -1;
	return 0;
}

