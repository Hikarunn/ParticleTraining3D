#include <DxLib.h>
#include <math.h>
#include "Scene.h"
#include "Camera.h"
#include "Stage.h"
#include "Player.h"

Player::Player(Scene* scene)
{
	scene_ = scene;

	Init();
}

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
	modelHandle_ = MV1LoadModel(L"Model/Jump.mv1");
	
	// �e�̓ǂݍ���
	shadowHandle_ = LoadGraph(L"Model/Shadow.tga");
	
	// ������ԂŃv���C���[�������ׂ������iX�����j
	moveDir_ = VGet(1.0f, 0.0f, 0.0f);

	// �����̃X�e�[�^�X�Z�b�g(�ҋ@)
	state_ = ActionState::STAY;

	//�v���C���[�̏������
	anim_ = AnimAction::STAY;

	// �A�j���[�V�������Đ�����
	animTotalTime_ = 0.0f;

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

	MovementControl();

	StopMove();

	// ��Ԃ��W�����v�̏ꍇ
	if (state_ == ActionState::JUMP)
	{
		// Y�������̑��x���d�͕����Z����
		jumpPower_ -= PLAYER_GRAVITY;

		// �����������Ă��Ă��Đ�����Ă���A�j���[�V�������㏸�p�̂��̂������ꍇ
		if (jumpPower_ < 0.0f && MV1GetAttachAnim(modelHandle_, playAnim1_) == 2)
		{
			// �����������A�j���[�V�������Đ�����
			anim_ = AnimAction::STAY;
			PlayAnim((int)anim_);
		}

		// �ړ��x�N�g����Y������Y���������߂Â���
		moveVec_.y = jumpPower_;
	}

	// �v���C���[�̈ړ������Ƀ��f���̕������߂Â���
	AnglePlocess();

	// �ړ��x�N�g�������ƂɃR���W�������l�����v���C���[���ړ�
	Move(moveVec_);

	// �A�j���[�V��������
	AnimProcess();
	//// ���V�t�g��������t��Ȃ�������ړ�
	//if (CheckHitKey(KEY_INPUT_LSHIFT) == 0) 
	//{
	//	// �������{�^���������ꂽ��J�������猩�č��ֈړ�
	//	if (CheckHitKey(KEY_INPUT_LEFT))
	//	{
	//		// ���͂ɑ΂��ړ��x�N�g�����Z�i���j�v
	//		moveVec_ = VAdd(moveVec_, leftMoveVec_);
	//	
	//		// �ړ��t���O
	//		moveFlag_ = true;
	//	}
	//	// �E�����{�^���������ꂽ��J�������猩�ĉE�ֈړ�
	//	else if (CheckHitKey(KEY_INPUT_RIGHT))
	//	{
	//		// ���͂ɑ΂��ړ��x�N�g�����Z�i�E�j
	//		moveVec_ = VAdd(moveVec_, VScale(leftMoveVec_, -1.0f));
	//
	//		// �ړ��t���O
	//		moveFlag_ = true;
	//	}
	//
	//	// ������{�^���������ꂽ��J�������猩�ĉ��ֈړ�
	//	if (CheckHitKey(KEY_INPUT_UP))
	//	{
	//		// ���͂ɑ΂��ړ��x�N�g�����Z�i���j�v
	//		moveVec_ = VAdd(moveVec_, advanceMoveVec_);
	//
	//		// �ړ��t���O
	//		moveFlag_ = true;
	//	}
	//	// �������{�^���������ꂽ��J�������猩�Ď�O�ֈړ�
	//	else if (CheckHitKey(KEY_INPUT_DOWN))
	//	{
	//		// ���͂ɑ΂��ړ��x�N�g�����Z�i��O�j
	//		moveVec_ = VAdd(moveVec_, VScale(advanceMoveVec_, -1.0f));
	//
	//		// �ړ��t���O
	//		moveFlag_ = true;
	//	}
	//
	//	
	//}



}

void Player::Move(VECTOR MoveVector)
{

}

void Player::AnglePlocess(void)
{
}

// �V�����A�j���[�V�������Đ�
void Player::PlayAnim(int PlayAnim)
{
	//�Đ����̃��[�V�������L����������f�^�b�`
	if (playAnim2_ != -1) 
	{
		MV1DetachAnim(modelHandle_, playAnim2_);
		playAnim2_ = -1;
	}

	// ���܂ōĐ����̃��[�V�����P���������̂��Q�Ɉړ�
	playAnim2_ = playAnim1_;
	animPlayCount1_ = 0.0f;

	// �u�����h���͍Đ����̃��[�V�����Q���L���łȂ��ꍇ1.0f(�Đ����̃��[�V�����P���P�O�O���̏��)�ɂ���
	animBlendRate_ = playAnim2_ == -1 ? 1.0f : 0.0f;
}

// �v���C���[�̃A�j���[�V��������
void Player::AnimProcess(void)
{
	if (animBlendRate_ < 1.0f) 
	{
		animBlendRate_ += PLAYER_ANIM_BLEND_SPEED;
		if (animBlendRate_ > 1.0f)
		{
			animBlendRate_ = 1.0f;
		}
	}

	if (playAnim1_ != -1)
	{
		PlayingAnim(playAnim1_);
		//�A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(modelHandle_, playAnim1_, animBlendRate_);
	}
	if (playAnim2_ != -1)
	{
		PlayingAnim(playAnim2_);
		//�A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(modelHandle_, playAnim2_, 1.0f - animBlendRate_);
	}
}

void Player::PlayShadowRender(void)
{

	int i;
	MV1_COLL_RESULT_POLY_DIM hitResDim_;
	MV1_COLL_RESULT_POLY* hitRes_;
	VERTEX3D vertex_[3];
	VECTOR slideVec_;

	// ���C�e�B���O�𖳌�������
	SetUseLighting(FALSE);

	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �e�N�X�`���A�h���X���[�h���N�����v�ɂ���i�e�N�X�`���̒[�̓h�b�g�����X�����j
	SetTextureAddressMode(DX_TEXADDRESS_CLAMP);

	// �v���C���[�̒����ɑ��݂���n�ʂ̃|���S���̎擾
	hitResDim_ = MV1CollCheck_Capsule(scene_->stage_->modelHandle_, -1, pos_, VAdd(pos_, 
										VGet(0.0f, -PLAYER_SHADOW_HEIGHT, 0.0f)),
										PLAYER_SHADOW_SIZE);

	// ���_�f�[�^�ŕω����Ȃ��������Z�b�g
	vertex_[0].dif = GetColorU8(255, 255, 255, 255);
	vertex_[0].spc = GetColorU8(0, 0, 0, 0);
	vertex_[0].su = 0.0f;
	vertex_[0].sv = 0.0f;
	vertex_[1] = vertex_[0];
	vertex_[2] = vertex_[0];

	// ���̒����ɑ��݂���|���S���̐������J��Ԃ�
	hitRes_ = hitResDim_.Dim;
	for (i = 0; i < hitResDim_.HitNum; i++, hitRes_)
	{
		// �|���S���̍��W�͒n�ʃ|���S���̍��W
		vertex_[0].pos = hitRes_->Position[0];
		vertex_[1].pos = hitRes_->Position[1];
		vertex_[2].pos = hitRes_->Position[2];

		// ���������グ�ďd�Ȃ�Ȃ��悤��
		slideVec_ = VScale(hitRes_->Normal, 0.5f);
		vertex_[0].pos = VAdd(vertex_[0].pos, slideVec_);
		vertex_[1].pos = VAdd(vertex_[1].pos, slideVec_);		

		vertex_[2].pos = VAdd(vertex_[2].pos, slideVec_);

		// �|���S���̕s�����x��ݒ肷��
		vertex_[0].dif.a = 0;
		vertex_[1].dif.a = 0;
		vertex_[2].dif.a = 0;
		if(hitRes_->Position[0].y>pos_.y-PLAYER_SHADOW_HEIGHT)
		{
			vertex_[0].dif.a = 128 * (1.0f - fabs(hitRes_->Position[0].y - pos_.y) / PLAYER_SHADOW_HEIGHT);
		}
		if (hitRes_->Position[1].y > pos_.y - PLAYER_SHADOW_HEIGHT)
		{
			vertex_[1].dif.a = 128 * (1.0f - fabs(hitRes_->Position[0].y - pos_.y) / PLAYER_SHADOW_HEIGHT);
		}
		if (hitRes_->Position[2].y > pos_.y - PLAYER_SHADOW_HEIGHT)
		{
			vertex_[2].dif.a = 128 * (1.0f - fabs(hitRes_->Position[0].y - pos_.y) / PLAYER_SHADOW_HEIGHT);
		}

		// UV�l�͒n�ʃ|���S���ƃv���C���[�̑��΍��W���犄��o����
		vertex_[0].v = (hitRes_->Position[0].x - pos_.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		vertex_[0].v = (hitRes_->Position[0].z - pos_.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		vertex_[1].v = (hitRes_->Position[1].x - pos_.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		vertex_[1].v = (hitRes_->Position[1].z - pos_.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		vertex_[2].v = (hitRes_->Position[2].x - pos_.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
		vertex_[2].v = (hitRes_->Position[2].z - pos_.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;

		// �e�|���S���`��
		DrawPolygon3D(vertex_, 1, shadowHandle_, TRUE);
	}
	// ���o�����n�ʃ|���S�����̌�n��
	MV1CollResultPolyDimTerminate(hitResDim_);

	// ���C�e�B���O��L���ɂ��� 
	SetUseLighting(TRUE);

	// Z�o�b�t�@�𖳌��ɂ���
	SetUseZBuffer3D(FALSE);
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

	
	VECTOR cameraEye_ = scene_->camera_->GetEye();
	VECTOR cameraTarget_ = scene_->camera_->GetTargetPos();
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
	if (CheckHitKey(KEY_INPUT_LSHIFT)==0)
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

		// ������{�^�������͂��ꂽ��J�����̌��Ă���ق��Ɉړ�
		if(CheckHitKey(KEY_INPUT_UP))
		{
			// �ړ��x�N�g���ɏオ���͂��ꂽ�J�����̌��Ă�������Ɉړ�����
			moveVec_ = VAdd(moveVec_, advanceMoveVec_);
			
			// �ړ��������ǂ����̃t���O
			moveFlag_ = true;

		}
		else if (CheckHitKey(KEY_INPUT_DOWN))
		{
			// �ړ��x�N�g���ɉ������͂��ꂽ�J�����̌��Ă�������Ɉړ�����
			moveVec_ = VAdd(moveVec_, VScale(advanceMoveVec_, -1.0f));

			// �ړ��������ǂ����̃t���O
			moveFlag_ = true;
		}

		// �W�����v��Ԃł͂Ȃ��X�y�[�X�������ꂽ�ꍇ
		if (state_ != ActionState::JUMP && CheckHitKey(KEY_INPUT_SPACE))
		{
			// �W�����v�ɂ���
			state_ = ActionState::JUMP;

			// Y�������ɑ��x���Z�b�g����
			jumpPower_ = PLAYER_JUMP_POWER;

			// �W�����v�A�j���[�V�����̍Đ�
			anim_ = AnimAction::JUMP;
			PlayAnim((int)anim_);

		}

		//if (CheckHitKey(KEY_INPUT_LEFT))
		//{
		//	// �ړ������������ꂽ���̈ړ��x�N�g���̉��Z
		//	moveVec_ = VAdd(moveVec_, leftMoveVec_);
		//
		//	// �ړ��������ǂ����̃t���O
		//	moveFlag_ = true;
		//
		//}
		//else if (CheckHitKey(KEY_INPUT_RIGHT)) {
		//	// �ړ������������ꂽ���̈ړ��x�N�g���̉��Z
		//	moveVec_ = VAdd(moveVec_, VScale(leftMoveVec_, -1.0f));
		//
		//	// �ړ��������ǂ����̃t���O
		//	moveFlag_ = true;
		//}


	}


}

void Player::StopMove(void)
{
	// �ړ��{�^���������ꂽ���ǂ����ŏ����𕪊�
	if (moveFlag_)
	{
		// �ړ��x�N�g���𐳋K���������̂��v���C���[�������ׂ������Ƃ��ĕۑ�
		moveDir_ = VNorm(moveVec_);

		// �v���C���[�������ׂ������x�N�g�����v���C���[�̃X�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
		moveVec_ = VScale(moveDir_, PLAYER_MOVE_SPEED);

		// �����~�܂肩��n�߂���
		if (state_==ActionState::STAY)
		{
			// ����ɕύX
			anim_ = AnimAction::RUN;
			PlayAnim((int)anim_);
		}
	}
	else
	{
		if(state_==ActionState::RUN)
		{
			// �����A�j���[�V����
			anim_ = AnimAction::STAY;
			PlayAnim((int)AnimAction::STAY);

			// ��Ԃ�STAY�ɂ���
			state_ = ActionState::STAY;
		}
	}
}

// �Đ����Ă���A�j���[�V�����P�̏���
void Player::PlayingAnim(int playAnimNo)
{
	// �A�j���[�V�������Đ����Ԃ��擾
	animTotalTime_ = MV1GetAttachAnimTotalTime(modelHandle_, playAnimNo);

	// �Đ����Ԃ�i�߂�
	animPlayCount1_ += PLAYER_PLAY_ANIM_SPEED;

	// �Đ����Ԃ��������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
	if (animPlayCount1_ > animTotalTime_)
	{
		animPlayCount1_ = fmod(animPlayCount1_, animTotalTime_);
	}

	// �ύX�����Đ����Ԃ����f���ɔ��f������
	MV1SetAttachAnimTime(modelHandle_, playAnimNo, animPlayCount1_);

	
}
