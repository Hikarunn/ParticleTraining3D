#include <DxLib.h>
#include <math.h>
#include "Camera.h"
#include "Player.h"

//������
void Player::Init(void)
{
	// �����ʒu�i���W�j
	pos_ = VGet(0.0f, 0.0f, 0.0f);
	
	//��]�n��0
	angle_ = 0;

	//�W�����v�͏�����
	jumpPower_ = 0.0f;

	// ���f���̓ǂݍ���
	modelHandle_ = MV1LoadModel(L"Model/Test.x");
	
	// �e�̓ǂݍ���
	shadowHandle_ = LoadGraph(L"Model/Shadow.tga");
	
	// ������ԂŃv���C���[�������ׂ������iX�����j
	moveDir_ = VGet(1.0f, 0.0f, 0.0f);
	
	//�v���C���[�̏������
	anim_ = AnimAction::STAY;

	// �����A�j���[�V�����Z�b�g
	PlayAnim((int)anim_);

}

void Player::Terminate(void)
{
	// ���f���̍폜
	MV1DeleteModel(modelHandle_);

	// �e�̍폜
	DeleteGraph(shadowHandle_);
}

void Player::Process(void)
{


	LootFlameCancel();

	MoveVecOutput();

	// ���̃t���[���ł̈ړ��x�N�g����������
	moveVec_ = VGet(0.0f, 0.0f, 0.0f);

	//�ړ��������ǂ����̃t���O����������Ԃł�false�ɂ���
	moveFlag_ = false;



}

void Player::Move(VECTOR MoveVector)
{

}

void Player::AnglePlocess(void)
{
}

void Player::PlayAnim(int PlayAnim)
{
}

void Player::AnimProcess(void)
{
}

void Player::PlayShadowRender(void)
{
}

void Player::Jump(void)
{
	AddGravity();
}

void Player::SetJumpPow(float jumpPow)
{
	jumpPower_ = jumpPow;
	if (jumpPower_ > MAX_JUMP_POW) {
		jumpPower_ = MAX_JUMP_POW;
	}
}

void Player::AddGravity(void)
{
	SetJumpPow(jumpPower_ + PLAYER_GRAVITY);
}

void Player::Draw(void)
{
	MV1DrawModel(modelHandle_);
}

VECTOR Player::GetPos(void)
{
	return pos_;
}

void Player::LootFlameCancel(void)
{
	MATRIX LocalMatrix;

	// ���[�U�[�s�������
	MV1ResetFrameUserLocalMatrix(modelHandle_, 2);

	// ���݂̃��[�g�t���[���̍s����擾
	LocalMatrix = MV1GetFrameLocalMatrix(modelHandle_, 2);

	// z�������̕��s�ړ������𖳌��ɂ���
	LocalMatrix.m[3][2] = 0.0f;

	// ���[�U�[�s��Ƃ��ĕ��s�ړ������𖳌��ɂ����s������[�g�t���[���ɃZ�b�g����
	MV1SetFrameUserLocalMatrix(modelHandle_, 2, LocalMatrix);

}

/*VECTOR advanceMoveVec_;	// �O�i���������Ƃ��̂̈ړ�����
	VECTOR leftMoveVec_;	// �����������Ƃ��̂̈ړ�����
	VECTOR moveVec_;		// ���̃t���[���̈ړ��x�N�g��
	bool moveFlag_;			// �ړ��������ǂ����̃t���O�itrue���ړ�����,false���ړ����Ă��Ȃ�)
*/

void Player::MoveVecOutput(void)
{

	VECTOR cameraTarget_ = camera_->GetTargetPos();
	VECTOR cameraEye_ = camera_->GetEye();
	// ��{�^�����������Ƃ��̃v���C���[�̈ړ��x�N�g���̓J�����T������������Y�����𔲂�������
	advanceMoveVec_ = VSub(cameraTarget_, cameraEye_);

	advanceMoveVec_.y = 0.0f;

	// ���{�^�����������Ƃ��̃v���C��̈ړ��x�N�g���͏���������Ƃ��̕����x�N�g����Y���̃v���X�����̃x�N�g���ɐ����ȕ���
	leftMoveVec_ = VCross(advanceMoveVec_, VGet(0.0f, 1.0f, 0.0f));

	// ��̃x�N�g���𐳋K��
	advanceMoveVec_ = VNorm(advanceMoveVec_);
	leftMoveVec_ = VNorm(leftMoveVec_);
	
}

void Player::MovementControl(void)
{
	if (CheckHitKey(KEY_INPUT_LSHIFT))
	{
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			// �ړ������������ꂽ���̈ړ��x�N�g���̉��Z
			moveVec_ = VAdd(moveVec_, leftMoveVec_);

			// �ړ��������ǂ����̃t���O
			moveFlag_ = true;

		}
		else if(CheckHitKey(KEY_INPUT_RIGHT)) {
			// �ړ������������ꂽ���̈ړ��x�N�g���̉��Z
			moveVec_ = VAdd(moveVec_, VScale(leftMoveVec_, -1.0f));

			// �ړ��������ǂ����̃t���O
			moveFlag_ = true;
		}


	}
}
