#include "Monster.h"

Monster::Monster(int x, int y, int attr) {
	pos.first = x;
	pos.second = y;
	init_pos.first = x;
	init_pos.second = y;
	this->attr = attr;
}

void Monster::init() {
	pos.first = init_pos.first;
	pos.second = init_pos.second;
}


void Monster::move(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2])
{
	int now_x = pos.first;
	int now_y = pos.second;
	int next_attr = board[x][y];
	board[x][y] = getAttr();
	board[now_x][now_y] = next_attr;
	pos.first = x;
	pos.second = y;
}

int Monster::getAttr()
{
	return this->attr;
}
