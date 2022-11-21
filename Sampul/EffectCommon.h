#pragma once
#include "Effect.h"


// エフェクト別の処理を分けるためのコールバック関数テーブル
typedef struct EffectFunction
{
	// 初期化時に呼ばれる関数へのポインタ
	bool (*Init)(EffectBaseInfo* baseInfo_);

	// 後始末時に呼ばれる関数へのポインタ
	void (*Terminate)(EffectBaseInfo* baseInfo_);

	// 作成時に呼ばれる関数へのポインタ
	bool (*Create)(EffectInfo* effectInfo_);

	// 削除時に呼ばれる関数へのポインタ
	void (*Delete)(EffectInfo* effectInfo_);

	// 状態遷移時に呼ばれる関数へのポインタ
	void (*Step)(EffectInfo* effectInfo_, float stepTime);

	// 描画時に呼ばれる関数へのポインタ
	void (*Render)(EffectInfo* effectInfo);

};

