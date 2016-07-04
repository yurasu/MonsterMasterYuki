#pragma once
#include "Common.h"
#include "AllyMonster.h"
#include "EnemyMonster.h"
#include "Brother_like.h"
#include "Trap.h"

class StagePrinter;
//��{�I�ɂ͒S���t�W�^
class Stage {
public:
	StagePrinter *s_printer = nullptr;
	int board[BOARD_WD+2][BOARD_HT+2];
	int victory_enemy = 0;
	int yuki_life;         // ���W�l�^�C�v��`
	int monsters_length;
	int emonsters_length;
	int traps_length = 3;
	int action_monster = CHOKI;
	bool move_print = false;
	bool player_turn = true;
	int stage_number = 1;
	int move_monster;
	bool help = false;
	CurPos player_curpos;
	AllyMonster **pmonster;
	EnemyMonster **penemy;
	Trap **traps;
	//�R���X�g���N�^
	Stage(AllyMonster *monster[], int  length, EnemyMonster *emonsters[], int elength, Trap *traps[]);
	//�f�X�g���N�^
	~Stage();
	//�w���v���o��
	void help_stage();
	//�{�[�h��\��
	void b_print();
	//AI�̏���
	void AI();
	//�{�[�h�̏�����
	void init_board();
	//�X�e�[�W�N���A?
	bool is_stage_clear();
	//�v���C���[�̃J�[�\���̈ړ�
	void move_player_cursol(int x, int y);
	//���̏ꏊ�̓J�[�\�����ړ��ł���̂�
	bool is_cursol_moveable();
	//�Q�[���I�[�o�[?
	bool isGameOver();
	//�ړ����郂���X�^�[�̔ԍ����Z�b�g
	void setMoveMonster();
	//�����̃����_���z�u �S��:����
	void attr_shuffle();
	//�����p�̃e�L�X�g�\�� �S��:Nam
	void explain();
	void start();
	//���ꂼ��̃����X�^�[�̎��S���� �S��:����
	template<class Dead_M> void dead_Monster(Dead_M *monster,int x,int y) {
		if (typeid(*monster) == typeid(AllyMonster)) {
			yuki_life--;
		}
		else if (typeid(*monster) == typeid(Brother_like)) {
			victory_enemy += 2;
		}
		else if (typeid(*monster) != typeid(Trap)) {
			victory_enemy++;
		}
		s_printer->print_board();
		s_printer->draw_board_monsters();
		s_printer->deadAnimation(monster);
		monster->dead_process(this->board,x,y);
		Sleep(60);
	}
	//�����X�^�[�̐퓬����@�S��:���c
	template<class Move_X, class Wait_y> void battle(Move_X *move_m, Wait_y *w_m, int x, int y) {

		switch (w_m->is_attr_advance(move_m->attr)) {
		case VICTORY:
			dead_Monster(move_m,x,y);
			break;
		case DROW:
			dead_Monster(move_m, x, y);
			dead_Monster(w_m, x, y);
			break;
		default:
			dead_Monster(w_m,x,y);
			move_m->move(x, y, board);
			break;
		}
	}
	//�����X�^�[�̃N���X�̈Ⴂ���C�ɂ����ɍ��W��Ԃ� �S��:NAM
	template<class X> bool is_pos(X *monster, int x, int y) {
		if (monster->pos.first == x && monster->pos.second == y) {
			return true;
		}
		return false;
	}

	//�����X�^�[�ƃo�g�����邩�H
	template<class X, class Y> bool is_battle(X **monsters, Y *move_monster, int length, int x, int y) {
		for (int i = 0; i < length; i++) {
			if (monsters[i]->is_dead()) {
				continue;
			}

			if (this->is_pos(monsters[i], x, y)) {
				this->battle(move_monster, monsters[i], x, y);
				return true;
			}
		}
		return false;
	}

};