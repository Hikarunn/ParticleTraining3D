#include <DxLib.h>
#include <math.h>
#include "Camera.h"
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
	modelHandle_ = MV1LoadModel(L"Model/Test.x");
	
	// 影の読み込み
	shadowHandle_ = LoadGraph(L"Model/Shadow.tga");
	
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


	LootFlameCancel();

	MoveVecOutput();

	// このフレームでの移動ベクトルを初期化
	moveVec_ = VGet(0.0f, 0.0f, 0.0f);

	//移動したかどうかのフラグを初期化状態ではfalseにする
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

	// ユーザー行列を解除
	MV1ResetFrameUserLocalMatrix(modelHandle_, 2);

	// 現在のルートフレームの行列を取得
	LocalMatrix = MV1GetFrameLocalMatrix(modelHandle_, 2);

	// z軸方向の平行移動成分を無効にする
	LocalMatrix.m[3][2] = 0.0f;

	// ユーザー行列として平行移動成分を無効にした行列をルートフレームにセットする
	MV1SetFrameUserLocalMatrix(modelHandle_, 2, LocalMatrix);

}

/*VECTOR advanceMoveVec_;	// 前進を押したときのの移動方向
	VECTOR leftMoveVec_;	// 左を押したときのの移動方向
	VECTOR moveVec_;		// このフレームの移動ベクトル
	bool moveFlag_;			// 移動したかどうかのフラグ（true→移動した,false→移動していない)
*/

void Player::MoveVecOutput(void)
{

	VECTOR cameraTarget_ = camera_->GetTargetPos();
	VECTOR cameraEye_ = camera_->GetEye();
	// 上ボタンを押したときのプレイヤーの移動ベクトルはカメラ乃視線方向からY成分を抜いたもの
	advanceMoveVec_ = VSub(cameraTarget_, cameraEye_);

	advanceMoveVec_.y = 0.0f;

	// 左ボタンを押したときのプレイやの移動ベクトルは上を押したときの方向ベクトルとY軸のプラス方向のベクトルに垂直な方向
	leftMoveVec_ = VCross(advanceMoveVec_, VGet(0.0f, 1.0f, 0.0f));

	// 二つのベクトルを正規化
	advanceMoveVec_ = VNorm(advanceMoveVec_);
	leftMoveVec_ = VNorm(leftMoveVec_);
	
}

void Player::MovementControl(void)
{
	if (CheckHitKey(KEY_INPUT_LSHIFT))
	{
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			// 移動方向が押された時の移動ベクトルの加算
			moveVec_ = VAdd(moveVec_, leftMoveVec_);

			// 移動したかどうかのフラグ
			moveFlag_ = true;

		}
		else if(CheckHitKey(KEY_INPUT_RIGHT)) {
			// 移動方向が押された時の移動ベクトルの加算
			moveVec_ = VAdd(moveVec_, VScale(leftMoveVec_, -1.0f));

			// 移動したかどうかのフラグ
			moveFlag_ = true;
		}


	}
}
