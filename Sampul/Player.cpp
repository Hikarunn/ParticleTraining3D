#include <DxLib.h>
#include <math.h>
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
	modelHandle_ = MV1LoadModel("Model/Test.x");
	
	// �e�̓ǂݍ���
	shadowHandle_ = LoadGraph("Model/Shadow.tga");
	
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
	VECTOR advanceMoveVec_;	// �O�i���������Ƃ��̂̈ړ�����
	VECTOR leftMoveVec_;	// �����������Ƃ��̂̈ړ�����


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
