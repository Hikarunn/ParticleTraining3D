#pragma once


	enum class EffectNum {
		effect_Sphere_,
		effectNum_
	};



	
	


static constexpr int MAXNUM = 256;

class Effect
{
public:

	// �G�t�F�N�g�̊�{���
	struct EffectBaseInfo
	{
		// �G�t�F�N�g���g�p����O���t�B�b�N�n���h��
		int graphHandle_;
	};

	// �G�t�F�N�g�̏��
	struct EffectInfo
	{
		// �\���̂��g�p���Ă��邩�ǂ����̃t���O
		bool useFlag_;

		// �G�t�F�N�g�̏I�������N�G�X�g����Ă��邩�ǂ����̃t���O
		bool endRequest;

		// �G�t�F�N�g�̖{��
		EffectNum effect_;

		// �G�t�F�N�g�̊�{�\����
		EffectBaseInfo* baseInfo;

		// �G�t�F�N�g�ʂ̃f�[�^���i�[���Ă��郁�����̈�̃A�h���X
		void* subData;
	};


	// �G�t�F�N�g�̏�����
	bool Init(void);
	// �G�t�F�N�g�̍쐬
	EffectInfo Create(Effect effect);

	// �S�G�t�F�N�g�̕`��
	void RenderAll(void);

	// �G�t�F�N�g�̏I�����N�G�X�g
	void EffectEndRequest(EffectInfo* effectInfo);

	// �G�t�F�N�g�����̌�n��
	void Terminalize(void);

	// �G�t�F�N�g�̍폜
	void Delete(EffectInfo *effectInfo);

	// �S�G�t�F�N�g�̍폜
	void DeleteAll(void);

	// �S�G�t�F�N�g�̏�ԑJ��
	void StepAll(float stepTime);

private:
	

	// �G�t�F�N�g�ʂ̏����𕪂��邽�߂̃R�[���o�b�N�֐��e�[�u��
	struct EffectFunction
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

	struct EffectFunction effectFunctionTable_[(int)EffectNum::effectNum_] =
	{

	};


	
};

