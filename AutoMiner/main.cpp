#include "ImageProcess.h"
#include "MouseOperation.h"
#include <stdlib.h>

int main() {
	ImageProcess::Instance()->getFrame();
	vector<vector<int>> frameInfo = ImageProcess::Instance()->getFrameInfo();

	for (vector<int> rows : frameInfo) {
		for (int frame : rows) {

		}
	}

	while (1) {
		MouseOperation::Instance()->goClick(3, 5);
	}
	system("pause");
}