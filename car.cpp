#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	//待ち時間
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;
	//車の速度
	constexpr int kSpeed = -7.0f;
	//ジャンプ力
	constexpr float kJumpAcc = -20.0f;
	//重力
	constexpr float kGravity = 1.0f;
}

Car::Car()
{
	m_handle = -1;
	m_fieldY = 0.0f;
	m_moveType;
	m_waitFrame = 0;
	m_stopFrame = 0;
	m_isJump = false;
}

void Car::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
}

void Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;

	//動きのバリエーションを閃絡
	int randNum = GetRand(99);
	if (randNum < 38)
	{
		m_moveType = kMoveTypeNormal;
	}
	else if (randNum < 38 + 30)
	{
		m_moveType = kMoveTypeStop;
	}
	else if (randNum < 38 + 30 + 30)
	{
		m_moveType = kMoveTypeJump;
	}
	else
	{
		m_moveType = kMoveTypeReturn;
	}

	//デバック用に挙動を強制
	//m_moveType = kMoveTypeJump;
	m_moveType = kMoveTypeStop;
	//m_moveType = kMoveTypeReturn;
	//動き始めるまでの時間を設定	1秒から3秒待つ 60フレームから180フレーム
	m_waitFrame = GetRand(kWaitFrameMax) + kWaitFrameMin;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}

	switch (m_moveType)
	{
	case kMoveTypeNormal:
		updateNormal();
		break;
	case kMoveTypeStop:
		updateStop();
		break;
	case kMoveTypeJump:
		updateJump();
		break;
	case kMoveTypeReturn:
		updateReturn();
		break;
	default:
		updateNormal();
		break;
	}

	m_pos += m_vec;
}

void Car::draw()
{
	DrawFormatString(0, 0, GetColor(255,255,255), "wait:%d", m_waitFrame);
	if (m_vec.x <= 0.0f)
	{
		DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
	else
	{
		DrawTurnGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
}

//まっすぐ進む
void Car::updateNormal()
{
	m_pos += m_vec;
}

//一時停止フェイント
void Car::updateStop()
{
	if ((m_pos.x < 400.0f) && (m_stopFrame < 30))
	{
		m_stopFrame++;
		return;
	}
	m_pos += m_vec;
}

//ジャンプする
void Car::updateJump()
{
	m_pos += m_vec;
	//地面との当たり
	bool isField = false;
	if (m_pos.y > m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}

	if (m_pos.x < 500)
	{
		if (isField)
		{
			m_vec.y = kJumpAcc;				//ジャンプ開始
		}
	}
	
	m_vec.y += kGravity;

}



//途中で引き返す（必ず成功）

void Car::updateReturn()
{
	if ((m_pos.x < 360.0f) && (m_stopFrame < 60))
	{
		m_stopFrame++;
		if (m_stopFrame >= 60)
		{
			m_vec.x *= -1.0f;
		}
		return;
	}
	m_pos += m_vec;
}