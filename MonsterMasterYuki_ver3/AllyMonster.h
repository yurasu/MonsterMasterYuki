#pragma once
#include "Common.h"
#include "Monster.h"

//�S��:����
class AllyMonster :public Monster{
public:
	//�R���X�g���N�^
	AllyMonster(int x, int y, int attr);
	//�ړ��\�͈�
	void moveable_range(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2]);
	//�ړ��\�͈͂̍����̌v�Z
	void moveable_range_height(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2],int w);
	//���̏ꏊ�͈ړ��ł��܂����H
	bool is_moveable(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2]);
	//���S����
	void dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2],int x, int y);
	//���̑����͗L���ł����H
	int is_attr_advance(int attr) override;
	// �����H
	bool is_Victory(int attr) override;
	//�@��������
	bool is_Drow(int attr) override;
	//______���O�͂�������ł���
	bool is_dead() override;
};