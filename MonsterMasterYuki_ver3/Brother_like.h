#pragma once
#include "Common.h"
#include "Monster.h"
#include "EnemyMonster.h"
//�S��:����
//���Z�l�N���X
class Brother_like :public EnemyMonster {
public:
	//�R���X�g���N�^
	Brother_like(int x, int y, int attr);
	//HP
	int hp = 3;
	//���ʍ΂̏���
	void dead_process(int(&board)[BOARD_WD + 2][BOARD_HT + 2],int x, int y);
	//�����̕ύX(�S��Nam)
	void change_attr();
	//�����̎擾
	void move(int x, int y, int(&board)[BOARD_WD + 2][BOARD_HT + 2]) override;
	//�����̑�����n��
	int getAttr() override;
};