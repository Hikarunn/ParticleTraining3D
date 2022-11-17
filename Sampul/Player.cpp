#include <DxLib.h>
#include <math.h>
#include "Camera.h"
#include "Stage.h"
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

	// アニメーション総再生時間
	animTotalTime_ = 0.0f;

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

// 新しいアニメーションを再生
void Player::PlayAnim(int PlayAnim)
{
	//再生中のモーションが有効だったらデタッチ
	if (playAnim2_ != -1) 
	{
		MV1DetachAnim(modelHandle_, playAnim2_);
		playAnim2_ = -1;
	}

	// 今まで再生中のモーション１だったものを２に移動
	playAnim2_ = playAnim1_;
	animPlayCount1_ = 0.0f;

	// ブレンド率は再生中のモーション２が有効でない場合1.0f(再生中のモーション１が１００％の状態)にする
	animBlendRate_ = playAnim2_ == -1 ? 1.0f : 0.0f;
}

// プレイヤーのアニメーション処理
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
		//アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(modelHandle_, playAnim1_, animBlendRate_);
	}
	if (playAnim2_ != -1)
	{
		PlayingAnim(playAnim2_);
		//アニメーション１のモデルに対する反映率をセット
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

	// ライティングを無効化する
	SetUseLighting(FALSE);

	// Zバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// テクスチャアドレスモードをクランプにする（テクスチャの端はドットが延々続く）
	SetTextureAddressMode(DX_TEXADDRESS_CLAMP);

	// プレイヤーの直下に存在する地面のポリゴンの取得
	hitResDim_ = MV1CollCheck_Capsule(stage_->modelHandle_, -1, pos_, VAdd(pos_, 
										VGet(0.0f, -PLAYER_SHADOW_HEIGHT, 0.0f)),
										PLAYER_SHADOW_SIZE);

	// 頂点データで変化がない部分をセット
	vertex_[0].dif = GetColorU8(255, 255, 255, 255);
	vertex_[0].spc = GetColorU8(0, 0, 0, 0);
	vertex_[0].su = 0.0f;
	vertex_[0].sv = 0.0f;
	vertex_[1] = vertex_[0];
	vertex_[2] = vertex_[0];

	// 級の直下に存在するポリゴンの数だけ繰り返し
	hitRes_ = hitResDim_.Dim;
	for (i = 0; i < hitResDim_.HitNum; i++, hitRes_)
	{
		// ポリゴンの座標は地面ポリゴンの座標
		vertex_[0].pos = hitRes_->Position[0];
		vertex_[1].pos = hitRes_->Position[1];
		vertex_[2].pos = hitRes_->Position[2];

		// 少し持ち上げて重ならないように
		slideVec_ = VScale(hitRes_->Normal, 0.5f);
		vertex_[0].pos = VAdd(vertex_[0].pos, slideVec_);
		vertex_[1].pos = VAdd(vertex_[1].pos, slideVec_);		
		vertex_[2].pos = VAdd(vertex_[2].pos, slideVec_);

		// ポリゴンの不透明度を設定する
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

	}


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

		// 上方向ボタンが入力されたらカメラの見ているほうに移動
		if(CheckHitKey(KEY_INPUT_UP))
		{
			// 移動ベクトルに上が入力されたカメラの見ている方向に移動する
			moveVec_ = VAdd(moveVec_, advanceMoveVec_);
			
			// 移動したかどうかのフラグ
			moveFlag_ = true;

		}
		else if (CheckHitKey(KEY_INPUT_DOWN))
		{
			// 移動ベクトルに下が入力されたカメラの見ている方向に移動する
			moveVec_ = VAdd(moveVec_, VScale(advanceMoveVec_, -1.0f));

			// 移動したかどうかのフラグ
			moveFlag_ = true;
		}

		// 移動ボタンが押されたかどうかで処理を分岐
		if (moveFlag_)
		{
			// 移動ベクトルを正規化したものをプレイヤーが向くべき方向として保存
			moveDir_ = VNorm(moveVec_);

			// プレイヤーが向くべき方向ベクトルをプレイヤーのスピード倍したものを移動ベクトルとする
			moveVec_ = VScale(moveDir_, PLAYER_MOVE_SPEED);

			// 立ち止まりから始めたら
			if (anim_ == AnimAction::STAY) 
			{

				PlayAnim((int)anim_);
			}
		}

		//if (CheckHitKey(KEY_INPUT_LEFT))
		//{
		//	// 移動方向が押された時の移動ベクトルの加算
		//	moveVec_ = VAdd(moveVec_, leftMoveVec_);

		//	// 移動したかどうかのフラグ
		//	moveFlag_ = true;

		//}
		//else if (CheckHitKey(KEY_INPUT_RIGHT)) {
		//	// 移動方向が押された時の移動ベクトルの加算
		//	moveVec_ = VAdd(moveVec_, VScale(leftMoveVec_, -1.0f));

		//	// 移動したかどうかのフラグ
		//	moveFlag_ = true;
		//}


	}
}

// 再生しているアニメーション１の処理
void Player::PlayingAnim(int playAnimNo)
{
	// アニメーション総再生時間を取得
	animTotalTime_ = MV1GetAttachAnimTotalTime(modelHandle_, playAnimNo);

	// 再生時間を進める
	animPlayCount1_ += PLAYER_PLAY_ANIM_SPEED;

	// 再生時間がそう時間に到達していたら再生時間をループさせる
	if (animPlayCount1_ > animTotalTime_)
	{
		animPlayCount1_ = fmod(animPlayCount1_, animTotalTime_);
	}

	// 変更した再生時間をモデルに反映させる
	MV1SetAttachAnimTime(modelHandle_, playAnimNo, animPlayCount1_);

	
}
