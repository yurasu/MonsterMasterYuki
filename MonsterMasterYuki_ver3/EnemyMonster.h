#pragma once
#include "Common.h"
#include "Monster.h"
#include "AllyMonster.h"
//�S��:����
class EnemyMonster : public Monster{
public:
	int bonus = 0;
	int action_monster_attr = CHOKI;
	//����ł��邩�ǂ���
	bool dead = true;
	//�����͗L���ł���
	int is_attr_advance(int attr) override;
	//����ł���̂�
	bool is_dead() override;
	//���ʍۂ̏���
	virtual void dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2],int x,int y) override;
	//�R���X�g���N�^
	EnemyMonster(int x, int y, int attr);
	//�ړ��\�͈͂̌v�Z
	void moveable_range(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2]) override;
	//�ړ��\�͈͂̍����̌v�Z
	void moveable_range_height(vector<CurPos> &v, int(&board)[BOARD_WD + 2][BOARD_HT + 2], int w) override;
	int move_evaluation(AllyMonster *monsters[], int length, CurPos next_pos, int action_attr);
	int self_evaluation(AllyMonster *monsters[], int length, int action_attr);
	void self_evaluation_Defeat(int w, int h , int &evaluation);
	void self_evaluation_Drow(int w, int h, int &evaluation);
	void self_evaluation_Victory(int w, int h, int &evaluation);
	bool is_Victory(int attr) override;
	bool is_Drow(int attr) override;
	bool is_moveable(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2]) override;
};