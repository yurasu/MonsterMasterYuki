#pragma once
#include "Common.h"
#include "Monster.h"
//�S��:����
class Trap : public Monster{
public:
	bool dead = false;
	//�R���X�g���N�^
	Trap(int x, int y);
	//�L��������
	int is_attr_advance(int attr);
	//�ϐ�dead�̒l��n��
	bool is_dead();
	//���S���̏���
	void dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2],int x, int y);
	//���ۃ��\�b�h�̃I�[�o�[���C�h(�֐��͎g�p���Ȃ�)
	void moveable_range(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2]);
	//���ۃ��\�b�h�̃I�[�o�[���C�h(�֐��͎g�p���Ȃ�)
	void moveable_range_height(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2], int w);
	//���ۃ��\�b�h�̃I�[�o�[���C�h(�֐��͎g�p���Ȃ�)
	bool is_moveable(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2]);
	//���ۃ��\�b�h�̃I�[�o�[���C�h(�֐��͎g�p���Ȃ�)
	bool is_Victory(int attr);
	//���ۃ��\�b�h�̃I�[�o�[���C�h(�֐��͎g�p���Ȃ�)
	bool is_Drow(int attr);
};