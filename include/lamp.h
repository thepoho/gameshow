//#pragma once
#ifndef _LAMP_H
#define _LAMP_H
#include <iostream>
class lamp
{
public:
	lamp();
	~lamp();
	void startup(int _row, int _col);
private:
	int row, col;
};

#endif