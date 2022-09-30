#include "SceneTitle.h"
#include"DxLib.h"

SceneTitle::SceneTitle()
{

}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::init()
{

}

void SceneTitle::end()
{

}

bool SceneTitle::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		return true;
	}

	return 0;
}

void SceneTitle::draw()
{
	DrawString(0, 0, "SceneMain‚Ì•\Ž¦", GetColor(255, 255, 255));
}

