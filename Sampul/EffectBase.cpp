#include <DxLib.h>
#include <math.h>
#include "Effect.h"
#include "EffectBase.h"

EffectBase::EffectBase(Effect* _effect)
{
	effect_ = _effect;
}

EffectBase::~EffectBase()
{
}

bool EffectBase::Init(Effect::EffectBaseInfo* _baseInfo)
{
	return false;
}

void EffectBase::Terminate(Effect::EffectBaseInfo* _baseInfo)
{
}

bool EffectBase::Create(Effect::EffectInfo* _effectInfo)
{
	return false;
}

void EffectBase::Delete(Effect::EffectInfo* _effectInfo)
{
}

void EffectBase::Step(Effect::EffectInfo* _effectInfo, float stepTime)
{
}

void EffectBase::Render(Effect::EffectInfo* _effectInfo)
{
}

void EffectBase::Setup(Effect::EffectInfo* _effectInfo, COLOR_U8 color, int modelHandle)
{
}

Effect* EffectBase::GetEffect(void)
{
	return effect_;
}
