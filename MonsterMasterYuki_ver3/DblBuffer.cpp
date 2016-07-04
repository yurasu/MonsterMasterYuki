#include "DblBuffer.h"
#include "Common.h"

DblBuffer::DblBuffer()
	: m_swapped(false)
{
	//m_hCons = GetStdHandle( STD_OUTPUT_HANDLE );
	m_hCons1 = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	m_hCons2 = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(m_hCons1);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;
	info.bVisible = FALSE;
	SMALL_RECT rc = { 0, 0, 125, 40 };
	COORD      coord;
	coord.X = rc.Right+1;
	coord.Y = rc.Bottom+1;
	SetConsoleScreenBufferSize(m_hCons1, coord);
	SetConsoleWindowInfo(m_hCons1, TRUE, &rc);
	SetConsoleScreenBufferSize(m_hCons2, coord);
	SetConsoleWindowInfo(m_hCons2, TRUE, &rc);
	SetConsoleCursorInfo(m_hCons1, &info);
	SetConsoleCursorInfo(m_hCons2, &info);
}
DblBuffer::~DblBuffer()
{
	CloseHandle(m_hCons1);
	CloseHandle(m_hCons2);
}
void DblBuffer::setColor(int col)
{
	WORD attr = 0;
	if (col & COL_INTENSITY)
		attr |= FOREGROUND_INTENSITY;
	if (col & COL_RED_MASK)
		attr |= FOREGROUND_RED;
	if (col & COL_GREEN_MASK)
		attr |= FOREGROUND_GREEN;
	if (col & COL_BLUE_MASK)
		attr |= FOREGROUND_BLUE;
	SetConsoleTextAttribute(m_swapped ? m_hCons1 : m_hCons2, attr);
}
void DblBuffer::setColor(int fg, int bg)
{
	WORD attr = 0;
	if (fg & COL_INTENSITY)
		attr |= FOREGROUND_INTENSITY;
	if (fg & COL_RED_MASK)
		attr |= FOREGROUND_RED;
	if (fg & COL_GREEN_MASK)
		attr |= FOREGROUND_GREEN;
	if (fg & COL_BLUE_MASK)
		attr |= FOREGROUND_BLUE;

	if (bg & COL_INTENSITY)
		attr |= BACKGROUND_INTENSITY;
	if (bg & COL_RED_MASK)
		attr |= BACKGROUND_RED;
	if (bg & COL_GREEN_MASK)
		attr |= BACKGROUND_GREEN;
	if (bg & COL_BLUE_MASK)
		attr |= BACKGROUND_BLUE;
	SetConsoleTextAttribute(m_swapped ? m_hCons1 : m_hCons2, attr);
}
void DblBuffer::setCursorPos(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(m_swapped ? m_hCons1 : m_hCons2, pos);
}

void DblBuffer::write(const char *ptr)
{
	DWORD len = strlen(ptr);
	WriteConsoleA(m_swapped ? m_hCons1 : m_hCons2, ptr, len, &len, 0);
}
void DblBuffer::write(const wchar_t *ptr)
{
	DWORD len = wcslen(ptr);
	WriteConsoleW(m_swapped ? m_hCons1 : m_hCons2, ptr, len, &len, 0);
}
void DblBuffer::write(const std::string &str)
{
	DWORD len = str.size();
	WriteConsoleA(m_swapped ? m_hCons1 : m_hCons2, str.c_str(), len, &len, 0);
}
void DblBuffer::write(const std::wstring &str)
{
	DWORD len = str.size();
	WriteConsoleA(m_swapped ? m_hCons1 : m_hCons2, str.c_str(), len, &len, 0);
}

void DblBuffer::swap()
{
	if ((m_swapped = !m_swapped)) {
		SetConsoleActiveScreenBuffer(m_hCons2);
	}
	else {
		SetConsoleActiveScreenBuffer(m_hCons1);
	}
}

void DblBuffer::getBuffSize(CurPos &size)
{
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(m_swapped ? m_hCons1 : m_hCons2, &screenInfo);
	COORD   coord = { 0, 0 };       //書き込みを開始する位置 x:0y:0に設定
	GetConsoleScreenBufferInfo(m_swapped ? m_hCons1 : m_hCons2, &screenInfo);
	size.first = screenInfo.dwSize.X;
	size.second = screenInfo.dwSize.Y;
}

void DblBuffer::clearBuff()
{
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(m_swapped ? m_hCons1 : m_hCons2, &screenInfo);
	DWORD   dwNumberOfCharsWritten; // 書き込まれたセル数
	COORD   coord = { 0, 0 };       //書き込みを開始する位置 x:0y:0に設定
	GetConsoleScreenBufferInfo(m_swapped ? m_hCons1 : m_hCons2, &screenInfo);
	// バッファ内の指定した座標から指定した数の文字セル分だけ、前景色と背景色を設定
	FillConsoleOutputAttribute(m_swapped ? m_hCons1 : m_hCons2,
		COL_WHITE + (COL_BLACK << 4),
		screenInfo.dwSize.X * screenInfo.dwSize.Y*10,
		coord,
		&dwNumberOfCharsWritten
		);
	// バッファ内の指定した座標から、指定した文字を指定した数だけ書き込む
	FillConsoleOutputCharacter(
		m_swapped ? m_hCons1 : m_hCons2,
		' ',
		screenInfo.dwSize.X * screenInfo.dwSize.Y,
		coord,
		&dwNumberOfCharsWritten
		);
}


