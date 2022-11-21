#include "DxLib.h"
#include "Mathematics.h"

void Mathematics::CatmullRom(VECTOR* pos0, VECTOR* pos1, VECTOR* pos2, VECTOR* pos3, float DestPosRate, VECTOR* DestPos)
{
	VECTOR v0;
	VECTOR v1;
	float  t2;
	float  t3;

	// Catmull-Rom ��Ԃ��g�p���āAPos1 �` Pos2 �̕�ԍ��W���Z�o����

	v0.x = (pos2->x - pos0->x) / 2.0f;
	v0.y = (pos2->y - pos0->y) / 2.0f;
	v0.z = (pos2->z - pos0->z) / 2.0f;

	v1.x = (pos3->x - pos1->x) / 2.0f;
	v1.y = (pos3->y - pos1->y) / 2.0f;
	v1.z = (pos3->z - pos1->z) / 2.0f;

	t2 = DestPosRate * DestPosRate;
	t3 = t2 * DestPosRate;

	DestPos->x = (2 * pos1->x - 2 * pos2->x + v0.x + v1.x) * t3 +
		(-3 * pos1->x + 3 * pos2->x - 2 * v0.x - v1.x) * t2 +
		v0.x * DestPosRate + pos1->x;

	DestPos->y = (2 * pos1->y - 2 * pos2->y + v0.y + v1.y) * t3 +
		(-3 * pos1->y + 3 * pos2->y - 2 * v0.y - v1.y) * t2 +
		v0.y * DestPosRate + pos1->y;

	DestPos->z = (2 * pos1->z - 2 * pos2->z + v0.z + v1.z) * t3 +
		(-3 * pos1->z + 3 * pos2->z - 2 * v0.z - v1.z) * t2 +
		v0.z * DestPosRate + pos1->z;
}

void Mathematics::GetCatmullRomPosList(VECTOR* inPos, int posNum, int divNum, VECTOR* destPos)
{
	VECTOR  SPos;
	VECTOR  EPos;
	VECTOR* Pos[4];
	VECTOR* dp;
	int     i;
	int     j;
	int     num;
	float   sm;

	// �O�Ԗڂ̍��W�̐���_�͂P�Ԗڂ̍��W����O�Ԗڂ̍��W�̕�����
	// �O�Ԗڂ̍��W����ړ��������W�Ƃ���
	SPos.x = inPos[0].x + (inPos[0].x - inPos[1].x) / 2.0f;
	SPos.y = inPos[0].y + (inPos[0].y - inPos[1].y) / 2.0f;
	SPos.z = inPos[0].z + (inPos[0].z - inPos[1].z) / 2.0f;

	// �Ō�̍��W�̐���_�͍Ō�̈�O�̍��W����Ō�̍��W�̕�����
	// �Ō�̍��W����ړ��������W�Ƃ���
	EPos.x = inPos[posNum - 1].x + (inPos[posNum - 1].x - inPos[posNum - 2].x) / 2.0f;
	EPos.y = inPos[posNum - 1].y + (inPos[posNum - 1].y - inPos[posNum - 2].y) / 2.0f;
	EPos.z = inPos[posNum - 1].z + (inPos[posNum - 1].z - inPos[posNum - 2].z) / 2.0f;

	// Catmull-Rom ��Ԃ��g�p���đS���W�Ԃ̕�ԍ��W���Z�o����
	dp = destPos;
	num = posNum - 1;
	sm = 1.0f / divNum;
	for (i = 0; i < num; i++)
	{
		VECTOR v0;
		VECTOR v1;
		float  t2;
		float  t3;
		float  t;
		VECTOR par1;
		VECTOR par2;

		Pos[0] = i - 1 < 0 ? &SPos : &inPos[i - 1];
		Pos[1] = &inPos[i];
		Pos[2] = &inPos[i + 1];
		Pos[3] = i + 2 >= posNum ? &EPos : &inPos[i + 2];

		v0.x = (Pos[2]->x - Pos[0]->x) / 2.0f;
		v0.y = (Pos[2]->y - Pos[0]->y) / 2.0f;
		v0.z = (Pos[2]->z - Pos[0]->z) / 2.0f;

		v1.x = (Pos[3]->x - Pos[1]->x) / 2.0f;
		v1.y = (Pos[3]->y - Pos[1]->y) / 2.0f;
		v1.z = (Pos[3]->z - Pos[1]->z) / 2.0f;

		par1.x = 2 * Pos[1]->x - 2 * Pos[2]->x + v0.x + v1.x;
		par1.y = 2 * Pos[1]->y - 2 * Pos[2]->y + v0.y + v1.y;
		par1.z = 2 * Pos[1]->z - 2 * Pos[2]->z + v0.z + v1.z;

		par2.x = -3 * Pos[1]->x + 3 * Pos[2]->x - 2 * v0.x - v1.x;
		par2.y = -3 * Pos[1]->y + 3 * Pos[2]->y - 2 * v0.y - v1.y;
		par2.z = -3 * Pos[1]->z + 3 * Pos[2]->z - 2 * v0.z - v1.z;

		t = 0.0f;
		for (j = 0; j < divNum; j++, dp++, t += sm)
		{
			t2 = t * t;
			t3 = t2 * t;
			dp->x = par1.x * t3 + par2.x * t2 + v0.x * t + Pos[1]->x;
			dp->y = par1.y * t3 + par2.y * t2 + v0.y * t + Pos[1]->y;
			dp->z = par1.z * t3 + par2.z * t2 + v0.z * t + Pos[1]->z;
		}
	}
	*dp = inPos[posNum - 1];
}

int Mathematics::GetCatmullRomPosNum(int posNum, int divNum)
{
	// �o�͍��W�̐��́w���W�Ԃ̐��x�~�w��̍��W�Ԃ̕�ԍ��W�̐��x�{�w�Ō�̍��W�x
	return (posNum - 1) * divNum + 1;
}

bool Mathematics::ParamChangeFloat(float* param, float targetParam, float stepTime, float speed)
{
	// �ϐ��̒l���ڕW�Ƃ���l��菬�������ǂ����ŏ����𕪊�
	if (*param < targetParam)
	{
		// �ڕW�̒l��菬�����ꍇ�͕ϐ��̒l�ɕω��l�����Z����
		*param += speed * stepTime;

		// �ڕW�̒l�ɒB���Ă��邩�ǂ����̔���
		if (*param >= targetParam)
		{
			// �B���Ă�����ϐ��ɖڕW�̒l�������� true ��Ԃ�
			*param = targetParam;
			return true;
		}
	}
	else
	{
		// �ڕW�̒l��菬�����ꍇ�͕ϐ��̒l����ω��l�����Z����
		*param -= speed * stepTime;

		// �ڕW�̒l�ɒB���Ă��邩�ǂ����̔���
		if (*param <= targetParam)
		{
			// �B���Ă�����ϐ��ɖڕW�̒l�������� true ��Ԃ�
			*param = targetParam;
			return true;
		}
	}

	// �����ɗ�����܂��ڕW�̒l�ɒB���Ă��Ȃ��Ƃ������ƂȂ̂� false ��Ԃ�
	return false;
}

bool Mathematics::ParamChangeAngle(float* param, float targetParam, float stepTime, float speed)
{
	float RelateAngle;

	// �ڕW�Ƃ���p�x�ƕϐ��̊p�x�Ƃ̍����Z�o
	RelateAngle = targetParam - *param;

	// �p�x�̍����P�W�O�x�ȏ�̏ꍇ�͊p�x�̍������߂�������t�]������
	if (RelateAngle < -DX_PI_F)
	{
		RelateAngle += DX_TWO_PI_F;
	}
	else
		if (RelateAngle > DX_PI_F)
		{
			RelateAngle -= DX_TWO_PI_F;
		}

	// �p�x�̍����O�ɋ߂Â���
	if (ParamChangeFloat(&RelateAngle, 0.0f, stepTime, speed))
	{
		// �p�x�̍����O�ɂȂ�����ڕW�Ƃ���p�x�ɂȂ�Ƃ������ƂȂ̂�
		// �ϐ��ɖڕW�̊p�x�������� true ��Ԃ�
		*param = targetParam;
		return true;
	}

	// �ڕW�̊p�x����p�x�̍������������̂�V�����p�x�Ƃ���
	*param = targetParam - RelateAngle;

	// �܂��ڕW�̊p�x�ɒB���Ă��Ȃ��̂� false ��Ԃ�
	return false;
}

float Mathematics::GetRandomFloat(float maxF, float minF)
{
	return GetRand(10000) * (maxF - minF) / 10000.0f + minF;
}

int Mathematics::GetRandomInt(int maxI, int minI)
{
	return GetRand(maxI - minI) + minI;
}

float Mathematics::GetRandomFloatStructure(MinMaxFloat* minMaxF)
{
	return GetRandomFloat(minMaxF->maxF_, minMaxF->minF_);
}

int Mathematics::GetRandomIntStructure(MinMaxInt* minMaxI)
{
	return GetRandomInt(minMaxI->maxI_, minMaxI->minI_);
}
