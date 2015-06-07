#include "lamp.h"

lamp::lamp()
{
}

lamp::~lamp()
{
}

void lamp::startup(int _row, int _col)
{
	row = _row;
	col = _col;
  std::cout << "creating lamp " << row << ", " << col << "\n";
}