#include <DxLib.h>
#include <math.h>
#include "Player.h"

//初期化
void Player::Init(void)
{
	// 初期位置（座標）
	pos_ = VGet(0.0f, 0.0f, 0.0f);
	
	//回転地＝0
	angle_ = 0;

	//ジャンプ力初期化
	jumpPower_ = 0.0f;

	// モデルの読み込み
	modelHandle_ = MV1LoadModel("Model/Test.x");
	
	// 影の読み込み
	shadowHandle_ = LoadGraph("Model/Shadow.tga");
	
	// 初期状態でプレイヤーが向くべき方向（X方向）
	moveDir_ = VGet(1.0f, 0.0f, 0.0f);
	
	//プレイヤーの初期状態
	anim_ = AnimAction::STAY;

	// 初期アニメーションセット
	PlayAnim((int)anim_);

}

void Player::Terminate(void)
{
	// モデルの削除
	MV1DeleteModel(modelHandle_);

	// 影の削除
	DeleteGraph(shadowHandle_);
}

void Player::Process(void)
{
	VECTOR advanceMoveVec_;	// 前進を押したときのの移動方向
	VECTOR leftMoveVec_;	// 左を押したときのの移動方向


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
