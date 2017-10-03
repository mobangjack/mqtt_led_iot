#ifndef GPIO_H
#define GPIO_H

#include <string>

class gpio
{
public:
	gpio(std::string port);
	~gpio();
	bool wire(int flag);
	bool isWired();
	int stat();
	bool assign(char val);
	void cutoff();
protected:
	int fd;
	std::string port;
	bool is_wired;
};

#endif

