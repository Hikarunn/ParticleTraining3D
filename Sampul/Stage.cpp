#include <DxLib.h>
#include "Stage.h"

Stage::Stage(Scene* scene)
{
	scene_ = scene;
	Init();
}

void Stage::Init(void)
{
	modelHandle_ = MV1LoadModel(L"Model/ColTestStage.mqo");
	
//	modelHandle_ = LoadGraph(L"Image/Flame01.png");

	MV1SetupCollInfo(modelHandle_, -1);
}

void Stage::Terminalize(void)
{
	MV1DeleteModel(modelHandle_);
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	MV1DrawModel(modelHandle_);

//	DrawGraph(0, 0, modelHandle_, true);
}
