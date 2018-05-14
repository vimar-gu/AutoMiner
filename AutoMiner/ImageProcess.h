#pragma once
#include "singleton.h"
#include "opencv2\opencv.hpp"

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
	cv::Mat frame;
};

typedef NormalSingleton<CImageProcess> ImageProcess;