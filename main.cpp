#include "DxLib.h"
#include "game.h"

#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneTest.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	//現在のシーン番号		0:Title 1Main 2:Test
	int sceneNo = 0;

	SceneTitle sceneTitle;
	SceneMain sceneMain;
	SceneTest sceneTest;

	switch (sceneNo)
	{
	case 0:
		sceneTitle.init();
		break;
	case 1:
		sceneMain.init();
		break;
	case 2:
		sceneTest.init();
		break;
	}

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		//シーン変更フラグ
		bool isChange = false;
		switch (sceneNo)
		{
		case 0:
			isChange = sceneTitle.update();
			sceneTitle.draw();
			if (isChange)
			{
				sceneTitle.end();

				sceneMain.init();
				sceneNo = 1;
			}
			break;
		case 1:
			sceneMain.update();
			break;
		case 2:
			sceneTest.update();
			break;
		}

		switch (sceneNo)
		{
		case 0:
			sceneTitle.draw();
			break;
		case 1:
			sceneMain.draw();
			break;
		case 2:
			sceneTest.draw();
			break;
		}


		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	switch (sceneNo)
	{
	case 0:
		sceneTitle.end();
		break;
	case 1:
		sceneMain.end();
		break;
	case 2:
		sceneTest.end();
		break;
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}