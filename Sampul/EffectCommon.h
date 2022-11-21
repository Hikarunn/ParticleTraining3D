#pragma once
#include "Effect.h"


// �G�t�F�N�g�ʂ̏����𕪂��邽�߂̃R�[���o�b�N�֐��e�[�u��
typedef struct EffectFunction
{
	// ���������ɌĂ΂��֐��ւ̃|�C���^
	bool (*Init)(EffectBaseInfo* baseInfo_);

	// ��n�����ɌĂ΂��֐��ւ̃|�C���^
	void (*Terminate)(EffectBaseInfo* baseInfo_);

	// �쐬���ɌĂ΂��֐��ւ̃|�C���^
	bool (*Create)(EffectInfo* effectInfo_);

	// �폜���ɌĂ΂��֐��ւ̃|�C���^
	void (*Delete)(EffectInfo* effectInfo_);

	// ��ԑJ�ڎ��ɌĂ΂��֐��ւ̃|�C���^
	void (*Step)(EffectInfo* effectInfo_, float stepTime);

	// �`�掞�ɌĂ΂��֐��ւ̃|�C���^
	void (*Render)(EffectInfo* effectInfo);

};

