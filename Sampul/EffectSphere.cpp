#include <math.h>
#include <DxLib.h>

#include "Effect.h"
#include "EffectSphere.h"

// エフェクトポリゴン一つの情報
typedef struct EffectSpherePolygonInfo
{
	// ポリゴン面積
	float areaSize_;

	// ポリゴン頂点０から１へのベクトル
	VECTOR vec1_;

	// ポリゴン頂点０から２へのベクトル
	VECTOR vec2_;

	// ポリゴン頂点０の頂点
	VECTOR pos_;



};

// えっふぇくとのパーティクル一つの情報
typedef struct EffectSphereParticleInfo
{
	// 座標
	VECTOR pos_;

	// 上昇待ち時間
	float upWait_;

	// 上昇最大速度
	float upMaxSpeed_;

	// 上昇速度
	float upSpeed_;

	// 角度
	float abgle_;

	// 角速度
	float angleSpeed_;

	// パーティクル座標からの最大水平距離
	float distanceMax_;

	// パーティクル座標からの水平距離
	float distance_;

	// 表示時間
	float visibleTime_;

	// 不透明度
	float alpha_;

	// 大きさ
	float size_;

	// 大きさ率
	float sizeRate_;
};

// エフェクトの情報
typedef struct EffectSphereInfo
{
	// エフェクトの色
	COLOR_U8 color;

	// パーティクルの数
	int particleNum;

	// パーティクルの情報を格納しているメモリ領域のアドレス
	EffectSphereParticleInfo* partiicle_;
};

static int polygonInfoBufferSize;
static EffectSpherePolygonInfo* polygonInfoBuffer;


bool EffectSphere::EffectSphreInit(Effect::EffectBaseInfo* effectInfo)
{
	// エフェクト用の画像読み込み
	effectInfo->graphHandle_ = LoadGraph(L"image/Particle01.png");

	//　読み込み失敗で終了

	if (effectInfo->graphHandle_ < 0) {
		return false;
	}
	
	// 成功
	return true;

}

void EffectSphere::EffectSphereTerminate(Effect::EffectBaseInfo* effectInfo)
{

	// ポリゴン情報格納用に確保したメモリ領域を解放する
	if (polygonInfoBuffer != NULL)
	{
		free(polygonInfoBuffer);
		polygonInfoBuffer = NULL;
	}
}

bool EffectSphere::EffectSphereCreate(Effect::EffectInfo* effectInfo)
{
	EffectSphereInfo* info_;

	// エフェクトの情報構造体を格納するメモリ領域確保
	effectInfo->subData = malloc(sizeof(EffectSphereInfo));
	if (effectInfo->subData == NULL)
	{
		return false;
	}

	info_ = (EffectSphereInfo*)effectInfo->subData;

	// パーティクルの情報を格納するメモリの領域のアドレスを保存する変数を初期化する
	info_->partiicle_ = NULL;

	// 正常終了
	return true;
}

void EffectSphere::EffectSphereDelete(Effect::EffectInfo* effectInfo)
{
	EffectSphereInfo* info_ = (EffectSphereInfo*)effectInfo->subData;

	//パーティクルの情報を格納していたメモリ領域を解放
	if (info_->partiicle_ != NULL) {
		free(info_->partiicle_);
		info_->partiicle_ = NULL;
	}
}

void EffectSphere::EffectSphereStep(Effect::EffectInfo* effectInfo, float stepTime)
{
	EffectSphereInfo* info_ = (EffectSphereInfo*)effectInfo->subData;
	EffectSphereParticleInfo* particleInfo_;
	int num_;
	int validNum_;

	// 有効なパーティクルの数を初期化
	validNum_;

	// パーティクルの数だけ繰り返し
	particleInfo_ = info_->partiicle_;
	for (num_ = 0; num_ < info_->particleNum; num_++, particleInfo_++)
	{
		// 不透明度が０以下の場合は次のループへ
		if (particleInfo_->alpha_ <= 0.0f)
		{
			continue;
		}

		// 有効なパーティクルの数を増やす
		validNum_++;

		// 大きさが1.0f未満の場合は大きさ率をあげる
		if (particleInfo_->sizeRate_< 0.99999f)
		{
			particleInfo_->sizeRate_ += stepTime * SIZERATE_SPEED;
			if (particleInfo_->sizeRate_ > 1.0f)
			{
				particleInfo_->sizeRate_ = 1.0f;
			}
		}
		else
		{
			// 角度を変更
			particleInfo_->angleSpeed_ += stepTime * particleInfo_->angleSpeed_;

			// 表示時間が０より大きいかで分岐
			if (particleInfo_->visibleTime_ > 0.0f)
			{
				// 表示時間が０より大きい場合表示時間を減らす
				particleInfo_->visibleTime_ -= stepTime;
			}
			else
			{
				// 表示時間が０以下だったら不透明度を減らす
				particleInfo_->alpha_ -= stepTime * ALPHA_DOWN_SPEED;
			}
			// 上昇待ち時間が０より大きいかで分岐
			if (particleInfo_->upWait_ > 0.0f)
			{
				// 上昇待ち時間が０より大きかったら上昇待ち時間を減らす
				particleInfo_->upWait_ -= stepTime;
			}
			else
			{
				// 上昇待ち時間が０の場合

				// 上昇速度を上げる
				if (particleInfo_->upSpeed_ < particleInfo_->upMaxSpeed_)
				{
					particleInfo_->upSpeed_ += stepTime * UPACCEL;
					if (particleInfo_->upSpeed_ > particleInfo_->upMaxSpeed_)
					{
						particleInfo_->upSpeed_ = particleInfo_->upMaxSpeed_;
					}

				}

				// パーティクルを上昇させる
				particleInfo_->pos_.y += particleInfo_->upSpeed_ * stepTime;

				// パーティクル座標からの水平方向距離
				if (particleInfo_->distance_ < particleInfo_->distanceMax_)
				{
					particleInfo_->distance_ += stepTime * H_DISTANCE_SPEED;
					if (particleInfo_->distance_ > particleInfo_->distanceMax_)
					{
						particleInfo_->distance_ = particleInfo_->distanceMax_;
					}
				}

			}
		}
	}
	// 終了リクエストがされ有効なパーティクル数も０だったらエフェクトを削除する
	if (effectInfo->endRequest || validNum_ == 0)
	{
		//Effect::Delete(effectInfo);

		// すでに構造体が使用されていなかった場合何もせず終了
		if (effectInfo->useFlag_)
		{
			return;
		}
		//// 削除時に実行する関数が存在する場合はメモリを解放
		//if(effectFunc)
	}


}


void EffectSphere::EffectSphereRender(Effect::EffectInfo* effectInfo)
{

}

void EffectSphere::EffectSphereSetup(Effect::EffectInfo* effectInfo, COLOR_U8 color, int modelHandle)
{
}
