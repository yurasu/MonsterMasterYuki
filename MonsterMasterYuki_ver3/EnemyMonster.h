#pragma once
#include "Common.h"
#include "Monster.h"
#include "AllyMonster.h"
//担当:鴫原
class EnemyMonster : public Monster{
public:
	int bonus = 0;
	int action_monster_attr = CHOKI;
	//死んでいるかどうか
	bool dead = true;
	//属性は有利ですか
	int is_attr_advance(int attr) override;
	//死んでいるのか
	bool is_dead() override;
	//死ぬ際の処理
	virtual void dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2],int x,int y) override;
	//コンストラクタ
	EnemyMonster(int x, int y, int attr);
	//移動可能範囲の計算
	void moveable_range(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2]) override;
	//移動可能範囲の高さの計算
	void moveable_range_height(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2], int w) override;
	int move_evaluation(AllyMonster *monsters[], int length, CurPos next_pos, int action_attr);
	int self_evaluation(AllyMonster *monsters[], int length, int action_attr);
	void self_evaluation_Defeat(int w, int h , int &evaluation);
	void self_evaluation_Drow(int w, int h, int &evaluation);
	void self_evaluation_Victory(int w, int h, int &evaluation);
	bool is_Victory(int attr) override;
	bool is_Drow(int attr) override;
	bool is_moveable(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2]) override;
};