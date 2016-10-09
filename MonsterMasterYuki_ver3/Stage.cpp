#include <Windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include "Stage.h"
#include "AllyMonster.h"
#include "EnemyMonster.h"
#include "Brother_like.h"
#include "StagePrinter.h"

Stage::Stage(AllyMonster *monster[], int  length, EnemyMonster *emonsters[], int elength, Trap *traps[]) {
	yuki_life = STARTLIFE;
	pmonster = monster;
	penemy = emonsters;
	monsters_length = length;
	emonsters_length = elength;
	player_curpos.first = 3;
	player_curpos.second = BOARD_HT;
	move_monster = 1;
	this->traps = traps;
	s_printer = new StagePrinter(this);
	init_board();
}

Stage::~Stage()
{
	delete s_printer;
}

void Stage::help_stage()
{
	s_printer->helpText();
}

void Stage::attr_shuffle() {
	random_device rnd;
	int a[] = { ENEMY_CHOKI, ENEMY_GOO, ENEMY_PER };
	for (int i = 0; i < 100; i++) {
		int r = rnd() % 3;
		int s = rnd() % 3;
		int temp = a[s];
		a[s] = a[r];
		a[r] = temp;
	}
	for (int i = 0; i < 3; i++) {
		penemy[i]->attr = a[i];
	}
}

void Stage::explain()
{
	char *text = "���� 28��\nYUKI�Ɠ����͂������Ă���㋉�̃����X�^�[�𑀂邱�Ƃ��ł��� \n�������B���Ă���l�q\n\nAI�P 18��\n �D�����S�B\n�V��j���ȊO�ɂ������X�^�[�ɂ�����Ă���B\n�͂������Ă���킯�ł͂Ȃ�\nYUKi�Ɨ��l��������Ȃ������Ƃ��Ȃ�\n\nYUKI 24��\n�����X�^�[�𑀂闧�h�ȏ����m \n�������܂��X���C�����������������Ƃ��Ȃ�\n\n���炷��\n�Ƃ��鎞�����Ȃ����a�Řa�₩�ȍ����������B\n�F���K���Ȗ����𑗂��Ă������A������ˑR�������̕P�AAI�P�������ɂ���ĘA�ꋎ���Ă��܂����B \n��������ʂ̃����X�^�[�������񂹍��͑卬���ƂȂ����B\n���͂���ɏZ��ł���YUKI�͂��̒m�点�𕷂��AYUKI�͖�����|���Ε��a�����߂���͂����ƍl�����B\nYUKI�͍��̕��a��AI�P�������邽�߁A�E�C��U��i�薂����|���킢�ɕ����̂ł������B\n\n";
	s_printer->flowing_message(text);
	while (true) {
		if (GetAsyncKeyState(VK_RETURN)) {
			Sleep(100);
			break;
		}
	}
	s_printer->clear();
	text = "�Q�[���̃��[��  \n\n���̃Q�[���̓`�F�X�^�̐헪�Q�[���ł���B�_���W�����̂P�X�e�[�W�͂T�~�T�}�X�ō\������Ă��āA�����X�^�[����Ƃ��Đ퓬     	\n���s���B�����X�^�[�ɂ̓O�[�E�`���L�E�p�[�̂R��ނ̑���������A�G�Ƃ͑����ɂ��R�����݂ɂ��퓬���s���B�v���C���[��CPU��		�Ō��݂Ƀ����X�^�[�𓮂����Ă����B��̓��������ɂ͈ȉ��̐��񂪂���B  \n��������ׂ͈͂͗荇�����E�Q�}�X�Ǝ΂߂��܂ޑO���̂R�}�X�B�܂��ނ͕s�B\n���łɎ����̕ʂ̋�z�u����Ă���}�X�ɂ͐i�߂Ȃ��B\n���݂��̋�����}�X�ŏd�Ȃ�Ɛ퓬�B�R�����݂̗D�ʐ��ɂ�菟�s���肪���B�퓬�ɂ͈ȉ��̏���������B  \nCPU������������A���̑���̋�̓Q�[�����珜�O�����B  \n�v���C���[������������A��l����HP���P���炵�ă����X�^�[�������ʒu�ɍď��������B���������̍ۂɂ́A��L�̂Q��K�p   	 \n����B�G�̑����͌����Ȃ��B���̃X�e�[�W�̑���̃����X�^�[��S�Ĕr�������珟���BHP�������p���Ŏ��̃X�e�[�W�֐i�ށB	    \n��l����HP���s������v���C���[�̔s�k�B\n\n�Q�[���̏I������\n��������			\n�X�e�[�W�̓G��S�ē|�����A�����̃����X�^�[�ň�ԉ��܂œ��B����ƃX�e�[�W�N���A�B�S�S�X�e�[�W�𐧔e����΃Q�[���N���A�ƂȂ�B\n�s�k����\n�v���C���[��HP���s���邩�A�G�̃����X�^�[�Ɉ�Ԏ�O�܂œ��B�����ƃQ�[���I�[�o�[�ƂȂ�B      		\n\n[AI�P�ɂ�鑀�����]\n�L�[�{�[�h��[��][��][��][��]�ɂ���č��F�̃J�[�\���������܂��B�J�[�\���������X�^�[�ɍ��킹�ăL�[�{�[�h��[�G���^�[�L�[]��������\n���F�Ń����X�^�[�̈ړ��\�͈͂��\������܂��B\n����ɁA���F�ŕ\�����ꂽ�ꏊ�ɃJ�[�\�������킹��[�G���^�[�L�[]�������ƃ����X�^�[���ړ��ł��܂��B\n\n[�o�g���ɂ���]\n��{�I�ɂ͂���񂯂�̎O�����݂��l���Ă��������B\n�����X�^�[�͂��ꂼ��̑����ɍ��킹��[�O�[][�`���L][�p�[]�̑����������Ă��܂��B��ʂɂ͊�{�I�ɂ́A[�O�[]���ԂŁA[�`���L]���΂ŁA\n[�p�[]�����F�ŕ\������Ă��܂��B\n���F�ŕ\�����ꂽ�G�̈ʒu�Ɉړ�����ƃo�g�����n�܂�A�G�Ǝ����̑����ɂ���Ăǂ��炩�܂��͗��������S���܂��B\n\n[�g���b�v�ɂ���]\n��2�X�e�[�W�̂݃X�e�[�W��̂ǂ�����㩂�3�d�|���Ă���܂��B\n�g���b�v�𓥂ނƃg���b�v�̏ꏊ�Ɠ��񂾃����X�^�[�����S���܂��B\n��x���߂΃g���b�v�͉�������܂����A�����ꏊ��2�d�|���Ă���ꍇ������̂ł��C������      		";
	s_printer->flowing_message(text);
	while (true) {
		if (GetAsyncKeyState(VK_RETURN)) {
			Sleep(100);
			s_printer->buff.swap();
			s_printer->buff.clearBuff();
			b_print();
			break;
		}
	}
}

void Stage::start()
{
	s_printer->startDraw();
}

void Stage::init_board() {
	s_printer->clear();
	attr_shuffle();
	for (int i = 0; i < emonsters_length; i++) {
		penemy[i]->dead = true;
	}

	for (int x = 0; x < BOARD_WD + 2; ++x) {
		for (int y = 0; y < BOARD_HT + 2; ++y) {
			if (x == 0 || x == BOARD_WD + 1 ||
				y == 0 || y == BOARD_HT + 1)
			{
				this->board[x][y] = WALL;
			}
			else {
				this->board[x][y] = MOVE_ABLE;
			}
		}
	}


	for (int i = 0; i < monsters_length; i++) {
		pmonster[i]->init();
		int test = i;
		int w = pmonster[i]->pos.first;
		int h = pmonster[i]->pos.second;
		this->board[w][h] = pmonster[i]->getAttr();
	}
	int mainas = -3;
	if (stage_number == 3) {
		mainas = -1;
	}
	for (int i = 0; i < emonsters_length + mainas; i++) {
		penemy[i]->dead = false;
	}

	if (stage_number == 4) {

		penemy[1]->dead = true;
		penemy[emonsters_length - 1]->dead = false;
	}

	for (int i = 0; i < emonsters_length; i++) {
		if (penemy[i]->is_dead()) {
			continue;
		}
		penemy[i]->init();
		int w = penemy[i]->pos.first;
		int h = penemy[i]->pos.second;
		board[w][h] = penemy[i]->getAttr();
	}


	if (stage_number == 2) {
		for (int i = 0; i < traps_length; i++) {
			traps[i]->dead = false;
			int w = traps[i]->pos.first;
			int h = traps[i]->pos.second;
			board[w][h] = traps[i]->getAttr();
		}
	}
	else {
		for (int i = 0; i < traps_length; i++) {
			traps[i]->dead = true;
		}
	}
}


void Stage::move_player_cursol(int x, int y) {
	int w = player_curpos.first + x;
	int h = player_curpos.second + y;
	if (board[w][h] != WALL) {
		player_curpos.first = w;
		player_curpos.second = h;
	}
}
void Stage::setMoveMonster() {
	for (int i = 0; i < monsters_length; i++) {
		if (pmonster[i]->pos.first == player_curpos.first && pmonster[i]->pos.second == player_curpos.second) {
			move_monster = i;
			action_monster = pmonster[i]->attr;
			return;
		}
	}
}


bool Stage::is_cursol_moveable() {
	vector<CurPos> v;
	pmonster[move_monster]->moveable_range(v, board);
	for (auto itr = v.begin(); itr != v.end(); itr++) {
		int w = itr->first;
		int h = itr->second;
		if (w == player_curpos.first && h == player_curpos.second) {
			if (!(is_battle(penemy, pmonster[move_monster], emonsters_length, w, h)) &&
				!(is_battle(traps, pmonster[move_monster], traps_length, w, h))) {
				CurPos next;
				next.first = w;
				next.second = h;
				s_printer->DrawMonsterAnimation(pmonster[move_monster]->getAttr(), pmonster[move_monster]->pos, next);
				pmonster[move_monster]->move(w, h, board);
				b_print();
			}
			return true;
		}

	}
	return false;
}

bool Stage::isGameOver() {
	if (yuki_life <= 0) {
		return true;
	}
	for (int i = 0; i < emonsters_length; i++) {
		for (int t = 1; t <= 5; t++) {
			if (penemy[i]->pos.first == t && penemy[i]->pos.second == BOARD_HT) {
				b_print();
				Sleep(1200);
				s_printer->result();
				stage_number = 1;
				yuki_life = STARTLIFE;
				init_board();
				return true;
			}
		}
	}
	return false;

}


void Stage::b_print()
{
	s_printer->print_board();
	s_printer->draw_board_monsters();
	s_printer->buff.swap();
	s_printer->clear();
}

void Stage::AI() {
	player_turn = false;
	int e = 0;
	for (int i = 0; i < emonsters_length; i++) {
		if (penemy[i]->is_dead()) {
			continue;
		}
		else {
			e = i;
		}
	}

	int evaluation = -1000;
	CurPos next;
	for (int i = 0; i < emonsters_length; i++) {
		if (penemy[i]->is_dead()) {
			continue;
		}
		vector<CurPos> v;
		penemy[i]->moveable_range(v, board);
		for (auto itr = v.begin(); itr != v.end(); itr++) {
			int nextevaluation = penemy[i]->move_evaluation(pmonster, monsters_length, *itr, action_monster);

			if (nextevaluation > evaluation) {
				evaluation = nextevaluation;
				e = i;
				next = *itr;
			}
		}
		penemy[i]->action_monster_attr = action_monster;
	}
	if (!(is_battle(pmonster, penemy[e], monsters_length, next.first, next.second)) &&
		!(is_battle(traps, penemy[e], traps_length, next.first, next.second))) {
		s_printer->DrawMonsterAnimation(penemy[e]->getAttr(), penemy[e]->pos, next);
		penemy[e]->move(next.first, next.second, board);
		b_print();
	}
	player_turn = true;
}


bool Stage::is_stage_clear() {

	for (int i = 0; i < monsters_length; i++) {
		int x = pmonster[i]->pos.first;
		int y = pmonster[i]->pos.second;
		for (int s = 1; s <= BOARD_WD; s++) {
			if (y == 1 && x == s) {
				stage_number++;
				if (stage_number == 5) {
					s_printer->result(true);
					stage_number = 1;
					yuki_life = STARTLIFE;
					b_print();
				}
				s_printer->clear();
				return true;
			}
		}
	}
	for (int i = 0; i < emonsters_length; i++) {
		if (!(penemy[i]->is_dead())) {
			return false;
		}
	}
	stage_number++;
	if (stage_number == 5) {
		s_printer->result(true);
		stage_number = 1;
		yuki_life = STARTLIFE;
		b_print();
	}
	return true;
}