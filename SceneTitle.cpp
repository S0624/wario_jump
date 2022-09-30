#include "SceneTitle.h"
#include"DxLib.h"

SceneTitle::SceneTitle()
{
	m_fadeBright = 0;
	m_fadeSpeed = 0;
}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::init()
{
	m_fadeBright = 0;
	m_fadeSpeed = 8;
}

void SceneTitle::end()
{
	SetDrawBright(255, 255, 255);
}

bool SceneTitle::update()
{
	//�t�F�[�h�C��
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright > 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	if ((m_fadeBright <= 0) && (m_fadeSpeed < 0))
	{
		//�t�F�[�h�A�E�g���������玟�̃V�[����
		m_fadeBright = 0;
		return true;
	}

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (m_fadeSpeed == 0)			//�t�F�[�h�A�E�g�������Ă���{�^���̓��͂��󂯕t����
	{
		if (padState & PAD_INPUT_1)
		{
			//return true;
			m_fadeSpeed = -8;		//�t�F�[�h�A�E�g
		}
	}
	
	return 0;
}

void SceneTitle::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	DrawString(0, 0, "SceneMain�̕\��", GetColor(255, 255, 255));
}

