#pragma once
#include "Common.h"
#include "Monster.h"
#include "EnemyMonster.h"
//担当:鴫原
//お兄様クラス
class Brother_like :public EnemyMonster {
public:
	//コンストラクタ
	Brother_like(int x, int y, int attr);
	//HP
	int hp = 3;
	//死ぬ歳の処理
	void dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2],int x, int y);
	//属性の変更(担当Nam)
	void change_attr();
	//属性の取得
	void move(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2]) override;
	//自分の属性を渡す
	int getAttr() override;
};