#pragma once
#include <Windows.h>
#include <string>
#include "Common.h"
//担当フジタ
class DblBuffer
{
public:
	//コンストラクタ
	DblBuffer();
	//デストラクタ
	~DblBuffer();

public:
	//色設定
	void setColor(int);
	//色設定
	void setColor(int, int);
	//コンソールカーソル座標の設定
	void setCursorPos(int, int);
	//文字を書き込む
	void write(const char *);
	//文字を書き込む
	void write(const wchar_t *);
	//文字を書き込む
	void write(const std::string &);
	//文字を書き込む
	void write(const std::wstring &);
	//バッファを入れ替える
	void swap();
	//バッファのサイズを設定
	void getBuffSize(CurPos &size);
	//バッファをクリーンにする
	void clearBuff();

private:
	bool			m_swapped;
	HANDLE		m_hCons1;		//	コンソールハンドルその１
	HANDLE		m_hCons2;		//	コンソールハンドルその２
};