#pragma once
#include "singleton.h"
#include <iostream>
#include <vector>
//#include "opencv2\opencv.hpp"

using namespace std;
//using namespace cv;

class CImageProcess
{
public:
	void getFrame();
private:
	int left_;
	int right_;
	int top_;
	int bottom_;
	int blocksX_;
	int blocksY_;
	vector<vector<int>> frameRed_;
	vector<vector<int>> frameGreen_;
	vector<vector<int>> frameBlue_;
};

typedef NormalSingleton<CImageProcess> ImageProcess;