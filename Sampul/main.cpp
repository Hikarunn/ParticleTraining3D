// パーティクル基本
#include <DxLib.h>
#include <math.h>
#include "Effect.h"
#include "Camera.h"
#include "Stage.h"
#include "Player.h"





// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);

	// ライブラリの初期化
	if (DxLib_Init() < 0)
		return -1;


	
	
	bool isFullScreen = false;

	// ＥＳＣキーが押されるか、ウインドウが閉じられるまでループ
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

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}


	// ライブラリの後始末
	DxLib_End();

	// ソフト終了
	return 0;
}
