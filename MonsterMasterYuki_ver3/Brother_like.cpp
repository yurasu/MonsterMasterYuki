#include "Brother_like.h"


Brother_like::Brother_like(int x, int y, int attr) : EnemyMonster(x, y, attr) {

}

void Brother_like::move(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2])
{
	int now_x = pos.first;
	int now_y = pos.second;
	int next_attr = board[x][y];
	board[x][y] = getAttr();
	board[now_x][now_y] = next_attr;
	pos.first = x;
	pos.second = y;
}

void Brother_like::dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2], int x,int y) {
	hp--;
	if (this->hp <= 0) {
		board[pos.first][pos.second] = 0;
		dead = true;
	}else {
		change_attr();
		if ((board[init_pos.first][init_pos.second] == MOVE_ABLE || board[init_pos.first][init_pos.second] == this->attr) &&
			!(init_pos.first == x && init_pos.second == y)) {
			move(init_pos.first, init_pos.second, board);
			return;
		}
		for (int i = 0; i < BOARD_WD; i++) {
			if (board[i][1] == MOVE_ABLE) {
				move(i, 1, board);
				return;
			}
		}
	}
}

void Brother_like::change_attr() {
	random_device rnd;
	this->attr = (rnd() % 3) + 11;
}

int Brother_like::getAttr()
{
	return TATUYA;
}
