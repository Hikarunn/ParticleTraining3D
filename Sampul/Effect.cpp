#include <math.h>
#include <DxLib.h>
#include "EffectCommon.h"
#include "EffectSphere.h"
#include "Effect.h"






bool Effect::Init(void)
{
	return false;
}

Effect::EffectInfo Effect::Create(Effect effect)
{
	return EffectInfo();
}

void Effect::RenderAll(void)
{
}

void Effect::EffectEndRequest(EffectInfo* effectInfo)
{
}

void Effect::Terminalize(void)
{
}

void Effect::Delete(EffectInfo* effectInfo)
{
	// すでに構造体が使用されていなっかったら何もせずに終了
	if (effectInfo->useFlag_)
	{
		return;
	}

	// 削除時に実行する関数が存在する場合は実行する
	//if(EffectFunction)

	// エフェクト別の情報があった場合はメモリを開放する


	// 構造体を使用しているかのフラグ
}

void Effect::DeleteAll(void)
{

}

void Effect::StepAll(float stepTime)
{

}
