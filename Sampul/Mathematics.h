#pragma once


// �w��͈͂��烉���_���ɒl�����肷����i���������_�^�j
struct MinMaxFloat
{
	// �ő�l
	float maxF_;

	// �ŏ��l
	float minF_;
};
// �w��͈͂��烉���_���ɒl�����肷����i�����^�j
struct MinMaxInt
{
	// �ő�l
	int maxI_;

	// �ŏ��l
	int minI_;
};


class Mathematics
{

public:

	// Catmull-Rom ��Ԃ𗘗p���Ďw���4�_��Pos1�`Pos2���Ԃ�����W���擾����
	//pos0  ��ԂŎg�p������W�O�i����_�Ƃ��Ďg�p����j
	//pos1�@��ԂŎg�p������W�P
	//pos2�@��ԂŎg�p������W�Q
	//pos3�@��ԂŎg�p������W�R
	//DestPosRate�@�擾������W�̈ʒu
	//DestPos�@�v�Z���ʂ̍��W��������ϐ��̃A�h���X
	void CatmullRom(VECTOR* pos0, VECTOR* pos1, VECTOR* pos2, VECTOR* pos3, float DestPosRate, VECTOR* DestPos);



	// ���W�z��̊Ԃ� Catmull-Rom ���g�p���ĕ�Ԃ������W�z����擾����
	// inPos ��Ԃ��s�����W�z��̐擪�A�h���X
	// posNum  InPos �̍��W�̐�
	// divNum  ����W�Ԃ̕�ԍ��W�̐�
	// desPos ���ʂ̍��W���i�[������W�z��̐擪�A�h���X
	void GetCatmullRomPosList(VECTOR* inPos, int posNum, int divNum, VECTOR* destPos);

	// GetCatmullRomPosList �ɓn���uInPos �̍��W�̐��v�Ɓu����W�Ԃ̕�ԍ��W�̐��v����
	// ���ʂ��i�[������W�z��ɕK�v�ȗv�f�����擾����
	// �߂�l : ���ʂ��i�[������W�z��ɕK�v�ȗv�f��
	// posNum�@inPos�̍��W�̐�
	// divNum  ����W�Ԃ̕ۊǍ��W�̐�
	int GetCatmullRomPosNum(int posNum, int divNum);

	// ���������_�^�̕ϐ��̒l���w��̒l�ɋ߂Â���
	// �i�ڕW�Ƃ���Ӑ��ɑ������Ă���p�x�̍���2.0f���Έȓ��ł���K�v������
	// �߂�l�F�ϐ��̊p�x���w��̊p�x�ɒB������
	// param�@����Ώۂ̕ϐ��A�h���X	
	// targetParam�@�ڕW�Ƃ���p�x
	// stepTime�@���ڂ����鎞��
	// speed�@�p�x�̕ω����x
	bool ParamChangeFloat(float* param, float targetParam, float stepTime, float speed);

	// ���������_�^�̕ϐ��ɑ������Ă���p�x���w��̊p�x�ɋ߂Â��鏈�����s��
	// �i�ڕW�Ƃ���Ӑ��ɑ������Ă���p�x�̍���2.0f���Έȓ��ł���K�v������
	// �߂�l�F�ϐ��̊p�x���w��̊p�x�ɒB������
	// param�@����Ώۂ̕ϐ��A�h���X
	// targetParam�@�ڕW�Ƃ���p�x
	// stepTime�@���ڂ����鎞��
	// speed�@�p�x�̕ω����x
	bool ParamChangeAngle(float* param, float targetParam, float stepTime, float speed);

	// �w��͈̔͂��烉���_���Ō��肵���l���擾����i���������_�^�j
	float GetRandomFloat(float maxF, float minF);

	// �w��͈̔͂��烉���_���Ō��肵���l���擾����i�����^�j
	int GetRandomInt(int maxI, int minI);

	// �w��͈̔͂��烉���_���Ō��肵���l���擾����i���������_�^�j
	float GetRandomFloatStructure(MinMaxFloat* minMaxF/* �ő�l�ƍŏ��l�̏�񂪓������\���̂̃A�h���X*/);

	// �w��͈̔͂��烉���_���Ō��肵���l���擾����i�����^�j
	int GetRandomIntStructure(MinMaxInt* minMaxI/* �ő�l�ƍŏ��l�̏�񂪓������\���̂̃A�h���X*/);

};

