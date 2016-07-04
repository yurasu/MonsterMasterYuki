#include "Trap.h"


Trap::Trap(int x, int y) : Monster(x,y,TRAP){}

int Trap::is_attr_advance(int attr)
{
	return DROW;
}

bool Trap::is_dead() {
	return this->dead;
}

void Trap::dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2],int x, int y) {
	board[pos.first][pos.second] = 0;
	this->dead = true;
}

void Trap::moveable_range(vector<CurPos>& v, int(&board)[BOARD_WD + 2][BOARD_HT + 2])
{
}

void Trap::moveable_range_height(vector<CurPos>& v, int(&board)[BOARD_WD + 2][BOARD_HT + 2], int w)
{
}

bool Trap::is_moveable(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2])
{
	return false;
}

bool Trap::is_Victory(int attr)
{
	return false;
}

bool Trap::is_Drow(int attr)
{
	return true;
}
