#ifndef _LAMP_H
#define _LAMP_H

enum LampState{ LAMP_ON, LAMP_OFF, LAMP_FLASH_FAST, LAMP_FLASH_SLOW };

class lamp
{
public:
	lamp();
	~lamp();
	void startup(int _row, int _col);

  LampState state;  //use accessors?
private:
	int row, col;
};

#endif //_LAMP_H