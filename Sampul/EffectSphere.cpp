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
	int paticleNum;

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

void EffectSphere::EffectSphereStep(Effect::EffectInfo* effectInfo, float stepTime)
{
	EffectSphereInfo* info_ = (EffectSphereInfo*)effectInfo->subData;

	//パーティクルの情報を格納していたメモリ領域を解放
	if (info_->partiicle_ != NULL) {
		free(info_->partiicle_);
		info_->partiicle_ = NULL;
	}
}

void EffectSphere::EffectSphereRender(Effect::EffectInfo* effectInfo)
{
}

void EffectSphere::EffectSphereSetup(Effect::EffectInfo* effectInfo, COLOR_U8 color, int modelHandle)
{
}
