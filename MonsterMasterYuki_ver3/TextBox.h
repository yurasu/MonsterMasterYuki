#pragma once
#include "Common.h"
#include "DblBuffer.h"
//担当フジタ
class TextBox {
public:
	CurPos pos;
	CurPos m_pos;
	DblBuffer *buff;
	int wlength; //メッセージの横幅
	int hlength; //メッセージの縦幅
	int flame_wlength;
	int flame_hlength;
	int flame_bg = COL_DARK_RED;
	int message_bg = COL_WHITE;
	string text;
	//コンストラクタ
	TextBox(int wlength, int hlength, DblBuffer *buff);

	//テキストをセットさせる
	void setText(string str);

	//テキストを表示させる
	void showText();

	//テキストボックス
	void DrawMBox(int x, int y, int w, int h);
	//テキストボックスを動かしながら表示
	void animation(int x, int y);
};