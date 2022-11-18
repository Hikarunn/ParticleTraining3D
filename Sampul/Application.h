#pragma once
#include "Scene.h"
class Application
{
public:
	bool Init(void);
	void Run(void);
	bool Release(void);

private:

	Scene scene_;
	bool isFullScreen = false;
};

