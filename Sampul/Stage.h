#pragma once
class Scene;

class Stage
{
public:
	Stage(Scene* scene);
	void Init(void);
	void Terminalize(void);
	void Update(void);
	void Draw(void);
	int modelHandle_;
private:
	Scene* scene_;

	
};

