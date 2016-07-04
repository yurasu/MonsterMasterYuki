#include "StagePrinter.h"
#include "Stage.h"
#include "DblBuffer.h"
#include <locale.h>

StagePrinter::StagePrinter(Stage * stage)
{
	this->s = stage;
}

void StagePrinter::print_board()
{
	buff.setCursorPos(0, 2);
	buff.setColor(COL_WHITE, COL_BLACK);
	for (int y = 1; y <= BOARD_HT; ++y) {
		print_line(y, false);
		print_line(y, false);
		print_line(y, true);
		print_line(y, false);
		print_line(y, false);
	}
	buff.write("\n");
	show_explanatory_text();
	buff.setColor(COL_WHITE, COL_BLACK);

}


void StagePrinter::print_line(int y, bool printval)
{
	for (int x = 1; x <= BOARD_WD; ++x) {
		int i = s->board[x][y];
		buff.setColor(COL_WHITE, COL_LIGHT_GRAY);
		vector<CurPos> v;
		s->pmonster[s->move_monster]->moveable_range(v, s->board);
		movable_draw(v, x, y);
		if (x == s->player_curpos.first && y == s->player_curpos.second) {
			buff.setColor(COL_WHITE, COL_BLACK);
		}
		line_write(printval);
	}
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.write("\n");
}

void StagePrinter::line_write(bool printval, bool monsterstr, int attr) {
	string str(CELL_WIDTH, ' ');
	if (printval) {
		str = '.';
		if (monsterstr) {
			str = str_attribute(attr);
		}
		str += string((CELL_WIDTH - str.size()) / 2, ' ');      //  �����ɋ󔒃p�f�B���O
		str = string(CELL_WIDTH - str.size(), ' ') + str;       //  �擪�ɋ󔒃p�f�B���O
	}
	buff.write(str);
}

void StagePrinter::movable_draw(vector<CurPos> v, int x, int y)
{
	for (auto itr = v.begin(); itr != v.end(); itr++) {
		int w = itr->first;
		int h = itr->second;
		if (w == x && h == y) {
			buff.setColor(COL_BLACK, COL_WHITE);
		}

	}

}

char * StagePrinter::str_attribute(int v)
{
	switch (v) {
	case TRAP:
		return ".";
	case GOO:
		//case ENEMY_GOO:
		return "�O";
	case CHOKI:
		//case ENEMY_CHOKI:
		return "�`";
	case PER:
		//case ENEMY_PER:
		return "�p";
	case TATUYA:
		return "�Z";
	default:
		return "E";
	}
}

void StagePrinter::setMonsterColor(int v)
{
	int fg = COL_WHITE;
	int bg = COL_BLACK;
	switch (v) {
	case TRAP:
		bg = COL_LIGHT_GRAY;
		break;
	case GOO:
		bg = COL_DARK_RED;
		break;
	case PER:
		bg = COL_DARK_CYAN;
		break;
	case CHOKI:
		bg = COL_DARK_GREEN;
		break;
	case TATUYA:
		bg = COL_DARK_VIOLET;
		break;
	default:
		bg = COL_DARK_YELLOW;
		break;
	}
	buff.setColor(fg, bg);
}

void StagePrinter::draw_board_monsters(int x, int y, bool animation)
{
	EnemyMonster **e_array = s->penemy;
	AllyMonster **m_array = s->pmonster;
	CurPos mapping_pos;
	for (int i = 0; i < s->emonsters_length; i++) {
		if (e_array[i]->is_dead()) {
			continue;
		}
		mapping_coordinate(e_array[i]->pos, mapping_pos);
		if (animation && x == e_array[i]->pos.first && y == e_array[i]->pos.second) {
			continue;
		}
		int w = mapping_pos.first;
		int v = mapping_pos.second;
		DrawMonster(w, v, e_array[i]->getAttr(), s->player_curpos);

	}
	for (int i = 0; i < s->monsters_length; i++) {
		if (m_array[i]->is_dead()) {
			continue;
		}
		mapping_coordinate(m_array[i]->pos, mapping_pos);
		if (animation && x == m_array[i]->pos.first && y == m_array[i]->pos.second) {
			continue;
		}
		int w = mapping_pos.first;
		int v = mapping_pos.second;
		DrawMonster(w, v, m_array[i]->getAttr(), s->player_curpos);
	}
}

void StagePrinter::clear()
{
	buff.clearBuff();
}

void StagePrinter::helpText()
{
	if (!s->help) {
		clear();
		return;
	}
	CurPos size;
	string str;
	buff.getBuffSize(size);
	TextBox t(80, 28, &buff);
	print_board();
	int x = 23;
	draw_board_monsters();
	t.animation(20, size.second / 4 -8);
	buff.setColor(COL_BLACK, COL_WHITE);
	int y = 3;
	if (s->stage_number == 1) {
		buff.setCursorPos(x, y);
		str = "�X�e�[�W1  ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "YUKI�N�IYUKI�N�I��������H�悩�����������Ȃ̂ˁH";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���H�������͕��C��I";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�Ȃ�Řb���ł��邩���āH����Ȃ̈��̗͂Ɍ��܂��Ă邶��Ȃ��I";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "����Ȃ��Ƃ����G�����Ă���I";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�����X�^�[�̈�������YUKI�̕����m���Ă���ˁH ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�o���ĂȂ������獶�̉�ʂ�����Ƃ�����B  ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�w�^����YUKI�ł��킩��悤�ɑ̗͂�X�e�[�W�̏ꏊ��������悤�ɂ�����I";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���Ȃ݂ɂ��̃X�e�[�W�����ǁE�E�E		";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�w�^����YUKI�ł������l�����ɐi�߂Ώ��Ă��I�撣���āI";
		buff.write(str);
		buff.swap();
	}
	else if (s->stage_number == 2) {
		buff.setCursorPos(x, y);
		str = "�X�e�[�W2 ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���Ƃ����Ă��݂�����YUKI�ɂ��Ă͏�o������Ȃ��I�B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�ł��܂��X�e�[�W1��B���ꂩ�炪�{�ԂȂ񂾂���ˁI�B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���̃X�e�[�W2�͔��e���d�|�����Ă���̓��񂾂�ǂ����[��I���Ďd�|���炵����B ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "��`���̃X�e�[�W��YUKI�N�ɂ҂�����ˁI";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�����Ă��Ȃ��A���Ƃ��鎞�������̏�ł����ӂ����ĉ������Ȃ�����Ȃ��B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�o���ĂȂ������獶�̉�ʂ�����Ƃ�����B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���̒��q�ł����Ώ��Ă�񂶂�Ȃ�?";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���e����Ŏ��ȂȂ��悤�ɂˁH";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���̃X�e�[�W�ɐi�߂邱�Ƃ��F���Ă��B";
		buff.write(str);
		buff.swap();
	}
	else if (s->stage_number == 3) {
		buff.setCursorPos(x, y);
		str = "�X�e�[�W3 ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "YUKI�N�A���e������ꂽ�̂͂����񂾂��ǁE�E�E�B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�����X�^�[�ɓ��܂���̂͂悭�Ȃ��Ǝv����I���킢��������Ȃ��I�B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�ł������ł悩������B���͖����ł͂Ȃ������ł����ǂ��`�B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�����G�Ɉ͂܂ꂿ����Ă邶��Ȃ��I";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "YUKI�N�܂�3�̂��������X�^�[�o���Ȃ��񂾂��獡����͂łȂ�Ƃ��Ȃ����I";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�����˂��E�E�E�B�����X�^�[��ˌ�������������Ă̂͂ǂ�������H		";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "��������Ύ��R�Ƃ��Ȃ��Ȃ���I�����ƁI";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���Ȃ��̗̑͂ƓG�̌R�c�ǂ�������������ˁH";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���͂��Ȃ��̗̑͂������Ƃ�M���Ă����B";
		buff.write(str);
		buff.swap();
	}
	else if (s->stage_number == 4) {
		buff.setCursorPos(x, y);
		str = "�X�e�[�W4 ";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�Ƃ��Ƃ������܂ŗ�����ˁI";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�����{���{������Ȃ��B���v�H";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���Ȃ��̃����X�^�[���h�����ˁE�E�E�B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "��H�����Ԃ�Ɩ����̕]���������Ȃ������āH��������Ȃ킯�Ȃ�����Ȃ��I";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "����Ȃ��Ƃ���������B���̂����͋��G��B	";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���Ȃ��̍��̗͂���3��U�����d�|���Ȃ��Ɠ|���Ȃ������B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�����X�^�[�̑��߂͂���������������v���Ƃ͎v�����ǁE�E�E�B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���f�͋֕���I�ł��ǂ�Ȃɂ炭�Ă�YUKI�N�͎�����M���āI";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "������߂Ȃ���΂����Ə��Ă��I";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�����|���Ȃ����莩�g���Ȃ��Ȃ������́E�E�E�E�E�B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�����Ȃ񂩖������Ď��̂Ƃ���֗��Ă�������I�I�I�B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���͖����̌��ɂ���֎q�ɍ����đ҂��Ă��B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "�撣����YUKI�N�B";
		buff.write(str);
		y += 2;
		buff.setCursorPos(x, y);
		str = "���̍ł��������l�B";
		buff.write(str);
		buff.swap();
	}
}


void StagePrinter::DrawMonster(int x, int y, int attr, CurPos pos)
{
	setMonsterColor(attr);
	CurPos p_mapping_pos;
	mapping_coordinate(pos, p_mapping_pos);
	if (x == p_mapping_pos.first && y == p_mapping_pos.second) {
		buff.setColor(COL_WHITE, COL_BLACK);
	}

	for (int i = 0; i < BOARD_HT; i++) {
		bool printval = false;
		buff.setCursorPos(x, y + i);
		if (i == 2) {
			printval = true;
		}
		line_write(printval, true, attr);
	}
	buff.setColor(COL_WHITE, COL_LIGHT_GRAY);
}

void StagePrinter::deadAnimation(Monster *m) {
	CurPos mapping_pos;
	mapping_coordinate(m->pos, mapping_pos);
	buff.setCursorPos(mapping_pos.first, mapping_pos.second);
	for (int y = 0; y < BOARD_HT; ++y) {
		bool printval = false;
		int i = 0;
		do {
			if (i == 2) {
				printval = true;
			}
			Sleep(5);
			buff.setColor(COL_WHITE, COL_LIGHT_GRAY);
			buff.setCursorPos(mapping_pos.first, mapping_pos.second + i);
			line_write(false, false, m->getAttr());
			i++;
		} while (i <= y);
		buff.swap();
	}
	Sleep(400);
}


void StagePrinter::result(bool clear)
{
	buff.swap();
	buff.clearBuff();
	buff.swap();
	buff.clearBuff();
	TextBox tb(40, 20, &buff);
	CurPos size;
	buff.getBuffSize(size);
	tb.flame_bg = COL_LIGHT_GRAY;
	int x = size.first / 4;
	tb.animation(x + 8, 13);
	buff.swap();
	int i = 4;
	i = i + x;
	CurPos init;
	init.first = 2;
	init.second = i;
	int fg = COL_LIGHT_GRAY;
	int bg = COL_LIGHT_GRAY;
	drawChar(drow18, 7, 9, init, fg, bg);
	i += 9;
	init.first = 2;
	init.second = i;
	drawChar(drow5, 7, 9, init, fg, bg);
	i += 9;
	init.first = 2;
	init.second = i;
	drawChar(drow19, 7, 9, init, fg, bg);
	i += 9;
	init.first = 2;
	init.second = i;
	drawChar(drow21, 7, 9, init, fg, bg);
	i += 9;
	init.first = 2;
	init.second = i;
	drawChar(drow12, 7, 9, init, fg, bg);
	i += 9;
	init.first = 2;
	init.second = i;
	drawChar(drow20, 7, 9, init, fg, bg);
	buff.setColor(COL_BLACK, COL_WHITE);
	string str("");
	int clear_num = s->stage_number;
	if (!clear) {
		clear_num--;
	}
	buff.setCursorPos(x + 13, 16);
	str = "�X�e�[�W�N���A��:" + to_string(clear_num) + "	";
	buff.write(str);
	buff.setCursorPos(x + 13, 18);
	str = "�c��c�@:" + to_string(s->yuki_life);
	buff.write(str);
	buff.setCursorPos(x + 13, 20);
	str = "�|�����G�̐�:" + to_string(s->victory_enemy);
	buff.write(str);
	int score = s->victory_enemy * 100 + s->yuki_life * 10;
	buff.setCursorPos(x + 13, 22);
	if (!clear) {
		score *= 0;
	}
	str = "�����X�R�A:" + to_string(score);
	buff.write(str);
	CurPos evalu_pos;
	evalu_pos.first = 25;
	evalu_pos.second = x + 25;
	if (!clear) {
		drawChar(drow24, 7, 9, evalu_pos, COL_BLACK, COL_BLACK);
	}
	else if (score >= 1900) {
		drawChar(drow19, 7, 9, evalu_pos, COL_DARK_VIOLET, COL_DARK_VIOLET);
	}
	else if (score >= 1500) {
		drawChar(drow1, 7, 9, evalu_pos, COL_DARK_RED, COL_DARK_RED);
	}
	else if (score >= 1100) {
		drawChar(drow2, 7, 9, evalu_pos, COL_DARK_BLUE, COL_DARK_BLUE);
	}
	else {
		drawChar(drow3, 7, 9, evalu_pos, COL_DARK_YELLOW, COL_DARK_YELLOW);
	}

	buff.swap();
	Sleep(200);
	while (true) {
		if (GetAsyncKeyState(VK_RETURN)) {
			if (clear) {
				Sleep(500);
				buff.swap();
				buff.clearBuff();
				flowing_message("�����c�������c�����Ȃ����̂���YUKI��B\n\nYUKI�c�I�H�Ȃ��l�̖��O��m���Ă���I\n\n�����c�m���Ă���Ƃ��A���O�����܂ꂽ������m���Ă���B\n\nYUKI�c���O�͂����������҂Ȃ񂾂�I\n\n�����c�������ȁc�B���������Ă����Ă������̂ł͂Ȃ����H�Ȃ��P�l�H\n\nYUKI�c��!\n\nAI�P�c�E�E�E�����ł��ˁBYUKI�N���������ĕ����ĂˁB�����͂��Ȃ��̂��Z����Ȃ̂�B\n\nYUKI�c�����I�H�Ȃ񂾂��āI�I�I\n\n�����c�܂��喂���̎q�ł͂��邪�A�l�ԂƂ̊Ԃ̎q�łȁc�B���Ƃ͕��Ⴂ���B\n\nYUKI�c�Ȃ������炻��Ȃ��Ƃ����񂾂�I���̉��\�N�Ԃŉ����Ȃ�Ă�����ł�����������Ȃ����Ȃ̂ɂǂ����āE�E�E�B\n\n�����c�䎩�g�m��Ȃ������c����L����������Ă����Ƃ����̂����������B\n\nYUKI�c�L�����H\n\n�����c�������B���E�ɐl�Ԃ̎q������ƂȂ�ΐ푈�̉Ύ�ɂȂ�\�������邩��ȁB\n���̗v����1�ł��������߂Ɋւ���Ă���2�l���������S���̋L�����������Ƃ������Ƃ��B\n\nYUKI�c����2�l�͂܂����c\n\n�����c���̂܂������l�ԊE�̌������Ɖ�̕��喂�����B�܂��������͂�����Ɩ񑩂�����Ă��ꂽ�炵���Ȗ��ɂ��狳���Ȃ������̂�����B\n\nAI�P�c�����A�ꋎ����O�ɂ��̂��Ƃ𕷂�����܂����B�v��������߂͂��낢�날��܂������A�܂������̂悤�Ȃ��Ƃ��������Ƃ͒m��܂���ł����E�E�E�B\n\nYUKI�c�A�ꋎ��O�H��̂ǂ��������Ƃ��c����������̎��������������̗��R�������Ă���Ȃ��Ƃ����񂾁H�B\n\nAI�P�c��������́E�E�E�E///");
				Sleep(500);
				buff.swap();
				buff.clearBuff();
				flowing_message("�����c�͂��E�E�EYUKI�A�P�ƕt�������Ă��邻������Ȃ����B\n\nYUKI�c�Ȃ�ł���Ȃ��ƒm���Ă���񂾁H\n\n�����c�������畷�����B\n\nYUKI�c��ޔ閧�ɂ��Ă������͂��Ȃ̂Ɂc\n\n�����c�S���o���o���������炵�����E�E�E�B\n\nYUKI�c����Ȃ�\n\n�����c����Ȃ��Ƃ������O��t�������Ă���̂Ɏ���q���Ȃ��Ƃ͂ǂ��������ƂȂ񂾂����������Ă݂��1�N���i�W���Ȃ��ƕP�l���Q���Ă���\n\nAI�P�c/////\n\nYUKI�c�����������Ĉꍑ�̉��������l�ɂ͒ނ荇��Ȃ��Ǝv���Ă������A�P�l�̏Ί炪����邾���ł悩�����Ƃ������E�E�E�B\n\n�����c�䂪��ł͂��邪�Ȃ�Ƃ��w�^���Ȃ���ȁB\n\nYUKI�c�w�^�������ȁI\n\n�����c���O���w�^���Ȃ����ŁAYUKI���{���ɕP�l�̂��Ƃ��D���Ă���̂��s���ɂȂ��Ă��܂��ĂȂ��̂��Ƃɂ��ĕ��Ɖ�ɑ��k����Ă��܂����̂��B\n���̎��ɉ�̋L�����삪�����Ă��܂��Ƃ͎v�������Ȃ��������ȁB\n\nYUKI�c�����I�H�����ƕP�l�Ƃ���Ȋ֌W�Ȃ́I�I�I�H\n\n�����c���R���낤�B�閧�����L�����O�Ƃ��̕��a�����Ăق����Ɨ��񂾂̂͑喂���������ǂ��Ȃ���΂���Ȃ��Ƃł��Ȃ��ł��낤�B\n�܂����̂��Ƃ͍��ザ������b���Ă��B���͂��O�ƕP�l�̖�肾�I���O�͕P�l�̎��D���Ȃ̂��H�����Ȃ̂��H\n\nYUKI�c����́E�E�E�E�E���E�E�E�D���ł����ǁE�E�E�E\n\n�����c�����̎q�ŉ䂪��ł��邼�I�����Ɠ��X�Ƃ���I��قǂ̐ڕ��������̈А��������Ă݂��I\n\n");
				Sleep(500);
				buff.swap();
				buff.clearBuff();
				flowing_message("YUKI�c�I�H�`�`�`�I�I�I�E�E�E�E�P�l�̂��Ƃ����������������I�I�I�I\n\nAI�P�c////\n\n�����c���ނ��̓x�����������ɂ��ĉ䂪��ł��邼�I���āE�E�E�P�l�͂ǂ��Ȃ̂��H\n\nAI�P�c����YUKI�N�����΂ɂ��Ă��ꂽ�����炸���ƍD���Ă��܂�����B\n\nYUKI�c/////\n\nAI�P�c////\n\n�����c�����������O�����̗��Ŗ��l�ɕ����č��ɋA��ł�������A�䂪�P�l���łƂ��Ė���Ă������ȁI\n\nYUKI�c�܂��ł����E�E�E�E�B\n\n�����c��k���B\n\nAI�P�c����ɂĈꌏ�����ł���/////\n\n�݂�Ȓ��ǂ��͂��ҁ[�����");
				Sleep(1000);
				buff.swap();
				buff.clearBuff();
				break;
			}
			else {
				Sleep(500);
				buff.swap();
				buff.clearBuff();
				flowing_message("�����cYUKI�敉���Ă��܂��Ƃ́A�Ȃ�Ƃ���Ȃ��B\n\n�����c���O��AI�ւ̈��͂���Ȃ��̂ł������̂��H\n�E�E�E�E�E�E�܂�����Ȃ��Ƃ͂ǂ��ł��悢�B\n\nYUKI�c���H����͂��������ǂ������\�B\n\n�����c���O��AI�̗��l�ɂ͂ӂ��킵���Ȃ������Ƃ������Ƃ��ȁB���͉A�Ȃ��牞�����Ă͂������A�������E���E�E�E�B\n\nYUKI�c��̂ǂ��������ƂȂ�ł����I�������ĉ������I\n\n�����c�����Ɏ��M�����ĂȂ��A�����̂��Ƃɂ������ɂȂ����O�ɁA�������邷���Ȃǎ������B\n\nYUKI�c�I�I�I�I\n\n�����c�E�E�E�������Ȃ����ꂾ���͌����Ă�낤�B�h���Ɩ����͖�����������h\n\nYUKI�c�Ȃ��Ȃ��I\n\n�����c���������͎����Ȃ��Ƃ��������낱�ꂾ���ł����ӂ��Ăق����ˁB���̏Ί�h�����h�������������̂ł��낤�H\n\nYUKI�c���E�E�E����Ȃ��Ƃ́E�E�E\n\n�����c�����Ă����ł��낤�H�������������l�Ɗւ��@���^�����̂ɂ��O�͂���Ȃ��ƍl���������A\n�䂪���Ƃ͗���ĕ�炵�A�l�Ƃ͘b���������X�^�[�Ƃ����ւ��Ȃ��B����Ȏ����̎������l���Ă��Ȃ����O�Ȃǂ��ꂾ���ŏ\�����B\n\nYUKI�c����ȁE�E�E�B\n\n�����c�킩�����̂Ȃ炳�����Əo�čs���Ă��ꂨ�O�̂悤�Ȑl�Ԃ͂��̍��ɂ͕s�v���B\n\nYUKI�c�E�E�E�E�E�E�E�E�E�E�E�B\n\n�����Ď��̓��A������AI�P�̌������s��ꂽ�B���̂Ƃ�YUKI�̎p�͂������Ƃ����B���������̓�����YUKI�����邱�Ƃ͂Ȃ��Ȃ����B\n�]AI�P�̓��L�]\n\nBAD END");
				Sleep(1000);
				break;
			}
		}
	}
}

void StagePrinter::show_explanatory_text()
{
	CurPos size;
	int i = 5;
	buff.getBuffSize(size);
	buff.setCursorPos(size.first - 50, i);
	if (s->player_turn) {
		buff.setColor(COL_WHITE, COL_DARK_BLUE);
		buff.write("Player Turn");
	}
	else {
		buff.setColor(COL_WHITE, COL_DARK_RED);
		buff.write("Enemy Turn");
	}
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.setCursorPos(size.first - 50, i);
	buff.write("YUKI_LIFE: " + to_string(s->yuki_life));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.write("Stage:" + to_string(s->stage_number));
	i += 3;
	buff.setCursorPos(size.first - 50, i);
	buff.write(string("�J�[�\���ړ�:[��][��][��][��]"));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.write(string("�ړ���̌���,�����X�^�[�̑I��:[ENTER]"));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_DARK_VIOLET);
	buff.write(string("�X�e�[�W�����m�F/����:[h] "));
	i += 3;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_DARK_VIOLET);
	buff.write(string("�Z"));
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.write(string(":YUKI�̌Z(����)"));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_DARK_YELLOW);
	buff.write(string("�d"));
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.write(string(":�G�l�~�["));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_DARK_RED);
	buff.write(string("�O"));
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.write(string(":���������X�^�[[�����O�[]"));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_DARK_GREEN);
	buff.write(string("�`"));
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.write(string(":���������X�^�[[�����`���L]"));
	i += 2;
	buff.setCursorPos(size.first - 50, i);
	buff.setColor(COL_WHITE, COL_DARK_CYAN);
	buff.write(string("�p"));
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.write(string(":���������X�^�[[�����p�[]"));
}

CurPos StagePrinter::mapping_coordinate(CurPos &now_pos, CurPos &pos)
{
	int array_m_wpos[5] = { 0,10,20,30,40 };
	int array_m_hpos[5] = { 0,5,10,15,20 };
	pos.first = array_m_wpos[now_pos.first - 1];
	pos.second = array_m_hpos[now_pos.second - 1] + 2;
	return pos;
}

void StagePrinter::DrawMonsterAnimation(int attr, CurPos now_pos, CurPos next_pos)
{
	CurPos n_mappintg_pos;
	mapping_coordinate(now_pos, n_mappintg_pos);
	int w = n_mappintg_pos.first;
	int v = n_mappintg_pos.second;
	CurPos next_mapping_pos;
	mapping_coordinate(next_pos, next_mapping_pos);
	int next_w = next_mapping_pos.first;
	int next_h = next_mapping_pos.second;
	int i = 2;
	int t = 1;
	if (w > next_w) {
		i *= -1;
	}

	if (v > next_h) {
		t *= -1;
	}
	while (true) {
		if (w != next_w) {
			w += i;
		}
		if (v != next_h) {
			v += t;
		}
		print_board();
		draw_board_monsters(now_pos.first, now_pos.second, true);
		DrawMonster(w, v, attr, s->player_curpos);
		buff.swap();
		buff.clearBuff();
		if (w == next_w && v == next_h) {
			Sleep(400);
			break;
		}
	}
}

void StagePrinter::flowing_message(char *text)
{
	int i = 0;
	int len = 0;
	string str("");
	setlocale(LC_CTYPE, "jpn");
	while (text[i] != '\0') {
		len = mblen(&text[i], MB_CUR_MAX);
		if (len == 2) {
			str += text[i];
			str += text[i + 1];
			i++;
		}
		else {
			str += text[i];
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			str = text;
			break;
		}
		buff.setColor(COL_WHITE, COL_DARK_RED);
		buff.setCursorPos(0, 0);
		buff.write("Skip�������ꍇ�ɂ̓G���^�[�������Ă� ");
		buff.setColor(COL_WHITE, COL_BLACK);
		buff.setCursorPos(0, 1);
		buff.write(str);
		buff.swap();
		buff.clearBuff();
		Sleep(10);
		i++;
	}
	buff.setCursorPos(0, 0);
	buff.setColor(COL_WHITE, COL_DARK_RED);
	buff.write("Skip�������ꍇ�ɂ̓G���^�[�������Ă�  ");
	buff.setColor(COL_WHITE, COL_BLACK);
	buff.setCursorPos(0, 1);
	buff.write(str);
	buff.setColor(COL_WHITE, COL_DARK_RED);
	buff.write("\n\n���֐i�ނɂ̓G���^�[�L�[�������Ă�������   ");
	buff.swap();
	buff.clearBuff();
	Sleep(1000);

}

void StagePrinter::drawChar(int array[7][9], int y_length, int x_length, CurPos init_pos, int fgCOL, int bgCOL) {
	for (int y = 0; y < y_length; y++) {
		for (int x = 0; x < x_length; x++) {
			buff.setCursorPos((init_pos.second + x), (init_pos.first + y));
			if (array[y][x] == 1) {
				buff.setColor(fgCOL, bgCOL);
				buff.write(" ");
			}
		}
	}
	buff.setColor(COL_BLACK, COL_BLACK);
}

void StagePrinter::startDraw()
{
	int count = 0;
	while (true) {

		int i = 0;

		CurPos size;
		buff.getBuffSize(size);
		int x = size.first / 4;
		i = i + x;
		CurPos init;
		init.first = 2;
		init.second = i;
		int fg = COL_DARK_VIOLET;
		int bg = COL_DARK_VIOLET;
		drawChar(drow13, 7, 9, init, fg, bg);
		i += 9;
		init.first = 2;
		init.second = i;
		drawChar(drow15, 7, 9, init, fg, bg);
		i += 9;
		init.first = 2;
		init.second = i;
		drawChar(drow14, 7, 9, init, fg, bg);
		i += 9;
		init.first = 2;
		init.second = i;
		drawChar(drow19, 7, 9, init, fg, bg);
		i += 9;
		init.first = 2;
		init.second = i;
		drawChar(drow20, 7, 9, init, fg, bg);
		i += 9;
		init.first = 2;
		init.second = i;
		drawChar(drow5, 7, 9, init, fg, bg);
		i += 9;
		init.first = 2;
		init.second = i;
		drawChar(drow18, 7, 9, init, fg, bg);


		int s = 5 + x;
		init.first = 12;
		init.second = s;
		drawChar(drow13, 7, 9, init, fg, bg);
		s += 9;
		init.first = 12;
		init.second = s;
		drawChar(drow1, 7, 9, init, fg, bg);
		s += 9;
		init.first = 12;
		init.second = s;
		drawChar(drow19, 7, 9, init, fg, bg);
		s += 9;
		init.first = 12;
		init.second = s;
		drawChar(drow20, 7, 9, init, fg, bg);
		s += 9;
		init.first = 12;
		init.second = s;
		drawChar(drow5, 7, 9, init, fg, bg);
		s += 9;
		init.first = 12;
		init.second = s;
		drawChar(drow18, 7, 9, init, fg, bg);


		int t = 14 + x;
		init.first = 22;
		init.second = t;
		drawChar(drow25, 7, 9, init, fg, bg);
		t += 9;
		init.first = 22;
		init.second = t;
		drawChar(drow21, 7, 9, init, fg, bg);
		t += 9;
		init.first = 22;
		init.second = t;
		drawChar(drow11, 7, 9, init, fg, bg);
		t += 9;
		init.first = 22;
		init.second = t;
		drawChar(drow9, 7, 9, init, fg, bg);


		buff.setCursorPos(size.first / 2 - 15, size.second - 8);
		count++;
		if (count % 2) {
			buff.setColor(COL_WHITE, COL_BLACK);
			buff.write("Press Enter Key Start YUKI STORY");
		}
		buff.swap();
		Sleep(550);
		buff.clearBuff();
		if (GetAsyncKeyState(VK_RETURN)) {
			Sleep(100);
			break;
		}
	}
}


