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

	//カメラ水平角度
	angleH_ = DX_PI_F;

	//垂直角度0度
	angleV_ = 0.0f;
}

void Camera::Process(void)
{
	//カメラの回転
	if (CheckHitKey(KEY_INPUT_LSHIFT)) 
	{
		//左
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			angleH_ -= CAMERA_ANGLE_SPEED;
			if (angleH_ < -DX_PI_F)
			{
				angleH_ += DX_TWO_PI_F;
			}
		}

		//右
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			angleH_ += CAMERA_ANGLE_SPEED;
			if (angleH_ > DX_PI_F)
			{
				angleH_ -= DX_TWO_PI_F;
			}
		}

		//上
		if (CheckHitKey(KEY_INPUT_UP))
		{
			angleV_ -= CAMERA_ANGLE_SPEED;
			if (angleV_ < -DX_PI_F / 2.0f - 0.6f)
			{
				angleV_ = -DX_PI_F / 2.0f - 0.6f;
			}
		}

		//下
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
	
	// 水平方向の回転
	rotY_ = MGetRotY(angleH_);

	// 垂直方向
	rotZ_ = MGetRotZ(angleV_);

	// カメラからプレイヤーへの初期距離
	cameraPlayerLength = CAMERA_PLAYER_LENGTH;

	// カメラ座標
	eye_ = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotZ_), rotY_), target_);


	// 注視点からカメラの間にステージがあるか調べる

	CheckStage(rotZ_, rotY_, cameraPlayerLength);

	// カメラ情報を反映
	SetCameraPositionAndTarget_UpVecY(eye_, target_);
}

// 注視点からカメラの間にステージがあるか調べる
void Camera::CheckStage(MATRIX rotZ, MATRIX rotY, float cameraPlayerLength)
{
	MV1_COLL_RESULT_POLY_DIM res_{};
	int hitNum_;


	res_ = MV1CollCheck_Capsule(scene_->stage_->modelHandle_, -1, target_, eye_, CAMERA_COLLISION_SIZE);
	hitNum_ = res_.HitNum;
	MV1CollResultPolyDimTerminate(res_);
	if (hitNum_ != 0)
	{
		

		// ポリゴンに当たらない距離
		notHitLength_ = 0.0f;

		// ポリゴンに当たる距離
		hitLength = cameraPlayerLength;
		do
		{
			// 当たるかどうかのテスト距離のセット
			testLength = notHitLength_ + (hitLength - notHitLength_) / 2.0f;

			// テスト用カメラ座標を算出
			testPos_ = VAdd(VTransform(VTransform(VGet(-testLength, 0.0f, 0.0f), rotZ), rotY), target_);

			// 新しい座標で壁に当たるか
			res_ = MV1CollCheck_Capsule(scene_->stage_->modelHandle_, -1, target_, testPos_, CAMERA_COLLISION_SIZE);
			hitNum_ = res_.HitNum;
			MV1CollResultPolyDimTerminate(res_);

			if (hitNum_ != 0) {

				// 当たる距離をtestLengthに変更する
				hitLength = testLength;
			}
			else
			{
				// 当たらなかったらその距離をtestLengthに変更する
				notHitLength_ = testLength;
			}

			// hitLengthとnotHitLengthが十分に近づいていなかったらループ
		} while (hitLength - notHitLength_ > 0.1f);
		
		// カメラ座標セット
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
