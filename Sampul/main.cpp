// �p�[�e�B�N����{
#include "DxLib.h"

// �V���b�g�ƃp�[�e�B�N���̍ő吔
#define MAX_SHOT	4
#define MAX_SPARK	1600

// �V���b�g�f�[�^�^
typedef struct tagSHOT
{
	int Valid;	// ���̃f�[�^���g�p�����A�t���O
	int shotPosX_, shotPosY_;	// �V���b�g�̈ʒu
} SHOT;

// �Ήԃf�[�^�^
typedef struct tagSPARK
{
	int Valid;	// ���̃f�[�^���g�p�����A�t���O
	int X, Y;	// �ΉԂ̈ʒu
	int Sx, Sy;	// �ΉԂ̈ړ���
	int G;		// �ΉԂ̏d��
	int Bright;	// �ΉԂ̖��邳
} SPARK;

int PlayerX, PlayerY;	// �v���C���[�̈ʒu
int Image;
int Image1;
int Image2;
int time;
SHOT shot_[MAX_SHOT];	// �V���b�g�f�[�^
SPARK spark_[MAX_SPARK];	// �Ήԃf�[�^


void CreateSpark(int x, int y);	// �ΉԂ��o������
void MoveSpark(void);	// �ΉԈړ�����
void CreateShot(void);	// �V���b�g��������
void MoveShot(void);	// �V���b�g�̈ړ�����


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	int Key = 0;
	int OldKey = 0;	// �O�̃L�[���͏��
	int sparkNum_, shotNum_;

	

	SetGraphMode(640, 480, 16);
	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// �v���C���[�̏����ʒu���Z�b�g
	PlayerX = 320;
	PlayerY = 400;

	// �V���b�g�̑��݂�����������
	for (sparkNum_ = 0; sparkNum_ < MAX_SHOT; sparkNum_++)
		shot_[sparkNum_].Valid = 0;

	// �ΉԂ̑��݂�����������
	for (sparkNum_ = 0; sparkNum_ < MAX_SPARK; sparkNum_++)
		spark_[sparkNum_].Valid = 0;

	// ���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		time++;
		// �L�[���͎擾
		OldKey = Key;
		Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		if (Key & PAD_INPUT_RIGHT) PlayerX += 3;	// �E�������Ă�����E�ɐi��
		if (Key & PAD_INPUT_LEFT) PlayerX -= 3;	// ���������Ă����獶�ɐi��

		// �V���b�g�̈ړ�����
		MoveShot();

		// �ΉԂ̈ړ�����
		MoveSpark();

		// �V���b�g�{�^���������Ă�����V���b�g���o��
		if ((Key & ~OldKey) & PAD_INPUT_A) CreateShot();

		// ��ʂ�����������
		ClearDrawScreen();
		Image = LoadGraph("Image/AuroraRing_R.png");
		Image1 = LoadGraph("Image/AuroraRing_G.png");
		Image2 = LoadGraph("Image/AuroraRing_B.png");
		// �v���C���[��`�悷��
		//DrawBox(PlayerX, PlayerY, PlayerX + 48, PlayerY + 48, GetColor(255, 0, 0), TRUE);
		DrawBox(PlayerX, PlayerY, PlayerX + 48, PlayerY + 48, 0xff0000,TRUE);
		//DrawGraph(0, 0,
		//	/*GetColor(spark_[shotNum_].Bright, spark_[shotNum_].Bright, spark_[shotNum_].Bright)*/
		//	Image, true);
		// �V���b�g��`�悷��
		for (shotNum_ = 0; shotNum_ < MAX_SHOT; shotNum_++)
		{
			// �V���b�g�f�[�^���L���Ȏ��̂ݕ`��
			if (shot_[shotNum_].Valid == 1)
				DrawBox(shot_[shotNum_].shotPosX_, shot_[shotNum_].shotPosY_, shot_[shotNum_].shotPosX_ + 16, shot_[shotNum_].shotPosY_ + 16,
					0xffffff,true);

		}
		DrawFormatString(0, 0, 0xffffff, "aaaaaaaa");

		// �ΉԂ�`�悷��
		for (shotNum_ = 0; shotNum_ < MAX_SPARK; shotNum_++)
		{
			// �Ήԃf�[�^���L���Ȏ��̂ݕ`��
			/*	if (time / 10 % 3)*/ 
				if (spark_[shotNum_].Valid == 1) {
					DrawGraph(spark_[shotNum_].X / 200, spark_[shotNum_].Y/ 100,
						/*GetColor(spark_[shotNum_].Bright, spark_[shotNum_].Bright, spark_[shotNum_].Bright)*/
						Image, true);

					
						DrawGraph(spark_[shotNum_].X / 300, spark_[shotNum_].Y / 100,
							/*GetColor(spark_[shotNum_].Bright, spark_[shotNum_].Bright, spark_[shotNum_].Bright)*/
							Image1, true);
					
					
						DrawGraph(spark_[shotNum_].X / 100, spark_[shotNum_].Y / 100,
							/*GetColor(spark_[shotNum_].Bright, spark_[shotNum_].Bright, spark_[shotNum_].Bright)*/
							Image2, true);
					
				}
			
		/*	if (spark_[shotNum_].Valid == 1)
				DrawPixel(spark_[shotNum_].X / 100, spark_[shotNum_].Y / 100,
					GetColor(spark_[shotNum_].Bright, spark_[shotNum_].Bright, spark_[shotNum_].Bright));*/


		}
		

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}

// �ΉԂ��o������
void CreateSpark(int x, int y)
{
	int sparkNum_;

	// �g���Ă��Ȃ��Ήԃf�[�^��T��
	for (sparkNum_ = 0; sparkNum_ < MAX_SPARK; sparkNum_++)
	{
		if (spark_[sparkNum_].Valid == 0) break;
	}

	// �����g���Ă��Ȃ��Ήԃf�[�^����������ΉԂ��o��
	if (sparkNum_ != MAX_SPARK)
	{
		// �ΉԂ̈ʒu��ݒ�
		spark_[sparkNum_].X = x * 100;
		spark_[sparkNum_].Y = y * 100;

		// �ړ��͂�ݒ�
		spark_[sparkNum_].Sx = GetRand(1000) - 500;
		spark_[sparkNum_].Sy = -GetRand(500);

		// �ΉԂ̏d�����Z�b�g
		spark_[sparkNum_].G = GetRand(10);

		// �ΉԂ̖��邳�Z�b�g
		spark_[sparkNum_].Bright = 255;

		// �Ήԃf�[�^���g�p���ɃZ�b�g
		spark_[sparkNum_].Valid = 1;
	}
}

// �ΉԈړ�����
void MoveSpark(void)
{
	int sparkNum_;

	// �ΉԂ̈ړ�����
	for (sparkNum_ = 0; sparkNum_ < MAX_SPARK; sparkNum_++)
	{
		// �Ήԃf�[�^��������������X�L�b�v
		if (spark_[sparkNum_].Valid == 0) continue;

		// �ʒu���ړ��͂ɉ����Ă��炷
		spark_[sparkNum_].Y += spark_[sparkNum_].Sy;
		spark_[sparkNum_].X += spark_[sparkNum_].Sx;

		// �ړ��͂�ύX
		spark_[sparkNum_].Sy += spark_[sparkNum_].G;

		// �ΉԂ̖��邳��������
		spark_[sparkNum_].Bright -= 2;

		// �ΉԂ̖��邳���O�ȉ��ɂȂ�����Ήԃf�[�^�𖳌��ɂ���
		if (spark_[sparkNum_].Bright < 0) spark_[sparkNum_].Valid = 0;
	}
}

// �V���b�g��������
void CreateShot(void)
{
	int shotNum_;

	// �g���Ă��Ȃ��V���b�g�f�[�^��T��
	for (shotNum_ = 0; shotNum_ < MAX_SHOT; shotNum_++)
	{
		if (shot_[shotNum_].Valid == 0) break;
	}

	// �����g���Ă��Ȃ��V���b�g�f�[�^����������V���b�g���o��
	if (shotNum_ != MAX_SHOT)
	{
		// �V���b�g�̈ʒu��ݒ�
		shot_[shotNum_].shotPosX_ = PlayerX + 16;
		shot_[shotNum_].shotPosY_ = PlayerY;

		// �V���b�g�f�[�^���g�p���ɃZ�b�g
		shot_[shotNum_].Valid = 1;
	}
}

// �V���b�g�̈ړ�����
void MoveShot(void)
{
	int shotNum_, sparkNum_, sparkMax_;

	// �V���b�g�̈ړ�����
	for (shotNum_ = 0; shotNum_ < MAX_SHOT; shotNum_++)
	{
		// �V���b�g�f�[�^��������������X�L�b�v
		if (shot_[shotNum_].Valid == 0) continue;

		// �ʒu����ɂ��炷
		shot_[shotNum_].shotPosY_ -= 8;

		// ��ʊO�ɏo�Ă�����ΉԂ��o�������ƃV���b�g�f�[�^�𖳌��ɂ���
		if (shot_[shotNum_].shotPosY_ < 150)
		{
			// �ΉԂ��o�������Z�b�g
			sparkMax_ = GetRand(60);
			for (sparkNum_ = 0; sparkNum_ < sparkMax_; sparkNum_++)
			{
				// �ΉԂ𐶐�
				CreateSpark(shot_[shotNum_].shotPosX_ + 8, shot_[shotNum_].shotPosY_ + 8);
			}

			// �V���b�g�f�[�^�𖳌��ɂ���
			shot_[shotNum_].Valid = 0;
		}
	}
}




