#include "gpio.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>   //define O_WRONLY and O_RDONLY

gpio::gpio(std::string port)
{
	this->fd = -1;
	this->port = port;
	this->is_wired = false;
}

bool gpio::wire(int flag)
{
	fd = open(port.c_str(), flag);
	if (fd != -1)
	{
		is_wired = true;
	}
	else
	{
		is_wired = false;
	}
	return is_wired;
}

bool gpio::isWired()
{
	return this->is_wired;
}

int gpio::stat()
{
	if (!is_wired)
	{
		return -1;
	}
	char buf[2];
	memset(buf, 0, 2 * sizeof(char));
	int len = read(fd, buf, 1);
	if (len != 1)
	{
		return -1;
	}
	lseek(fd, 0, SEEK_SET); // important!!!
	return buf[0];
}

bool gpio::assign(char val)
{
	if (!is_wired)
	{
		return false;
	}
	int len = write(fd, &val, 1);
	if (len != 1)
	{
		return false;
	}
	return true;
}

void gpio::cutoff()
{
	if (fd != -1)
	{
		close(fd);
		fd = -1;
	}
	is_wired = false;
}

gpio::~gpio()
{
	cutoff();
}

