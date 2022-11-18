// パーティクル基本
#include <DxLib.h>
#include "Application.h"
//#include "Effect.h"
//#include "Camera.h"
//#include "Stage.h"
//#include "Player.h"

//
//Player* player_;
//Camera* camera_;
//Stage* stage_;


//void Draw(void)
//{
//	// ステージの描画処理
//	stage_->Draw();
//
//	// プレイヤーモデルの描画
//	//player_->Draw();
//
//	
//}


// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application application_;

	if (!application_.Init())
	{
		return -1;
	}
	application_.Run();

	if (!application_.Release())
	{
		return -1;
	}

	return 0;
	// ＥＳＣキーが押されるか、ウインドウが閉じられるまでループ
	
	/*player_->Terminate();

	stage_->Terminalize();*/



	
}
