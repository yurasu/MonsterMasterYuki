#pragma once
#include "Common.h"
//担当:鴫原
class Monster {
public:

	CurPos pos;
	int attr;
	CurPos init_pos;
	//コンストラクタ
	Monster(int x, int y, int attr);
	//ステージクリア時のモンスターの初期化
	void init();
	//移動処理
	virtual void move(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2]);
	//移動可能範囲の計算
	virtual void moveable_range(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2]) = 0;
	//移動可能範囲の高さの計算
	virtual void moveable_range_height(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2], int w) = 0;
	//移動できる?
	virtual bool is_moveable(int x,int y,int(&board)[BOARD_WD + 2][BOARD_HT + 2]) = 0;
	//死亡時処理
	virtual void dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2],int x, int y) = 0;
	//属性は有利?
	virtual int is_attr_advance(int attr)=0;
	//勝ってる?
	virtual bool is_Victory(int attr)=0;
	//引き分け?
	virtual bool is_Drow(int attr)=0;
	//死んでる?
	virtual bool is_dead() = 0;
	//属性取得
	virtual int getAttr();
};