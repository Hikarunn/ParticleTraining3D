#include "DxLib.h"
#include "Scene.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"

Camera::Camera(Scene* scene)
{
	scene_ = scene;
}

void Camera::Init(void)
{

	//�J���������p�x
	angleH_ = DX_PI_F;

	//�����p�x0�x
	angleV_ = 0.0f;
}

void Camera::Process(void)
{
	//�J�����̉�]
	if (CheckHitKey(KEY_INPUT_LSHIFT)) 
	{
		//��
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			angleH_ -= CAMERA_ANGLE_SPEED;
			if (angleH_ < -DX_PI_F)
			{
				angleH_ += DX_TWO_PI_F;
			}
		}

		//�E
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			angleH_ += CAMERA_ANGLE_SPEED;
			if (angleH_ > DX_PI_F)
			{
				angleH_ -= DX_TWO_PI_F;
			}
		}

		//��
		if (CheckHitKey(KEY_INPUT_UP))
		{
			angleV_ -= CAMERA_ANGLE_SPEED;
			if (angleV_ < -DX_PI_F / 2.0f - 0.6f)
			{
				angleV_ = -DX_PI_F / 2.0f - 0.6f;
			}
		}

		//��
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			angleV_ += CAMERA_ANGLE_SPEED;
			if (angleV_ > DX_PI_F / 2.0f - 0.6f)
			{
				angleV_ = DX_PI_F / 2.0f - 0.6f;
			}
		}
	}

	target_ = VAdd(scene_->player_->GetPos(), VGet(0.0f, CAMERA_PLAYER_TARGET_HEIGHT, 0.0f));

	CameraPos();
	

}

void Camera::CameraPos(void)
{
	MATRIX rotZ_, rotY_;
	float cameraPlayerLength;
	
	// ���������̉�]
	rotY_ = MGetRotY(angleH_);

	// ��������
	rotZ_ = MGetRotZ(angleV_);

	// �J��������v���C���[�ւ̏�������
	cameraPlayerLength = CAMERA_PLAYER_LENGTH;

	// �J�������W
	eye_ = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotZ_), rotY_), target_);


	// �����_����J�����̊ԂɃX�e�[�W�����邩���ׂ�

	CheckStage(rotZ_, rotY_, cameraPlayerLength);

	// �J�������𔽉f
	SetCameraPositionAndTarget_UpVecY(eye_, target_);
}

// �����_����J�����̊ԂɃX�e�[�W�����邩���ׂ�
void Camera::CheckStage(MATRIX rotZ, MATRIX rotY, float cameraPlayerLength)
{
	MV1_COLL_RESULT_POLY_DIM res_{};
	int hitNum_;


	res_ = MV1CollCheck_Capsule(scene_->stage_->modelHandle_, -1, target_, eye_, CAMERA_COLLISION_SIZE);
	hitNum_ = res_.HitNum;
	MV1CollResultPolyDimTerminate(res_);
	if (hitNum_ != 0)
	{
		

		// �|���S���ɓ�����Ȃ�����
		notHitLength_ = 0.0f;

		// �|���S���ɓ����鋗��
		hitLength = cameraPlayerLength;
		do
		{
			// �����邩�ǂ����̃e�X�g�����̃Z�b�g
			testLength = notHitLength_ + (hitLength - notHitLength_) / 2.0f;

			// �e�X�g�p�J�������W���Z�o
			testPos_ = VAdd(VTransform(VTransform(VGet(-testLength, 0.0f, 0.0f), rotZ), rotY), target_);

			// �V�������W�ŕǂɓ����邩
			res_ = MV1CollCheck_Capsule(scene_->stage_->modelHandle_, -1, target_, testPos_, CAMERA_COLLISION_SIZE);
			hitNum_ = res_.HitNum;
			MV1CollResultPolyDimTerminate(res_);

			if (hitNum_ != 0) {

				// �����鋗����testLength�ɕύX����
				hitLength = testLength;
			}
			else
			{
				// ������Ȃ������炻�̋�����testLength�ɕύX����
				notHitLength_ = testLength;
			}

			// hitLength��notHitLength���\���ɋ߂Â��Ă��Ȃ������烋�[�v
		} while (hitLength - notHitLength_ > 0.1f);
		
		// �J�������W�Z�b�g
		eye_ = testPos_;

	}
}

VECTOR Camera::GetEye(void)
{
	return eye_;
}

VECTOR Camera::GetTargetPos(void)
{
	return target_;
}
