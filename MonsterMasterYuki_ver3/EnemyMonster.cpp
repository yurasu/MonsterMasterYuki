#include "Common.h"
#include <stdlib.h>
#include "AllyMonster.h"
#include "EnemyMonster.h"

EnemyMonster::EnemyMonster(int x, int y, int attr) :Monster(x, y, attr) {
}


int EnemyMonster::is_attr_advance(int attr) {
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

bool EnemyMonster::is_Victory(int attr) {
	if ((attr == PER && this->attr == ENEMY_CHOKI) ||
		(attr == CHOKI && this->attr == ENEMY_GOO) ||
		(attr == GOO && this->attr == ENEMY_PER)
		) {
		return true;
	}
	return false;
}

bool EnemyMonster::is_Drow(int attr) {
	if ((attr == GOO && this->attr == ENEMY_GOO) ||
		(attr == CHOKI && this->attr == ENEMY_CHOKI) ||
		(attr == PER && this->attr == ENEMY_PER)) {
		return true;
	}
	return false;
}

bool EnemyMonster::is_dead() {
	return this->dead;
}

void EnemyMonster::dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2], int x, int y) {
	board[pos.first][pos.second] = 0;
	this->dead = true;
	Sleep(10);
}

void EnemyMonster::moveable_range(vector<CurPos>& v, int(&board)[BOARD_WD + 2][BOARD_HT + 2])
{
	for (int x = -1; x <= 1; x++) {
		int w = x + pos.first;
		moveable_range_height(v, board, w);
	}
}

void EnemyMonster::moveable_range_height(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2], int w) {
	for (int y = 0; y <= 1; y++) {
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

bool EnemyMonster::is_moveable(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2])
{
	if ((board[x][y] != WALL)
		&& (board[x][y] != ENEMY_GOO)
		&& (board[x][y] != ENEMY_CHOKI)
		&& (board[x][y] != ENEMY_PER)
		&& (board[x][y] != TATUYA)
		&& !(x == pos.first &&y == pos.second)
		) {
		return true;
	}

	return false;
}

int EnemyMonster::self_evaluation(AllyMonster *monsters[], int length, int action_attr) {
	int evaluation = 0;
	if (is_attr_advance(action_attr) == VICTORY) {
		evaluation += 5;
	}
	for (int i = 0; i < length; i++) {
		int attr = monsters[i]->attr;
		int advan = is_attr_advance(attr);
		int w = monsters[i]->pos.first;
		int h = monsters[i]->pos.second;
		if (advan == VICTORY) {
			self_evaluation_Victory(w, h, evaluation);
		}
		else if (advan == DROW) {
			self_evaluation_Drow(w, h, evaluation);
		}
		else {
			self_evaluation_Defeat(w, h, evaluation);
		}
	}
	return evaluation;
}

void EnemyMonster::self_evaluation_Defeat(int w, int h, int &evaluation) {
	evaluation -= (7 - abs(h - pos.second));
	if ((h - pos.second) == 0 && (w - pos.first) == 0) {
		evaluation -= 10000;
	}
	if (abs(h - pos.second) <= 2) {
		evaluation += abs(w - pos.first);
	}
}

void EnemyMonster::self_evaluation_Drow(int w, int h, int & evaluation)
{
	evaluation += 15 - (abs(h - pos.second));
	if ((h - pos.second) == 0 && (w - pos.first) == 0) {
		evaluation += 40000;
	}
	evaluation += (6- abs(w - pos.first));
}

void EnemyMonster::self_evaluation_Victory(int w, int h, int & evaluation)
{
	evaluation += 25 - (abs(h - pos.second));
	if ((h - pos.second) == 0 && (w - pos.first) == 0) {
		evaluation += 50000;
	}
	evaluation += (12 - (abs(w - pos.first)*2));
}

int EnemyMonster::move_evaluation(AllyMonster *monsters[], int length, CurPos next_pos, int action_attr) {
	if (action_monster_attr == action_attr) {
		bonus += 10;
	}
	else {
		bonus = 0;
	}
	int now_x = pos.first;
	int now_y = pos.second;
	pos.first = next_pos.first;
	pos.second = next_pos.second;
	int evaluation = self_evaluation(monsters, length, action_attr);
	/*if (is_attr_advance(action_monster_attr) == VICTORY) {
		evaluation += bonus;
		}
	*/
	pos.first = now_x;
	pos.second = now_y;
	return evaluation;
}