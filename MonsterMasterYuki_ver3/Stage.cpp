#include <Windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include "Stage.h"
#include "AllyMonster.h"
#include "EnemyMonster.h"
#include "Brother_like.h"
#include "StagePrinter.h"

Stage::Stage(AllyMonster *monster[], int  length, EnemyMonster *emonsters[], int elength, Trap *traps[]) {
	yuki_life = STARTLIFE;
	pmonster = monster;
	penemy = emonsters;
	monsters_length = length;
	emonsters_length = elength;
	player_curpos.first = 3;
	player_curpos.second = BOARD_HT;
	move_monster = 1;
	this->traps = traps;
	s_printer = new StagePrinter(this);
	init_board();
}

Stage::~Stage()
{
	delete s_printer;
}

void Stage::help_stage()
{
	s_printer->helpText();
}

void Stage::attr_shuffle() {
	random_device rnd;
	int a[] = { ENEMY_CHOKI, ENEMY_GOO, ENEMY_PER };
	for (int i = 0; i < 100; i++) {
		int r = rnd() % 3;
		int s = rnd() % 3;
		int temp = a[s];
		a[s] = a[r];
		a[r] = temp;
	}
	for (int i = 0; i < 3; i++) {
		penemy[i]->attr = a[i];
	}
}

void Stage::explain()
{
	char *text = "魔王 28才\nYUKIと同じ力を持っており上級のモンスターを操ることができる \n何かを隠している様子\n\nAI姫 18才\n 優しい心。\n老若男女以外にもモンスターにも慕われている。\n力を持っているわけではない\nYUKiと恋人だが手をつないだこともない\n\nYUKI 24才\nモンスターを操る立派な召喚士 \nしかしまだスライムしか召喚したことがない\n\nあらすじ\nとある時代戦もなく平和で和やかな国があった。\n皆が幸せな毎日を送っていたが、ある日突然現国王の姫、AI姫が魔王によって連れ去られてしまった。 \nしかも大量のモンスターが押し寄せ国は大混乱となった。\n町はずれに住んでいたYUKIはその知らせを聞き、YUKIは魔王を倒せば平和が取り戻せるはずだと考えた。\nYUKIは国の平和とAI姫を助けるため、勇気を振り絞り魔王を倒す戦いに赴くのであった。\n\n";
	s_printer->flowing_message(text);
	while (true) {
		if (GetAsyncKeyState(VK_RETURN)) {
			Sleep(100);
			break;
		}
	}
	s_printer->clear();
	text = "ゲームのルール  \n\nこのゲームはチェス型の戦略ゲームである。ダンジョンの１ステージは５×５マスで構成されていて、モンスターを駒として戦闘     	\nを行う。モンスターにはグー・チョキ・パーの３種類の属性があり、敵とは属性による３すくみにより戦闘を行う。プレイヤーとCPUと		で交互にモンスターを動かしていく。駒の動かし方には以下の制約がある。  \n動かせる範囲は隣り合う左右２マスと斜めを含む前方の３マス。つまり後退は不可。\nすでに自分の別の駒が配置されているマスには進めない。\nお互いの駒が同じマスで重なると戦闘。３すくみの優位性により勝敗判定がつく。戦闘には以下の条件がある。  \nCPU側が負けたら、その相手の駒はゲームから除外される。  \nプレイヤー側が負けたら、主人公のHPを１減らしてモンスターが初期位置に再召喚される。引き分けの際には、上記の２つを適用   	 \nする。敵の属性は見えない。そのステージの相手のモンスターを全て排除したら勝利。HPを引き継いで次のステージへ進む。	    \n主人公のHPが尽きたらプレイヤーの敗北。\n\nゲームの終了条件\n勝利条件			\nステージの敵を全て倒すか、自分のモンスターで一番奥まで到達するとステージクリア。全４ステージを制覇すればゲームクリアとなる。\n敗北条件\nプレイヤーのHPが尽きるか、敵のモンスターに一番手前まで到達されるとゲームオーバーとなる。      		\n\n[AI姫による操作説明]\nキーボードの[↑][→][↓][←]によって黒色のカーソルが動きます。カーソルをモンスターに合わせてキーボードの[エンターキー]を押すと\n白色でモンスターの移動可能範囲が表示されます。\nさらに、白色で表示された場所にカーソルを合わせて[エンターキー]を押すとモンスターが移動できます。\n\n[バトルについて]\n基本的にはじゃんけんの三すくみを考えてください。\nモンスターはそれぞれの属性に合わせて[グー][チョキ][パー]の属性をもっています。画面には基本的には、[グー]が赤で、[チョキ]が緑で、\n[パー]が水色で表現されています。\n黄色で表現された敵の位置に移動するとバトルが始まり、敵と自分の相性によってどちらかまたは両方が死亡します。\n\n[トラップについて]\n第2ステージのみステージ上のどこかに罠が3つ仕掛けてあります。\nトラップを踏むとトラップの場所と踏んだモンスターが死亡します。\n一度踏めばトラップは解除されますが、同じ場所に2つ仕掛けてある場合があるのでお気をつけて      		";
	s_printer->flowing_message(text);
	while (true) {
		if (GetAsyncKeyState(VK_RETURN)) {
			Sleep(100);
			s_printer->buff.swap();
			s_printer->buff.clearBuff();
			b_print();
			break;
		}
	}
}

void Stage::start()
{
	s_printer->startDraw();
}

void Stage::init_board() {
	s_printer->clear();
	attr_shuffle();
	for (int i = 0; i < emonsters_length; i++) {
		penemy[i]->dead = true;
	}

	for (int x = 0; x < BOARD_WD + 2; ++x) {
		for (int y = 0; y < BOARD_HT + 2; ++y) {
			if (x == 0 || x == BOARD_WD + 1 ||
				y == 0 || y == BOARD_HT + 1)
			{
				this->board[x][y] = WALL;
			}
			else {
				this->board[x][y] = MOVE_ABLE;
			}
		}
	}


	for (int i = 0; i < monsters_length; i++) {
		pmonster[i]->init();
		int test = i;
		int w = pmonster[i]->pos.first;
		int h = pmonster[i]->pos.second;
		this->board[w][h] = pmonster[i]->getAttr();
	}
	int mainas = -3;
	if (stage_number == 3) {
		mainas = -1;
	}
	for (int i = 0; i < emonsters_length + mainas; i++) {
		penemy[i]->dead = false;
	}

	if (stage_number == 4) {

		penemy[1]->dead = true;
		penemy[emonsters_length - 1]->dead = false;
	}

	for (int i = 0; i < emonsters_length; i++) {
		if (penemy[i]->is_dead()) {
			continue;
		}
		penemy[i]->init();
		int w = penemy[i]->pos.first;
		int h = penemy[i]->pos.second;
		board[w][h] = penemy[i]->getAttr();
	}


	if (stage_number == 2) {
		for (int i = 0; i < traps_length; i++) {
			traps[i]->dead = false;
			int w = traps[i]->pos.first;
			int h = traps[i]->pos.second;
			board[w][h] = traps[i]->getAttr();
		}
	}
	else {
		for (int i = 0; i < traps_length; i++) {
			traps[i]->dead = true;
		}
	}
}


void Stage::move_player_cursol(int x, int y) {
	int w = player_curpos.first + x;
	int h = player_curpos.second + y;
	if (board[w][h] != WALL) {
		player_curpos.first = w;
		player_curpos.second = h;
	}
}
void Stage::setMoveMonster() {
	for (int i = 0; i < monsters_length; i++) {
		if (pmonster[i]->pos.first == player_curpos.first && pmonster[i]->pos.second == player_curpos.second) {
			move_monster = i;
			action_monster = pmonster[i]->attr;
			return;
		}
	}
}


bool Stage::is_cursol_moveable() {
	vector<CurPos> v;
	pmonster[move_monster]->moveable_range(v, board);
	for (auto itr = v.begin(); itr != v.end(); itr++) {
		int w = itr->first;
		int h = itr->second;
		if (w == player_curpos.first && h == player_curpos.second) {
			if (!(is_battle(penemy, pmonster[move_monster], emonsters_length, w, h)) &&
				!(is_battle(traps, pmonster[move_monster], traps_length, w, h))) {
				CurPos next;
				next.first = w;
				next.second = h;
				s_printer->DrawMonsterAnimation(pmonster[move_monster]->getAttr(), pmonster[move_monster]->pos, next);
				pmonster[move_monster]->move(w, h, board);
				b_print();
			}
			return true;
		}

	}
	return false;
}

bool Stage::isGameOver() {
	if (yuki_life <= 0) {
		return true;
	}
	for (int i = 0; i < emonsters_length; i++) {
		for (int t = 1; t <= 5; t++) {
			if (penemy[i]->pos.first == t && penemy[i]->pos.second == BOARD_HT) {
				b_print();
				Sleep(1200);
				s_printer->result();
				stage_number = 1;
				yuki_life = STARTLIFE;
				init_board();
				return true;
			}
		}
	}
	return false;

}


void Stage::b_print()
{
	s_printer->print_board();
	s_printer->draw_board_monsters();
	s_printer->buff.swap();
	s_printer->clear();
}

void Stage::AI() {
	player_turn = false;
	int e = 0;
	for (int i = 0; i < emonsters_length; i++) {
		if (penemy[i]->is_dead()) {
			continue;
		}
		else {
			e = i;
		}
	}

	int evaluation = -1000;
	CurPos next;
	for (int i = 0; i < emonsters_length; i++) {
		if (penemy[i]->is_dead()) {
			continue;
		}
		vector<CurPos> v;
		penemy[i]->moveable_range(v, board);
		for (auto itr = v.begin(); itr != v.end(); itr++) {
			int nextevaluation = penemy[i]->move_evaluation(pmonster, monsters_length, *itr, action_monster);

			if (nextevaluation > evaluation) {
				evaluation = nextevaluation;
				e = i;
				next = *itr;
			}
		}
		penemy[i]->action_monster_attr = action_monster;
	}
	if (!(is_battle(pmonster, penemy[e], monsters_length, next.first, next.second)) &&
		!(is_battle(traps, penemy[e], traps_length, next.first, next.second))) {
		s_printer->DrawMonsterAnimation(penemy[e]->getAttr(), penemy[e]->pos, next);
		penemy[e]->move(next.first, next.second, board);
		b_print();
	}
	player_turn = true;
}


bool Stage::is_stage_clear() {

	for (int i = 0; i < monsters_length; i++) {
		int x = pmonster[i]->pos.first;
		int y = pmonster[i]->pos.second;
		for (int s = 1; s <= BOARD_WD; s++) {
			if (y == 1 && x == s) {
				stage_number++;
				if (stage_number == 5) {
					s_printer->result(true);
					stage_number = 1;
					yuki_life = STARTLIFE;
					b_print();
				}
				s_printer->clear();
				return true;
			}
		}
	}
	for (int i = 0; i < emonsters_length; i++) {
		if (!(penemy[i]->is_dead())) {
			return false;
		}
	}
	stage_number++;
	if (stage_number == 5) {
		s_printer->result(true);
		stage_number = 1;
		yuki_life = STARTLIFE;
		b_print();
	}
	return true;
}