#include "DxLib.h"
//#include "_debug/_DebugConOut.h"
//#include "_debug/_DebugDispOut.h"
#include "Application.h"

bool Application::Init(void)
{
	SetWindowTextW(L"Effect");

	// ウインドウモードで起動
	ChangeWindowMode(TRUE);

	// ライブラリの初期化
	if (DxLib_Init() == -1) {
		return false;
	}
	scene_.Init();

	/*player_ = new Player();
	player_->Init();
	camera_ = new Camera();
	camera_->Init();
	stage_ = new Stage();
	stage_->Init();*/

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
	
}

void Application::Run(void)
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面をクリア
		ClearDrawScreen();



		if (CheckHitKey(KEY_INPUT_F1) && !isFullScreen)
		{
			ChangeWindowMode(FALSE);
			// 描画先を裏画面にする
			SetDrawScreen(DX_SCREEN_BACK);

			isFullScreen = true;
		}
		if (CheckHitKey(KEY_INPUT_F2) && isFullScreen)
		{
			ChangeWindowMode(TRUE);
			// 描画先を裏画面にする
			SetDrawScreen(DX_SCREEN_BACK);
			isFullScreen = false;
		}

		/*	player_->Process();
			camera_->Process();
			stage_->Draw();*/
		scene_.Update();

			// 裏画面の内容を表画面に反映
		ScreenFlip();
	}
}

bool Application::Release(void)
{
// ライブラリの後始末
DxLib_End();

// ソフト終了
return true;
}
