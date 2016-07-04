#pragma once
#include <Windows.h>
#include <conio.h>        //  _getch
#include <time.h>         //  time
#include <random>
#include <iostream>
#include <sstream>      // std::ostringstream
#include <string>
using namespace std;
#define     WALL                -1          //  -1は移動不可の判定のため
#define     BOARD_WD        5           //  ボード幅
#define     BOARD_HT        5           //  ボード高さ
#define     CELL_WIDTH  10          //  セル表示幅
#define     MOVE_ABLE   0
#define     TRAP    20 //トラップ
#define		TATUYA 50
#define		STARTLIFE 15

//属性設定
#define     GOO       1       //グー
#define     CHOKI      2       //チョキ
#define     PER       3       //パー


//敵属性設定
#define     ENEMY_GOO     11      //グー
#define     ENEMY_CHOKI        12      //チョキ
#define     ENEMY_PER     13      //パー


#define     VICTORY     1
#define     DROW        0
#define     DEFEAT      -1



//色指定

#define     COL_BLACK   0x00
#define     COL_DARK_BLUE       0x01
#define     COL_DARK_GREEN  0x02
#define     COL_DARK_CYAN       0x03
#define     COL_DARK_RED        0x04
#define     COL_DARK_VIOLET 0x05
#define     COL_DARK_YELLOW 0x06
#define     COL_GRAY    0x07
#define     COL_LIGHT_GRAY      0x08
#define     COL_BLUE        0x09
#define     COL_GREEN   0x0a
#define     COL_CYAN        0x0b
#define     COL_RED     0x0c
#define     COL_VIOLET  0x0d
#define     COL_YELLOW  0x0e
#define     COL_WHITE   0x0f
#define     COL_INTENSITY       0x08        //  高輝度マスク
#define     COL_RED_MASK        0x04
#define     COL_GREEN_MASK  0x02
#define     COL_BLUE_MASK   0x01

typedef pair<int, int> CurPos;          // 座標値タイプ定義