// �p�[�e�B�N����{
#include <DxLib.h>
#include <math.h>
#include "Effect.h"
#include "Camera.h"
#include "Stage.h"
#include "Player.h"





// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	// ���C�u�����̏�����
	if (DxLib_Init() < 0)
		return -1;

	
	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// �d�r�b�L�[��������邩�A�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ��N���A
		ClearDrawScreen();

	

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}


	// ���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�I��
	return 0;
}
