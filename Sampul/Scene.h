#pragma once


class Stage;
class Player;
class Camera;

class Scene
{

public:

	void Init(void);
	void Update(void);
	void Draw(void);
	void Deleat(void);

	Stage* stage_;
	Player* player_;
	Camera* camera_;
private:



};

