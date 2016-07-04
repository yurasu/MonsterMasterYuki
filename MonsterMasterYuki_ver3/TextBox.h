#pragma once
#include "Common.h"
#include "DblBuffer.h"
//�S���t�W�^
class TextBox {
public:
	CurPos pos;
	CurPos m_pos;
	DblBuffer *buff;
	int wlength; //���b�Z�[�W�̉���
	int hlength; //���b�Z�[�W�̏c��
	int flame_wlength;
	int flame_hlength;
	int flame_bg = COL_DARK_RED;
	int message_bg = COL_WHITE;
	string text;
	//�R���X�g���N�^
	TextBox(int wlength, int hlength, DblBuffer *buff);

	//�e�L�X�g���Z�b�g������
	void setText(string str);

	//�e�L�X�g��\��������
	void showText();

	//�e�L�X�g�{�b�N�X
	void DrawMBox(int x, int y, int w, int h);
	//�e�L�X�g�{�b�N�X�𓮂����Ȃ���\��
	void animation(int x, int y);
};