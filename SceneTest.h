#pragma once

#include "player.h"
#include "car.h"

class SceneTest
{
public:
	SceneTest();
	virtual ~SceneTest();

	//�����������A�I������
	void init();
	void end();

	//�Q�[������
	bool update();
	//�`��
	void draw();
};