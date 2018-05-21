#pragma once
#include "singleton.h"
#include <iostream>
#include <vector>

using namespace std;

class CImageProcess
{
public:
	CImageProcess() { mineFlag_ = false; }
	void getFrame();
	bool getMineFlag() { return mineFlag_; }
	vector<vector<int>> getFrameInfo() { return frameInfo_; }
private:
	int left_;
	int right_;
	int top_;
	int bottom_;
	int blocksX_;
	int blocksY_;
	bool mineFlag_;
	vector<vector<int>> frameInfo_;
};

typedef NormalSingleton<CImageProcess> ImageProcess;