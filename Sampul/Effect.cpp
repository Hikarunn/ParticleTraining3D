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
	// ���łɍ\���̂��g�p����Ă��Ȃ��������牽�������ɏI��
	if (effectInfo->useFlag_)
	{
		return;
	}

	// �폜���Ɏ��s����֐������݂���ꍇ�͎��s����
	//if(EffectFunction)

	// �G�t�F�N�g�ʂ̏�񂪂������ꍇ�̓��������J������


	// �\���̂��g�p���Ă��邩�̃t���O
}

void Effect::DeleteAll(void)
{

}

void Effect::StepAll(float stepTime)
{

}
