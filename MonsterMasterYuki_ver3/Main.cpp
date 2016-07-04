#include <Windows.h>
#include "Common.h"
#include "AllyMonster.h"
#include "EnemyMonster.h"
#include "Brother_like.h"
#include "Trap.h"
#include "Stage.h"
#include "StagePrinter.h"


int main() {
	random_device rnd;
	AllyMonster *monsters[] = { &AllyMonster(1, 5, GOO), &AllyMonster(3, BOARD_HT, CHOKI), &AllyMonster(5, BOARD_HT, PER) };
	EnemyMonster *emonsters[] = { &EnemyMonster(1,1, ENEMY_CHOKI), &EnemyMonster(3,1,ENEMY_GOO), &EnemyMonster(5,1,ENEMY_PER),
		&EnemyMonster(2,1,(rnd() % 3) + 11), &EnemyMonster(4,1,(rnd() % 3) + 11), &Brother_like(3, 1, (rnd() % 3) + 11) };
	Trap *traps[] = { &Trap((rnd() % 3) + 2,(rnd() % 3) + 2),&Trap((rnd() % 3) + 2,(rnd() % 3) + 2) ,&Trap((rnd() % 3) + 2,(rnd() % 3) + 2) };
	Stage stage(monsters, sizeof(monsters) / sizeof(monsters[0]), emonsters, sizeof(emonsters) / sizeof(emonsters[0]), traps);
	stage.start();
	stage.explain();
	while (true) {
		Sleep(100);
		if (GetAsyncKeyState(0x48)) {
			if (stage.help) {
				stage.help = false;
				stage.help_stage();
			}
			else {
				stage.help = true;
				stage.help_stage();
			}
		}
		if (stage.help) {
			continue;
		}
		stage.b_print();
		if (GetAsyncKeyState(VK_UP)) {
			stage.move_player_cursol(0, -1);
		}
		else if (GetAsyncKeyState(VK_LEFT)) {
			stage.move_player_cursol(-1, 0);
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			stage.move_player_cursol(1, 0);
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			stage.move_player_cursol(0, 1);
		}
		else if (GetAsyncKeyState(VK_RETURN)) {
			stage.setMoveMonster();
			if (stage.is_cursol_moveable()) {
				if (stage.isGameOver()) {
					break;
				}
				else if (stage.is_stage_clear()) {
					stage.init_board();
					continue;
				}
				stage.AI();
				if (stage.isGameOver()) {
					continue;
				}
				else if (stage.is_stage_clear()) {
					stage.init_board();
					continue;
				}
			}
		}
	}
	return 0;
}