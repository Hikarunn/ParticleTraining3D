#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <stack>
#include "DxLib.h"
#include "Stage.h"
#include "Player.h"
#include "Camera.h"
#include "Scene.h"

void Scene::Init(void)
{
	stage_ = new Stage(this);
	stage_->Init();

	player_ = new Player(this);
	player_->Init();

	camera_ = new Camera(this);
	camera_->Init();

}

void Scene::Update(void)
{
	stage_->Update();
	player_->Process();
	camera_->Process();

	Draw();
}

void Scene::Draw(void)
{
	stage_->Draw();
	player_->Draw();
	//camera_->Draw();
}

void Scene::Deleat(void)
{

}
