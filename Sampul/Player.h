#pragma once

static constexpr float PLAYER_PLAY_ANIM_SPEED = 250.0f;
static constexpr float PLAYER_MOVE_SPEED = 30.0f;
static constexpr float PLAYER_ANIM_BLEND_SPEED = 0.1f;
static constexpr float PLAYER_ANGLE_SPEED = 0.2f;
static constexpr float PLAYER_JUMP_POWER = 100.0f;
static constexpr float PLAYER_FALL_UP_POWER = 20.0f;
static constexpr float PLAYER_GRAVITY = 0.25f;
static constexpr float PLAYER_ENUM_DEFAULT_SIZE = 800.0f;
static constexpr float PLAYER_HIT_WIDTH = 200.0f;
static constexpr float PLAYER_HIT_HEIGHT = 700.0f;
static constexpr float PLAYER_HIT_SLIDE_LENGTH = 5.0f;
static constexpr float PLAYER_SHADOW_SIZE = 200.0f;
static constexpr float PLAYER_SHADOW_HEIGHT = 700.0f;
static constexpr float MAX_JUMP_POW = 8.0f;
static constexpr int PLAYER_MAX_HITCOLL = 2048;
static constexpr int PLAYER_HIT_TRYNUM = 16;

enum class AnimAction {
	STAY,			//待機
	WALK,			//歩き
	RUN,			//走り
	JUMP,			//ジャンプ
	ATTACK			//攻撃
};


class Player
{
public:
	void Init(void);
	void Terminate(void);
	void Process(void);
	void Move(VECTOR moveVector);
	void AnglePlocess(void);
	void PlayAnim(int playAnim);
	void AnimProcess(void);
	void PlayShadowRender(void);
	void Jump(void);
	void SetJumpPow(float jumpPow);
	void AddGravity(void);

private:
	AnimAction anim_;	//　状態

	VECTOR pos_;	//　座標
	VECTOR moveDir_;	//　モデルの向くべき方向
	float angle_;	//　モデルの向いている方向
	float jumpPower_; // ジャンプ力
	int modelHandle_; //モデルのハンドル
	int shadowHandle_; //影のハンドル
	int animTime_;		//アニメーション時間
	int animCont;		//アニメーション用のカウンタ
	

	bool isJump_ = false;	// ジャンプフラグ
	//float playAnim_;
	

};

