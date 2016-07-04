#pragma once
#include <Windows.h>
#include <conio.h>        //  _getch
#include <time.h>         //  time
#include <random>
#include <iostream>
#include <sstream>      // std::ostringstream
#include <string>
using namespace std;
#define     WALL                -1          //  -1�͈ړ��s�̔���̂���
#define     BOARD_WD        5           //  �{�[�h��
#define     BOARD_HT        5           //  �{�[�h����
#define     CELL_WIDTH  10          //  �Z���\����
#define     MOVE_ABLE   0
#define     TRAP    20 //�g���b�v
#define		TATUYA 50
#define		STARTLIFE 15

//�����ݒ�
#define     GOO       1       //�O�[
#define     CHOKI      2       //�`���L
#define     PER       3       //�p�[


//�G�����ݒ�
#define     ENEMY_GOO     11      //�O�[
#define     ENEMY_CHOKI        12      //�`���L
#define     ENEMY_PER     13      //�p�[


#define     VICTORY     1
#define     DROW        0
#define     DEFEAT      -1



//�F�w��

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
#define     COL_INTENSITY       0x08        //  ���P�x�}�X�N
#define     COL_RED_MASK        0x04
#define     COL_GREEN_MASK  0x02
#define     COL_BLUE_MASK   0x01

typedef pair<int, int> CurPos;          // ���W�l�^�C�v��`