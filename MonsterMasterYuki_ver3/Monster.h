#pragma once
#include "Common.h"
//�S��:����
class Monster {
public:

	CurPos pos;
	int attr;
	CurPos init_pos;
	//�R���X�g���N�^
	Monster(int x, int y, int attr);
	//�X�e�[�W�N���A���̃����X�^�[�̏�����
	void init();
	//�ړ�����
	virtual void move(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2]);
	//�ړ��\�͈͂̌v�Z
	virtual void moveable_range(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2]) = 0;
	//�ړ��\�͈͂̍����̌v�Z
	virtual void moveable_range_height(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2], int w) = 0;
	//�ړ��ł���?
	virtual bool is_moveable(int x,int y,int(&board)[BOARD_WD + 2][BOARD_HT + 2]) = 0;
	//���S������
	virtual void dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2],int x, int y) = 0;
	//�����͗L��?
	virtual int is_attr_advance(int attr)=0;
	//�����Ă�?
	virtual bool is_Victory(int attr)=0;
	//��������?
	virtual bool is_Drow(int attr)=0;
	//����ł�?
	virtual bool is_dead() = 0;
	//�����擾
	virtual int getAttr();
};