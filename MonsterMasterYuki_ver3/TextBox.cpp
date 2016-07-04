#include "TextBox.h"

TextBox::TextBox(int wlength, int hlength, DblBuffer *buff) {
	this->wlength = wlength;
	this->hlength = hlength;
	this->buff = buff;
	flame_wlength = wlength + 4;
	flame_hlength = hlength + 2;
}

void TextBox::setText(string str) {
	text = str;
}

void TextBox::showText() {
	buff->setColor(COL_BLACK, message_bg);
	buff->setCursorPos(m_pos.first, m_pos.second);
	buff->write(text);
}

void TextBox::DrawMBox(int x, int y, int w, int h) {
	flame_wlength = w + 4;
	flame_hlength = h + 2;
	buff->setColor(flame_bg, flame_bg);
	for (int i = x; i < x + flame_wlength; i++) {
		buff->setCursorPos(i, y);
		buff->write(" ");
		buff->setCursorPos(i, y + flame_hlength);
		buff->write(" ");
	}
	buff->setColor(flame_bg, flame_bg);
	for (int i = y; i < y + flame_hlength; i++) {
		buff->setCursorPos(x, i);
		buff->write(" ");
		buff->setCursorPos(x + 1, i);
		buff->write(" ");
		buff->setCursorPos(x + flame_wlength - 1, i);
		buff->write(" ");
		buff->setCursorPos(x + flame_wlength - 2, i);
		buff->write(" ");
	}

	//”’‚Ì•`‰æ—Ìˆæ
	m_pos.first = x + 2;
	m_pos.second = y + 1;
	buff->setColor(message_bg, message_bg);
	for (int i = x + 2; i < x + 2 + w; i++) {
		for (int s = y + 1; s < y + 2 + h; s++) {
			buff->setCursorPos(i, s);
			buff->write(" ");
		}
	}
}

void TextBox::animation(int x, int y) {
	int w = 0;
	int h = 0;
	int i = 1;
	while (true) {
		if (w < wlength) {
			w += i;
		}
		if (h < hlength) {
			h += i;
		}
		this->DrawMBox(x, y, w, h);
		buff->swap();
		if (w == this->wlength && h == this->hlength) {
			break;
		}
	}
}