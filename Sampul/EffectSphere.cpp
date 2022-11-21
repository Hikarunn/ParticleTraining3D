#include <math.h>
#include <DxLib.h>

#include "Effect.h"
#include "EffectSphere.h"

// �G�t�F�N�g�|���S����̏��
typedef struct EffectSpherePolygonInfo
{
	// �|���S���ʐ�
	float areaSize_;

	// �|���S�����_�O����P�ւ̃x�N�g��
	VECTOR vec1_;

	// �|���S�����_�O����Q�ւ̃x�N�g��
	VECTOR vec2_;

	// �|���S�����_�O�̒��_
	VECTOR pos_;



};

// �����ӂ����Ƃ̃p�[�e�B�N����̏��
typedef struct EffectSphereParticleInfo
{
	// ���W
	VECTOR pos_;

	// �㏸�҂�����
	float upWait_;

	// �㏸�ő呬�x
	float upMaxSpeed_;

	// �㏸���x
	float upSpeed_;

	// �p�x
	float abgle_;

	// �p���x
	float angleSpeed_;

	// �p�[�e�B�N�����W����̍ő吅������
	float distanceMax_;

	// �p�[�e�B�N�����W����̐�������
	float distance_;

	// �\������
	float visibleTime_;

	// �s�����x
	float alpha_;

	// �傫��
	float size_;

	// �傫����
	float sizeRate_;
};

// �G�t�F�N�g�̏��
typedef struct EffectSphereInfo
{
	// �G�t�F�N�g�̐F
	COLOR_U8 color;

	// �p�[�e�B�N���̐�
	int paticleNum;

	// �p�[�e�B�N���̏����i�[���Ă��郁�����̈�̃A�h���X
	EffectSphereParticleInfo* partiicle_;
};

static int polygonInfoBufferSize;
static EffectSpherePolygonInfo* polygonInfoBuffer;


bool EffectSphere::EffectSphreInit(Effect::EffectBaseInfo* effectInfo)
{
	// �G�t�F�N�g�p�̉摜�ǂݍ���
	effectInfo->graphHandle_ = LoadGraph(L"image/Particle01.png");

	//�@�ǂݍ��ݎ��s�ŏI��

	if (effectInfo->graphHandle_ < 0) {
		return false;
	}
	
	// ����
	return true;

}

void EffectSphere::EffectSphereTerminate(Effect::EffectBaseInfo* effectInfo)
{

	// �|���S�����i�[�p�Ɋm�ۂ����������̈���������
	if (polygonInfoBuffer != NULL)
	{
		free(polygonInfoBuffer);
		polygonInfoBuffer = NULL;
	}
}

bool EffectSphere::EffectSphereCreate(Effect::EffectInfo* effectInfo)
{
	EffectSphereInfo* info_;

	// �G�t�F�N�g�̏��\���̂��i�[���郁�����̈�m��
	effectInfo->subData = malloc(sizeof(EffectSphereInfo));
	if (effectInfo->subData == NULL)
	{
		return false;
	}

	info_ = (EffectSphereInfo*)effectInfo->subData;

	// �p�[�e�B�N���̏����i�[���郁�����̗̈�̃A�h���X��ۑ�����ϐ�������������
	info_->partiicle_ = NULL;

	// ����I��
	return true;
}

void EffectSphere::EffectSphereStep(Effect::EffectInfo* effectInfo, float stepTime)
{
	EffectSphereInfo* info_ = (EffectSphereInfo*)effectInfo->subData;

	//�p�[�e�B�N���̏����i�[���Ă����������̈�����
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
