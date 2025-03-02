#pragma once

#include "player.h"
#include "car.h"

class SceneTitle
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	//初期化処理、終了処理
	void init();
	void end();

	//ゲーム処理		シーン切り替え時はtrue
	bool update();
	//描画
	void draw();

private:
	//フェード処理
	int m_fadeBright;
	//フェード処理
	int m_fadeSpeed;
};