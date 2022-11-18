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


	// �p�x
	float angleH_;		// ����
	float angleV_;		// ����

	float notHitLength_;
	float hitLength;
	float testLength;
	VECTOR testPos_;

	// ���W
	VECTOR eye_;		// �J����
	VECTOR target_;		// �����_

	//Player* player_;
	//Stage* stage_;



};

