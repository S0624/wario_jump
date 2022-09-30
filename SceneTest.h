#pragma once

#include "player.h"
#include "car.h"

class SceneTest
{
public:
	SceneTest();
	virtual ~SceneTest();

	//‰Šú‰»ˆ—AI—¹ˆ—
	void init();
	void end();

	//ƒQ[ƒ€ˆ—
	bool update();
	//•`‰æ
	void draw();
};