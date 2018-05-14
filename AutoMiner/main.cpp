#include "ImageProcess.h"
#include <stdlib.h>

int main() {
	ImageProcess::Instance()->getFrame();
	//cvWaitKey();
	system("pause");
}