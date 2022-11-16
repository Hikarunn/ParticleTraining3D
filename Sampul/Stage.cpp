#include <DxLib.h>
#include "Stage.h"

void Stage::Init(void)
{
	modelHandle_ = MV1LoadModel("ColTestStage.mqo");

	MV1SetupCollInfo(modelHandle_, -1);
}

void Stage::Terminalize(void)
{
	MV1DeleteModel(modelHandle_);
}
