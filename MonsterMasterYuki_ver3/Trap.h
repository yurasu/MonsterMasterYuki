#pragma once
#include "Common.h"
#include "Monster.h"
//担当:小林
class Trap : public Monster{
public:
	bool dead = false;
	//コンストラクタ
	Trap(int x, int y);
	//有利か判定
	int is_attr_advance(int attr);
	//変数deadの値を渡す
	bool is_dead();
	//死亡時の処理
	void dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2],int x, int y);
	//抽象メソッドのオーバーライド(関数は使用しない)
	void moveable_range(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2]);
	//抽象メソッドのオーバーライド(関数は使用しない)
	void moveable_range_height(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2], int w);
	//抽象メソッドのオーバーライド(関数は使用しない)
	bool is_moveable(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2]);
	//抽象メソッドのオーバーライド(関数は使用しない)
	bool is_Victory(int attr);
	//抽象メソッドのオーバーライド(関数は使用しない)
	bool is_Drow(int attr);
};