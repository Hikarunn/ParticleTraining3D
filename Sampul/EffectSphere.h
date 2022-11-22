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


//// ���̋O�Ղ��`��������W�̏��
//struct EffectSpherePos
//{
//	// ���̒��S���W
//	VECTOR ceterPos;
//	 
//	// ���̌��������肷�邽�߂̍��W
//	VECTOR directPos;
//
//	// �s�����x
//	float alpha;
//};
//
//// ���̋O�ՃG�t�F�N�g�̏��
//struct EffectSphereInfo
//{
//	// �G�t�F�N�g�̐F
//	COLOR_U8 color;
//	
//	// ���̑傫��
//	float sphereSize;
//	
//	// ���̋O�Ղ��`������L���ȍ��W�̐�
//	int posNum;
//	
//	// ���̋O�Ղ��`��������W�̏��
//	EffectSpherePos pos[ POSNUM ];
//
//};
//


class EffectSphere:public EffectBase
{
public:
	// ���̋O�ՃG�t�F�N�g�̊�{��񏉊��֐� 
	//bool EffectSphreInit(Effect::EffectBaseInfo* effectInfo);
	bool Init(Effect::EffectBaseInfo);

	// �G�t�F�N�g�̊�{����n��
	//void EffectSphereTerminate(Effect::EffectBaseInfo* effectInfo);
	
	// ���̋O�ՃG�t�F�N�g���쐬���ꂽ�ۂɌĂ΂��֐�
	//bool EffectSphereCreate(Effect::EffectInfo* effectInfo);

	// �폜���ɌĂ΂��֐�
	//void EffectSphereDelete(Effect::EffectInfo* effectInfo);

	// ���̋O�ՃG�t�F�N�g�̏�ԑJ�ڏ����֐�
	//void EffectSphereStep(Effect::EffectInfo* effectInfo,float stepTime);
	
	// ���̋O�ՃG�t�F�N�g�̕`�揈���֐�
	//void EffectSphereRender(Effect::EffectInfo* effectInfo);
	
	// ���̋O�ՃG�t�F�N�g�����̏���������֐�
	// Color �G�t�F�N�g�̐F
	//void EffectSphereSetup(Effect::EffectInfo* effectInfo, COLOR_U8 color, int modelHandle);
	
	// ���̋O�ՂɎg�p������W��ǉ�����
	// newCenterPos ���̒��S���W
	// newOirectionPos ���̌��������肷�邽�߂̍��W
	//void EffectSphereAddPos(Effect::EffectInfo* effectInfo, VECTOR newCenterPos, VECTOR newOirectionPos);

};

