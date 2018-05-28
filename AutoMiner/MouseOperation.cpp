#include "MouseOperation.h"



CMouseOperation::CMouseOperation()
{
}

pair<int, int> CMouseOperation::getMousePos() {
	POINT mousePos;
	GetCursorPos(&mousePos);
	return pair<int, int>(mousePos.x, mousePos.y);
}

void CMouseOperation::goClick(int i, int j) {
	wstring miner = L"Minesweeper Arbiter ";
	LPCWSTR minerSTR = miner.c_str();
	wstring minerclass = L"TMain";
	LPCWSTR minerclassSTR = minerclass.c_str();
	HWND hq = FindWindow(minerclassSTR, minerSTR);

	RECT rect;
	GetWindowRect(hq, &rect);

	left_ = rect.left + 15;
	right_ = rect.right - 15;
	top_ = rect.top + 101;
	bottom_ = rect.bottom - 43;

	mouseX_ = left_ + 16 * (i - 1) + 8;
	mouseY_ = top_ + 16 * (j - 1) + 8;
	SetCursorPos(mouseX_, mouseY_);
}