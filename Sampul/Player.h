#pragma once
#include <math.h>
class Player
{
public:
	void Init(void);
	void Terminate(void);
	void Process(void);
	void Move(VECTOR MoveVector);
	void AnglePlocess(void);
	void PlayAnim(int PlayAnim);
	void AnimProcess(void);
	void PlayShadowRender(void);
};

