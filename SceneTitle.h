#pragma once

#include "player.h"
#include "car.h"

class SceneTitle
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	//�����������A�I������
	void init();
	void end();

	//�Q�[������		�V�[���؂�ւ�����true
	bool update();
	//�`��
	void draw();
};