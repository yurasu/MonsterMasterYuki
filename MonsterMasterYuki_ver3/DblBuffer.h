#pragma once
#include <Windows.h>
#include <string>
#include "Common.h"
//�S���t�W�^
class DblBuffer
{
public:
	//�R���X�g���N�^
	DblBuffer();
	//�f�X�g���N�^
	~DblBuffer();

public:
	//�F�ݒ�
	void setColor(int);
	//�F�ݒ�
	void setColor(int, int);
	//�R���\�[���J�[�\�����W�̐ݒ�
	void setCursorPos(int, int);
	//��������������
	void write(const char *);
	//��������������
	void write(const wchar_t *);
	//��������������
	void write(const std::string &);
	//��������������
	void write(const std::wstring &);
	//�o�b�t�@�����ւ���
	void swap();
	//�o�b�t�@�̃T�C�Y��ݒ�
	void getBuffSize(CurPos &size);
	//�o�b�t�@���N���[���ɂ���
	void clearBuff();

private:
	bool			m_swapped;
	HANDLE		m_hCons1;		//	�R���\�[���n���h�����̂P
	HANDLE		m_hCons2;		//	�R���\�[���n���h�����̂Q
};