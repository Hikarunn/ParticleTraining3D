#pragma once
#include "EffectBase.h"

// 
static constexpr float CREATE_RATE = 0.025f;

// 
static constexpr float MAX_UPWAIT = 1.0f;
static constexpr float MIN_UPWAIT = 0.01f;

// 
static constexpr float MAX_UPWAIT = 1.0f;

// 
static constexpr float MAX_UPSPEED = 400.0f;
static constexpr float MIN_UPSPEED = 100.0f;

// 
static constexpr float UPACCEL = 500.0f;

// 
static constexpr float MAX_ANGLESPEED = 6.0f;
static constexpr float MIN_ANGLESPEED = 1.5f;

// 
static constexpr float MAX_H_DISTANCE = 100.0f;
static constexpr float MIN_H_DISTANCE = 20.0f;

// 
static constexpr float H_DISTANCE_SPEED = 200.0f;

// 
static constexpr float MAX_VISIBLETIME = 0.5f;
static constexpr float MAX_VISIBLETIME = 0.2f;

// 
static constexpr float ALPHA_UP_SPEED = 16.0f;
static constexpr float ALPHA_DOWN_SPEED = 4.0f;

// 
static constexpr float MAX_SIZE = 16.0f;
static constexpr float MAX_SIZE = 4.0f;

// 
static constexpr float SIZERATE_SPEED = 3.0f;


static constexpr int ADD_PARTICLE_NUM = 10;


//// 球の軌跡を形成する座標の情報
//struct EffectSpherePos
//{
//	// 球の中心座標
//	VECTOR ceterPos;
//	 
//	// 球の向きを決定するための座標
//	VECTOR directPos;
//
//	// 不透明度
//	float alpha;
//};
//
//// 球の軌跡エフェクトの情報
//struct EffectSphereInfo
//{
//	// エフェクトの色
//	COLOR_U8 color;
//	
//	// 球の大きさ
//	float sphereSize;
//	
//	// 球の軌跡を形成する有効な座標の数
//	int posNum;
//	
//	// 球の軌跡を形成する座標の情報
//	EffectSpherePos pos[ POSNUM ];
//
//};
//


class EffectSphere:public EffectBase
{
public:
	// 球の軌跡エフェクトの基本情報初期関数 
	//bool EffectSphreInit(Effect::EffectBaseInfo* effectInfo);
	bool Init(Effect::EffectBaseInfo);

	// エフェクトの基本情報後始末
	//void EffectSphereTerminate(Effect::EffectBaseInfo* effectInfo);
	
	// 球の軌跡エフェクトが作成された際に呼ばれる関数
	//bool EffectSphereCreate(Effect::EffectInfo* effectInfo);

	// 削除時に呼ばれる関数
	//void EffectSphereDelete(Effect::EffectInfo* effectInfo);

	// 球の軌跡エフェクトの状態遷移処理関数
	//void EffectSphereStep(Effect::EffectInfo* effectInfo,float stepTime);
	
	// 球の軌跡エフェクトの描画処理関数
	//void EffectSphereRender(Effect::EffectInfo* effectInfo);
	
	// 球の軌跡エフェクト処理の準備をする関数
	// Color エフェクトの色
	//void EffectSphereSetup(Effect::EffectInfo* effectInfo, COLOR_U8 color, int modelHandle);
	
	// 級の軌跡に使用する座標を追加する
	// newCenterPos 球の中心座標
	// newOirectionPos 球の向きを決定するための座標
	//void EffectSphereAddPos(Effect::EffectInfo* effectInfo, VECTOR newCenterPos, VECTOR newOirectionPos);

};

