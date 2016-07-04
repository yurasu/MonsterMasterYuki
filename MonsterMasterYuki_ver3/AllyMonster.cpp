#include "Common.h"
#include "AllyMonster.h"

AllyMonster::AllyMonster(int x, int y, int attr) :Monster(x, y, attr) {}

void AllyMonster::moveable_range(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2]) {
	for (int x = -1; x <= 1; x++) {
		int w = x + pos.first;
		moveable_range_height(v, board, w);
	}
}

void AllyMonster::moveable_range_height(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2], int w) {
	for (int y = -1; y <= 0; y++) {
		// ˆÚ“®‚Å‚«‚é‚©H
		int h = y + pos.second;
		if (is_moveable(w, h, board)) {
			//ˆÚ“®‰Â”\‚È‚çvector‚Ì––”ö‚É’Ç‰Á
			CurPos p;
			p.first = w;
			p.second = h;
			v.push_back(p);
		}
	}
}

int AllyMonster::is_attr_advance(int attr) {
	if (is_Victory(attr)) {
		return VICTORY;
	}
	else if (is_Drow(attr)) {
		return DROW;
	}
	else {
		return DEFEAT;
	}
}

bool AllyMonster::is_Victory(int attr) {
	if ((this->attr == GOO && attr == ENEMY_CHOKI) ||
		(this->attr == PER && attr == ENEMY_GOO) ||
		(this->attr == CHOKI && attr == ENEMY_PER)
		) {
		return true;
	}
	return false;
}

bool AllyMonster::is_Drow(int attr) {
	if ((this->attr == GOO && attr == ENEMY_GOO) ||
		(this->attr == CHOKI && attr == ENEMY_CHOKI) ||
		(this->attr == PER && attr == ENEMY_PER)) {
		return true;
	}
	return false;
}

bool AllyMonster::is_dead()
{
	return false;
}

bool AllyMonster::is_moveable(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2]) {
	if ((board[x][y] != WALL)
		&& (board[x][y] != GOO)
		&& (board[x][y] != CHOKI)
		&& (board[x][y] != PER)
		) {
		return true;
	}
	return false;
}



void AllyMonster::dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2],int x, int y)
{
	if ((board[init_pos.first][init_pos.second] == MOVE_ABLE || board[init_pos.first][init_pos.second] == this->attr) && 
		!(init_pos.first == x && init_pos.second ==y)) {
		move(init_pos.first, init_pos.second, board);
		return;
	}
	for (int i = 0; i < BOARD_WD; i++) {
		if (board[i][BOARD_HT] == MOVE_ABLE) {
			move(i, BOARD_HT, board);
			return;
		}
	}
}





