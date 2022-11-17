#pragma once

class Stage;
class Player;

class Scene
{

public:
	void Init(void);
	void Update(void);
	void Draw(void);
	void Deleat(void);

	Stage* stage_;
	Player* player_;
private:


};

