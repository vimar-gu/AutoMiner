#include "ImageProcess.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <atlstr.h>

using namespace std;

namespace {
	const int blockWidth = 16;
	const int blockHeight = 16;
	int screenW;
	int screenH;
	BYTE* ScreenData = 0;
}

void CImageProcess::getFrame() {
	wstring miner = L"Minesweeper Arbiter ";
	LPCWSTR minerSTR = miner.c_str();
	wstring minerclass = L"TMain";
	LPCWSTR minerclassSTR = minerclass.c_str();
	HWND hq = FindWindow(minerclassSTR, minerSTR);

	RECT rect;
	GetWindowRect(hq, &rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;
	cout << w << " " << h << endl;    // 510 * 400 for expert

	left_ = rect.left + 15;
	right_ = rect.right - 15;
	top_ = rect.top + 101;
	bottom_ = rect.bottom - 43;

	blocksX_ = (right_ - left_) / blockWidth;
	blocksY_ = (bottom_ - top_) / blockHeight;
	cout << blocksX_ << " " << blocksY_ << endl;

	HDC hdcScreen = GetDC(NULL);
	HDC hdc = CreateCompatibleDC(hdcScreen);
	screenW = w - 6;
	screenH = h - 49;
	HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen, screenW, screenH);
	SelectObject(hdc, hbmp);
	PrintWindow(hq, hdc, PW_CLIENTONLY);

	BITMAPINFOHEADER bmi = { 0 };
	bmi.biSize = sizeof(BITMAPINFOHEADER);
	bmi.biPlanes = 1;
	bmi.biBitCount = 32;
	bmi.biWidth = screenW;
	bmi.biHeight = -screenH;
	bmi.biCompression = BI_RGB;
	bmi.biSizeImage = 0;
	SelectObject(hdc, hbmp);
	if (ScreenData) free(ScreenData);
	ScreenData = (BYTE*)malloc(4 * screenW * screenH);
	GetDIBits(hdcScreen, hbmp, 0, screenH, ScreenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

	for (int i = 0; i < blocksX_; i++) {
		for (int j = 0; j < blocksY_; j++) {
			int x = 13 + i * blockHeight + blockHeight / 2;
			int y = 55 + j * blockWidth + blockWidth / 2;
			cout << x << " " << y << " " << (int)(ScreenData[4 * ((y*screenW) + x)]) << " "
				<< (int)(ScreenData[4 * ((y*screenW) + x) + 1]) << " "
				<< (int)(ScreenData[4 * ((y*screenW) + x) + 2]) << endl;
		}
	}

	//release
	DeleteDC(hdc);
	DeleteObject(hbmp);
	ReleaseDC(NULL, hdcScreen);
}
