#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <locale.h>
#include <random>
#include "Monster.h"
#include "DblBuffer.h"
#include "TextBox.h"

class Stage;
//担当フジタ

class StagePrinter {
public:
	Stage *s = nullptr;
	//ダブルバッファのオブジェクト
	DblBuffer buff;
	//コンストラクタ
	StagePrinter(Stage *stage);
	//ボードを表示
	void print_board();
	//一行ずつ表示
	void print_line(int y, bool printval);
	//一行表示
	void line_write(bool printval, bool monsterstr = false,int attr = MOVE_ABLE);
	//移動可能範囲の表示
	void movable_draw(vector<CurPos> v, int x, int y);
	//属性の文字を返す
	char* str_attribute(int v);
	//モンスターの色を変える
	void setMonsterColor(int v);
	//モンスターを表示する
	void draw_board_monsters(int x = 0, int y = 0, bool animation = false);
	//ボードをきれいにする
	void clear();
	//助けてアイちゃーん
	void helpText();
	//死亡時のアニメーション処理やで
	void deadAnimation(Monster *m);
	//リザルト
	void result(bool clear=false);
	//よこの説明
	void show_explanatory_text();
	//ボードでの位置とバッファの位置を変換する
	CurPos mapping_coordinate(CurPos &now_pos, CurPos &pos);
	//モンスターを個別に表示
	void DrawMonster(int x, int y, int attr, CurPos pos);
	//モンスターの移動モーションを表示
	void DrawMonsterAnimation(int attr, CurPos now_pos, CurPos next_pos);
	//流れるメッセージ
	void flowing_message(char *text);
	void drawChar(int array[7][9], int y_length, int x_length, CurPos init_pos, int fgCOL, int bgCOL);
	void startDraw();


	// A
	int drow1[7][9] = {
		{ 0,0,1,1,1,1,1,0,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,1,1,1,1,1,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
	};

	// B
	int drow2[7][9] = {
		{ 0,1,1,1,1,1,1,0,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,1,1,1,1,1,0,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,1,1,1,1,1,0,0 },
	};

	// C
	int drow3[7][9] = {
		{ 0,1,1,1,1,1,1,0,0 },
		{ 1,1,0,0,0,0,0,1,0 },
		{ 1,1,0,0,0,0,0,0,0 },
		{ 1,1,0,0,0,0,0,0,0 },
		{ 1,1,0,0,0,0,0,0,0 },
		{ 1,1,0,0,0,0,0,1,0 },
		{ 0,1,1,1,1,1,1,0,0 },
	};

	// D
	int drow4[7][9] = {
		{ 0,1,1,1,1,1,1,0,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,1,1,1,1,1,0,0 },
	};

	//E
	int drow5[7][9] = {
		{ 0,1,1,1,1,1,1,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,1,1,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,1,1,0,0 },
	};

	// F
	int drow6[7][9] = {
		{ 0,1,1,1,1,1,1,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,1,1,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
	};

	//G
	int drow7[7][9] = {
		{ 0,1,1,1,1,1,1,0,0 },
		{ 1,1,0,0,0,0,0,1,0 },
		{ 1,1,0,0,0,0,0,0,0 },
		{ 1,1,0,0,0,0,0,0,0 },
		{ 1,1,0,0,0,1,1,1,0 },
		{ 1,1,0,0,0,0,0,1,0 },
		{ 0,1,1,1,1,1,1,0,0 },
	};

	// H
	int drow8[7][9] = {
		{ 0,1,0,0,0,0,1,0,0 },
		{ 0,1,0,0,0,0,1,0,0 },
		{ 0,1,0,0,0,0,1,0,0 },
		{ 0,1,1,1,1,1,1,0,0 },
		{ 0,1,0,0,0,0,1,0,0 },
		{ 0,1,0,0,0,0,1,0,0 },
		{ 0,1,0,0,0,0,1,0,0 },
	};

	//I
	int drow9[7][9] = {
		{ 0,0,1,1,1,1,1,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,1,1,1,1,1,0,0 },
	};

	//J
	int drow10[7][9] = {
		{ 0,0,0,1,1,1,1,1,0 },
		{ 0,0,0,0,0,1,0,0,0 },
		{ 0,0,0,0,0,1,0,0,0 },
		{ 0,0,0,0,0,1,0,0,0 },
		{ 1,0,0,0,0,1,0,0,0 },
		{ 1,1,0,0,0,1,0,0,0 },
		{ 0,1,1,1,1,1,0,0,0 },
	};


	// K
	int drow11[7][9] = {
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,1,0,0 },
		{ 0,1,0,0,0,1,0,0,0 },
		{ 0,1,1,1,1,0,0,0,0 },
		{ 0,1,0,0,0,1,0,0,0 },
		{ 0,1,0,0,0,0,1,0,0 },
		{ 0,1,0,0,0,0,0,1,0 },
	};

	//L
	int drow12[7][9] = {
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,1,1,1,0 },
	};

	//M
	int drow13[7][9] = {
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,1,0,0,0,1,1,0 },
		{ 0,1,0,1,0,1,0,1,0 },
		{ 0,1,0,0,1,0,0,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
	};

	//N
	int drow14[7][9] = {
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,1,0,0,0,0,1,0 },
		{ 0,1,0,1,0,0,0,1,0 },
		{ 0,1,0,0,1,0,0,1,0 },
		{ 0,1,0,0,0,1,0,1,0 },
		{ 0,1,0,0,0,0,1,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
	};


	//O
	int drow15[7][9] = {
		{ 0,0,1,1,1,1,0,0,0 },
		{ 0,1,0,0,0,0,1,0,0 },
		{ 1,0,0,0,0,0,0,1,0 },
		{ 1,0,0,0,0,0,0,1,0 },
		{ 1,0,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,1,0,0 },
		{ 0,0,1,1,1,1,0,0,0 },
	};

	//P
	int drow16[7][9] = {
		{ 0,1,1,1,1,1,0,0,0 },
		{ 0,1,0,0,0,0,1,0,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,1,0,0 },
		{ 0,1,1,1,1,1,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0 },
	};

	//Q
	int drow17[7][9] = {
		{ 0,0,1,1,1,1,0,0,0 },
		{ 0,1,0,0,0,0,1,0,0 },
		{ 1,0,0,0,0,0,0,1,0 },
		{ 1,0,0,0,0,0,0,1,0 },
		{ 1,0,0,0,0,1,0,1,0 },
		{ 0,1,0,0,0,0,1,0,0 },
		{ 0,0,1,1,1,1,0,1,0 },
	};

	//R
	int drow18[7][9] = {
		{ 1,1,1,1,1,1,0,0,0 },
		{ 1,0,0,0,0,0,1,0,0 },
		{ 1,0,0,0,0,0,1,0,0 },
		{ 1,0,0,0,0,0,1,0,0 },
		{ 1,1,1,1,1,1,0,0,0 },
		{ 1,0,0,0,0,0,1,0,0 },
		{ 1,0,0,0,0,0,0,1,1 },
	};

	//S
	int drow19[7][9] = {
		{ 0,0,1,1,1,1,1,0,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,0,0,0 },
		{ 0,0,1,1,1,1,1,0,0 },
		{ 0,0,0,0,0,0,0,1,0 },
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,0,1,1,1,1,1,0,0 },
	};

	//T
	int drow20[7][9] = {
		{ 0,1,1,1,1,1,1,1,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
	};

	//U
	int drow21[7][9] = {
		{ 1,0,0,0,0,0,0,1,0 },
		{ 1,0,0,0,0,0,0,1,0 },
		{ 1,0,0,0,0,0,0,1,0 },
		{ 1,0,0,0,0,0,0,1,0 },
		{ 1,0,0,0,0,0,0,1,0 },
		{ 1,0,0,0,0,0,0,1,0 },
		{ 0,1,1,1,1,1,1,0,0 },
	};

	//V
	int drow22[7][13] = {
		{ 0,0,0,1,0,0,0,0,0,1,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,1,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,1,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,1,0,0,0 },
		{ 0,0,0,0,1,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,0,1,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,1,0,0,0,0,0,0 },
	};

	//W
	int drow23[7][13] = {
		{ 0,0,1,0,0,0,0,0,0,0,1,0,0 },
		{ 0,0,1,0,0,0,0,0,0,0,1,0,0 },
		{ 0,0,1,0,0,0,0,0,0,0,1,0,0 },
		{ 0,0,1,0,0,0,0,0,0,0,1,0,0 },
		{ 0,0,1,0,0,0,1,0,0,0,1,0,0 },
		{ 0,0,1,0,0,0,1,0,0,0,1,0,0 },
		{ 0,0,0,1,1,1,0,1,1,1,0,0,0 },
	};

	//X
	int drow24[7][9] = {
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,0,1,0,0,0,1,0,0 },
		{ 0,0,0,1,0,1,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,1,0,1,0,0,0 },
		{ 0,0,1,0,0,0,1,0,0 },
		{ 0,1,0,0,0,0,0,1,0 },
	};

	//Y
	int drow25[7][9] = {
		{ 0,1,0,0,0,0,0,1,0 },
		{ 0,0,1,0,0,0,1,0,0 },
		{ 0,0,0,1,0,1,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0 },
	};

	//Z
	int drow26[7][13] = {
		{ 0,0,1,1,1,1,1,1,1,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,0,1,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,0,0,0 },
		{ 0,0,1,1,1,1,1,1,1,0,0,0,0 },
	};

	//0
	int drow27[7][13] = {
		{ 0,0,0,0,0,1,1,1,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,1,0,0,0,0 },
		{ 0,0,0,1,0,0,0,1,0,1,0,0,0 },
		{ 0,0,0,1,0,0,1,0,0,1,0,0,0 },
		{ 0,0,0,1,0,1,0,0,0,1,0,0,0 },
		{ 0,0,0,0,1,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,0,1,1,1,0,0,0,0,0 },
	};

};