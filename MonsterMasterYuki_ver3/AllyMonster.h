#pragma once
#include "Common.h"
#include "Monster.h"

//担当:梁川
class AllyMonster :public Monster{
public:
	//コンストラクタ
	AllyMonster(int x, int y, int attr);
	//移動可能範囲
	void moveable_range(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2]);
	//移動可能範囲の高さの計算
	void moveable_range_height(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2],int w);
	//その場所は移動できますか？
	bool is_moveable(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2]);
	//死亡処理
	void dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2],int x, int y);
	//その属性は有利ですか？
	int is_attr_advance(int attr) override;
	// 勝ち？
	bool is_Victory(int attr) override;
	//　引き分け
	bool is_Drow(int attr) override;
	//______お前はもう死んでいる
	bool is_dead() override;
};