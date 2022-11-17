// �p�[�e�B�N����{
#include <DxLib.h>
#include <math.h>
#include "Effect.h"
#include "Camera.h"
#include "Stage.h"
#include "Player.h"


Player* player_;
Camera* camera_;
Stage* stage_;


//void Draw(void)
//{
//	// �X�e�[�W�̕`�揈��
//	stage_->Draw();
//
//	// �v���C���[���f���̕`��
//	//player_->Draw();
//
//	
//}


// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	// ���C�u�����̏�����
	if (DxLib_Init() < 0)
		return -1;

	player_ = new Player();
	player_->Init();
	camera_ = new Camera();
	camera_->Init();
	stage_ = new Stage();
	stage_->Init();

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	
	bool isFullScreen = false;

	// �d�r�b�L�[��������邩�A�E�C���h�E��������܂Ń��[�v
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

		player_->Process();
		camera_->Process();
		stage_->Draw();


		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
	player_->Terminate();

	stage_->Terminalize();

	// ���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�I��
	return 0;
}
