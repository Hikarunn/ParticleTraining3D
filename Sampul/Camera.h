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

	// �p�x
	float angleH_;		// ����
	float angleV_;		// ����

	// ���W
	VECTOR eye_;		// �J����
	VECTOR target_;		// �����_

};

