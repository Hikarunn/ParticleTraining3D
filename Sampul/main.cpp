// �p�[�e�B�N����{
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
	// �d�r�b�L�[��������邩�A�E�C���h�E��������܂Ń��[�v
	
	/*player_->Terminate();

	stage_->Terminalize();*/



	
}
