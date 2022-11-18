#include "DxLib.h"
//#include "_debug/_DebugConOut.h"
//#include "_debug/_DebugDispOut.h"
#include "Application.h"

bool Application::Init(void)
{
	SetWindowTextW(L"Effect");

	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	// ���C�u�����̏�����
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

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
	
}

void Application::Run(void)
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ��N���A
		ClearDrawScreen();



		if (CheckHitKey(KEY_INPUT_F1) && !isFullScreen)
		{
			ChangeWindowMode(FALSE);
			// �`���𗠉�ʂɂ���
			SetDrawScreen(DX_SCREEN_BACK);

			isFullScreen = true;
		}
		if (CheckHitKey(KEY_INPUT_F2) && isFullScreen)
		{
			ChangeWindowMode(TRUE);
			// �`���𗠉�ʂɂ���
			SetDrawScreen(DX_SCREEN_BACK);
			isFullScreen = false;
		}

		/*	player_->Process();
			camera_->Process();
			stage_->Draw();*/
		scene_.Update();

			// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
}

bool Application::Release(void)
{
// ���C�u�����̌�n��
DxLib_End();

// �\�t�g�I��
return true;
}
