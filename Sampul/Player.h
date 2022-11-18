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
	T,				//Tポーズ
	STAY,			//待機
	RUN,			//走り
	JUMP,			//ジャンプ
	ATTACK			//攻撃
};
enum class ActionState {
	T,				//Tポーズ
	STAY,			//待機
	RUN,			//走り
	JUMP,			//ジャンプ
	ATTACK			//攻撃
};

class Scene;


class Player
{
public:
	Player(Scene* scene);
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
	void Draw(void);
	VECTOR GetPos(void);

	int modelHandle_; //モデルのハンドル
	int shadowHandle_; //影のハンドル


private:
	AnimAction anim_;	//　アニメーション状態
	ActionState state_;  //現在の状態

	Scene* scene_;
	

	//　ルートフレームのz軸方向の移動パラメータを無効化する
	void LootFlameCancel(void);

	// プレイヤーの移動方向のベクトルを算出
	void MoveVecOutput(void);

	// プレイヤーの移動制御
	void MovementControl(void);

	// 停止処理
	void StopMove(void);

	//アニメーションの再生
	void PlayingAnim(int playAnimNo1);



	VECTOR pos_;	//　座標
	VECTOR moveDir_;	//　モデルの向くべき方向
	
	VECTOR advanceMoveVec_;	// 前進を押したときのの移動方向
	VECTOR leftMoveVec_;	// 左を押したときのの移動方向
	VECTOR moveVec_;		// このフレームの移動ベクトル
	bool moveFlag_;			// 移動したかどうかのフラグ（true→移動した,false→移動していない)

	bool isJump_ = false;	// ジャンプフラグ

	float angle_;			//　モデルの向いている方向
	float jumpPower_;		// ジャンプ力
	float animTotalTime_;	// 再生しているアニメーションの総時間

	int animTime_;			// アニメーション時間
	int animCont;			// アニメーション用のカウンタ

	
	//float playAnim_;
	
	int	playAnim1_;				// 再生しているアニメーション１のアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float animPlayCount1_;			// 再生しているアニメーション１の再生時間
	int	playAnim2_;				// 再生しているアニメーション２のアタッチ番号( -1:何もアニメーションがアタッチされていない )
	float animPlayCount2_;			// 再生しているアニメーション２の再生時間
	float animBlendRate_;				// 再生しているアニメーション１と２のブレンド率

	
};

