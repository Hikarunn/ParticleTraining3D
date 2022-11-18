#pragma once

class Scene;


static constexpr float CAMERA_ANGLE_SPEED = 0.05f;
static constexpr float CAMERA_PLAYER_TARGET_HEIGHT = 400.0f;
static constexpr float CAMERA_PLAYER_LENGTH = 1600.0f;
static constexpr float CAMERA_COLLISION_SIZE = 50.0f;



class Camera
{
public:
	Camera(Scene* scene);
	void Init(void);

	void Process(void);

	void CameraPos(void);

	void CheckStage(MATRIX rotZ,MATRIX rotY, float cameraPlayerLength);

	VECTOR GetTargetPos(void);
	VECTOR GetEye(void);

private:
	Scene* scene_;


	// 角度
	float angleH_;		// 水平
	float angleV_;		// 垂直

	float notHitLength_;
	float hitLength;
	float testLength;
	VECTOR testPos_;

	// 座標
	VECTOR eye_;		// カメラ
	VECTOR target_;		// 注視点

	//Player* player_;
	//Stage* stage_;



};

