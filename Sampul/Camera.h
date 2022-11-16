#pragma once


static constexpr float CAMERA_ANGLE_SPEE = 0.05f;
static constexpr float CAMERA_PLAYER_TARGET_HEIGHT = 400.0f;
static constexpr float CAMERA_PLAYER_LENGTH = 1600.0f;
static constexpr float CAMERA_COLLISION_SIZE = 50.0f;



class Camera
{
public:
	void Init(void);

	void Process(void);

private:

	// 角度
	float angleH_;		// 水平
	float angleV_;		// 垂直

	// 座標
	VECTOR eye_;		// カメラ
	VECTOR target_;		// 注視点

};

