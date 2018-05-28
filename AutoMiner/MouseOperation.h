#pragma once
#include <iostream>
#include <Windows.h>
#include "singleton.h"

using namespace std;

class CMouseOperation
{
public:
	CMouseOperation();
	pair<int, int> getMousePos();
	void goClick(int i, int j);
private:
	int left_;
	int right_;
	int top_;
	int bottom_;
	int mouseX_;
	int mouseY_;
};

typedef NormalSingleton<CMouseOperation> MouseOperation;