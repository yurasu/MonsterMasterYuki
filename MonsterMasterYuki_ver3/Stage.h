#pragma once
#include "Common.h"
#include "AllyMonster.h"
#include "EnemyMonster.h"
#include "Brother_like.h"
#include "Trap.h"

class StagePrinter;
//基本的には担当フジタ
class Stage {
public:
	StagePrinter *s_printer = nullptr;
	int board[BOARD_WD+2][BOARD_HT+2];
	int victory_enemy = 0;
	int yuki_life;         // 座標値タイプ定義
	int monsters_length;
	int emonsters_length;
	int traps_length = 3;
	int action_monster = CHOKI;
	bool move_print = false;
	bool player_turn = true;
	int stage_number = 1;
	int move_monster;
	bool help = false;
	CurPos player_curpos;
	AllyMonster **pmonster;
	EnemyMonster **penemy;
	Trap **traps;
	//コンストラクタ
	Stage(AllyMonster *monster[], int  length, EnemyMonster *emonsters[], int elength, Trap *traps[]);
	//デストラクタ
	~Stage();
	//ヘルプを出す
	void help_stage();
	//ボードを表示
	void b_print();
	//AIの処理
	void AI();
	//ボードの初期化
	void init_board();
	//ステージクリア?
	bool is_stage_clear();
	//プレイヤーのカーソルの移動
	void move_player_cursol(int x, int y);
	//その場所はカーソルが移動できるのか
	bool is_cursol_moveable();
	//ゲームオーバー?
	bool isGameOver();
	//移動するモンスターの番号をセット
	void setMoveMonster();
	//属性のランダム配置 担当:小林
	void attr_shuffle();
	//説明用のテキスト表示 担当:Nam
	void explain();
	void start();
	//それぞれのモンスターの死亡処理 担当:鴫原
	template<class Dead_M> void dead_Monster(Dead_M *monster,int x,int y) {
		if (typeid(*monster) == typeid(AllyMonster)) {
			yuki_life--;
		}
		else if (typeid(*monster) == typeid(Brother_like)) {
			victory_enemy += 2;
		}
		else if (typeid(*monster) != typeid(Trap)) {
			victory_enemy++;
		}
		s_printer->print_board();
		s_printer->draw_board_monsters();
		s_printer->deadAnimation(monster);
		monster->dead_process(this->board,x,y);
		Sleep(60);
	}
	//モンスターの戦闘判定　担当:藤田
	template<class Move_X, class Wait_y> void battle(Move_X *move_m, Wait_y *w_m, int x, int y) {

		switch (w_m->is_attr_advance(move_m->attr)) {
		case VICTORY:
			dead_Monster(move_m,x,y);
			break;
		case DROW:
			dead_Monster(move_m, x, y);
			dead_Monster(w_m, x, y);
			break;
		default:
			dead_Monster(w_m,x,y);
			move_m->move(x, y, board);
			break;
		}
	}
	//モンスターのクラスの違いを気にせずに座標を返す 担当:NAM
	template<class X> bool is_pos(X *monster, int x, int y) {
		if (monster->pos.first == x && monster->pos.second == y) {
			return true;
		}
		return false;
	}

	//モンスターとバトルするか？
	template<class X, class Y> bool is_battle(X **monsters, Y *move_monster, int length, int x, int y) {
		for (int i = 0; i < length; i++) {
			if (monsters[i]->is_dead()) {
				continue;
			}

			if (this->is_pos(monsters[i], x, y)) {
				this->battle(move_monster, monsters[i], x, y);
				return true;
			}
		}
		return false;
	}

};