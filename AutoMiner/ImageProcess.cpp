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

	frameInfo_.resize(blocksY_);
	for (int i = 0; i < blocksY_; i++) frameInfo_[i].resize(blocksX_);

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
	int redBit, greenBit, blueBit;
	for (int i = 0; i < blocksX_; i++) {
		for (int j = 0; j < blocksY_; j++) {
			int x = 13 + i * blockHeight + blockHeight / 2;
			int y = 55 + j * blockWidth + blockWidth / 2;
			redBit   = (int)(ScreenData[4 * ((y*screenW) + x)]);
			greenBit = (int)(ScreenData[4 * ((y*screenW) + x) + 1]);
			blueBit  = (int)(ScreenData[4 * ((y*screenW) + x) + 2]);

			if (redBit == 192 && greenBit == 192 && blueBit == 192) { // gray
				if ((int)(ScreenData[4 * ((y*screenW) + x - 8)]) == 255) { // white
					frameInfo_[j][i] = -2; // never touched
				}
				else {
					frameInfo_[j][i] = -1; // blank block
				}
			}
			else if (redBit == 0 && greenBit == 0 && blueBit == 255) { // blue
				frameInfo_[j][i] = 1; // 1 mine
			}
			else if (redBit == 0 && greenBit == 128 && blueBit == 0) { // dark green
				frameInfo_[j][i] = 2; // 2 mines
			}
			else if (redBit == 255 && greenBit == 0 && blueBit == 0) { //red
				frameInfo_[j][i] = 3; // 3 mines
			}
			else if (redBit == 0 && greenBit == 0 && blueBit == 128) { // dark blue
				frameInfo_[j][i] = 4; // 4 mines
			}
			else if (redBit == 128 && greenBit == 0 && blueBit == 0) { // dark red
				frameInfo_[j][i] = 5; // 5 mines
			}
			else if (redBit == 0 && greenBit == 128 && blueBit == 128) { // blue green
				frameInfo_[j][i] = 6; // 6 mines
			}
			else if (redBit == 0 && greenBit == 0 && blueBit == 0) { // black
				if ((int)(ScreenData[4 * ((y*screenW - 1) + x)]) == 255) { // red
					frameInfo_[j][i] = 0; // flag
				}
				else if ((int)(ScreenData[4 * ((y*screenW - 1) + x - 1)]) == 255) { // white
					frameInfo_[j][i] = 9; // mine!
					mineFlag_ = true;
				}
				else {
					frameInfo_[j][i] = 7; // 7 mines
				}
			}
			else if (redBit == 128 && greenBit == 128 && blueBit == 128) { //dark gray
				frameInfo_[j][i] = 8; // 8 mines
			}
			else {
				frameInfo_[j][i] = -3; // nothing
				cout << "BLOCK ERROR: nothing recognized" << endl;
			}
		}
	}

	//release
	DeleteDC(hdc);
	DeleteObject(hbmp);
	ReleaseDC(NULL, hdcScreen);
}
