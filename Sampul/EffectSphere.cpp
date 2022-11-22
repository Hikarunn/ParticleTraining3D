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
	int particleNum;

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

void EffectSphere::EffectSphereDelete(Effect::EffectInfo* effectInfo)
{
	EffectSphereInfo* info_ = (EffectSphereInfo*)effectInfo->subData;

	//�p�[�e�B�N���̏����i�[���Ă����������̈�����
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

	// �L���ȃp�[�e�B�N���̐���������
	validNum_;

	// �p�[�e�B�N���̐������J��Ԃ�
	particleInfo_ = info_->partiicle_;
	for (num_ = 0; num_ < info_->particleNum; num_++, particleInfo_++)
	{
		// �s�����x���O�ȉ��̏ꍇ�͎��̃��[�v��
		if (particleInfo_->alpha_ <= 0.0f)
		{
			continue;
		}

		// �L���ȃp�[�e�B�N���̐��𑝂₷
		validNum_++;

		// �傫����1.0f�����̏ꍇ�͑傫������������
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
			// �p�x��ύX
			particleInfo_->angleSpeed_ += stepTime * particleInfo_->angleSpeed_;

			// �\�����Ԃ��O���傫�����ŕ���
			if (particleInfo_->visibleTime_ > 0.0f)
			{
				// �\�����Ԃ��O���傫���ꍇ�\�����Ԃ����炷
				particleInfo_->visibleTime_ -= stepTime;
			}
			else
			{
				// �\�����Ԃ��O�ȉ���������s�����x�����炷
				particleInfo_->alpha_ -= stepTime * ALPHA_DOWN_SPEED;
			}
			// �㏸�҂����Ԃ��O���傫�����ŕ���
			if (particleInfo_->upWait_ > 0.0f)
			{
				// �㏸�҂����Ԃ��O���傫��������㏸�҂����Ԃ����炷
				particleInfo_->upWait_ -= stepTime;
			}
			else
			{
				// �㏸�҂����Ԃ��O�̏ꍇ

				// �㏸���x���グ��
				if (particleInfo_->upSpeed_ < particleInfo_->upMaxSpeed_)
				{
					particleInfo_->upSpeed_ += stepTime * UPACCEL;
					if (particleInfo_->upSpeed_ > particleInfo_->upMaxSpeed_)
					{
						particleInfo_->upSpeed_ = particleInfo_->upMaxSpeed_;
					}

				}

				// �p�[�e�B�N�����㏸������
				particleInfo_->pos_.y += particleInfo_->upSpeed_ * stepTime;

				// �p�[�e�B�N�����W����̐�����������
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
	// �I�����N�G�X�g������L���ȃp�[�e�B�N�������O��������G�t�F�N�g���폜����
	if (effectInfo->endRequest || validNum_ == 0)
	{
		//Effect::Delete(effectInfo);

		// ���łɍ\���̂��g�p����Ă��Ȃ������ꍇ���������I��
		if (effectInfo->useFlag_)
		{
			return;
		}
		//// �폜���Ɏ��s����֐������݂���ꍇ�̓����������
		//if(effectFunc)
	}


}


void EffectSphere::EffectSphereRender(Effect::EffectInfo* effectInfo)
{

}

void EffectSphere::EffectSphereSetup(Effect::EffectInfo* effectInfo, COLOR_U8 color, int modelHandle)
{
}
