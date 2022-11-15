// パーティクル基本
#include "DxLib.h"

// ショットとパーティクルの最大数
#define MAX_SHOT	4
#define MAX_SPARK	1600

// ショットデータ型
typedef struct tagSHOT
{
	int Valid;	// このデータが使用中か、フラグ
	int shotPosX_, shotPosY_;	// ショットの位置
} SHOT;

// 火花データ型
typedef struct tagSPARK
{
	int Valid;	// このデータが使用中か、フラグ
	int X, Y;	// 火花の位置
	int Sx, Sy;	// 火花の移動力
	int G;		// 火花の重さ
	int Bright;	// 火花の明るさ
} SPARK;

int PlayerX, PlayerY;	// プレイヤーの位置
int Image;
int Image1;
int Image2;
int time;
SHOT shot_[MAX_SHOT];	// ショットデータ
SPARK spark_[MAX_SPARK];	// 火花データ


void CreateSpark(int x, int y);	// 火花を出す処理
void MoveSpark(void);	// 火花移動処理
void CreateShot(void);	// ショットを撃つ処理
void MoveShot(void);	// ショットの移動処理


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	int Key = 0;
	int OldKey = 0;	// 前のキー入力状態
	int sparkNum_, shotNum_;

	

	SetGraphMode(640, 480, 16);
	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// プレイヤーの初期位置をセット
	PlayerX = 320;
	PlayerY = 400;

	// ショットの存在を初期化する
	for (sparkNum_ = 0; sparkNum_ < MAX_SHOT; sparkNum_++)
		shot_[sparkNum_].Valid = 0;

	// 火花の存在を初期化する
	for (sparkNum_ = 0; sparkNum_ < MAX_SPARK; sparkNum_++)
		spark_[sparkNum_].Valid = 0;

	// ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		time++;
		// キー入力取得
		OldKey = Key;
		Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		if (Key & PAD_INPUT_RIGHT) PlayerX += 3;	// 右を押していたら右に進む
		if (Key & PAD_INPUT_LEFT) PlayerX -= 3;	// 左を押していたら左に進む

		// ショットの移動処理
		MoveShot();

		// 火花の移動処理
		MoveSpark();

		// ショットボタンを押していたらショットを出す
		if ((Key & ~OldKey) & PAD_INPUT_A) CreateShot();

		// 画面を初期化する
		ClearDrawScreen();
		Image = LoadGraph("Image/AuroraRing_R.png");
		Image1 = LoadGraph("Image/AuroraRing_G.png");
		Image2 = LoadGraph("Image/AuroraRing_B.png");
		// プレイヤーを描画する
		//DrawBox(PlayerX, PlayerY, PlayerX + 48, PlayerY + 48, GetColor(255, 0, 0), TRUE);
		DrawBox(PlayerX, PlayerY, PlayerX + 48, PlayerY + 48, 0xff0000,TRUE);
		//DrawGraph(0, 0,
		//	/*GetColor(spark_[shotNum_].Bright, spark_[shotNum_].Bright, spark_[shotNum_].Bright)*/
		//	Image, true);
		// ショットを描画する
		for (shotNum_ = 0; shotNum_ < MAX_SHOT; shotNum_++)
		{
			// ショットデータが有効な時のみ描画
			if (shot_[shotNum_].Valid == 1)
				DrawBox(shot_[shotNum_].shotPosX_, shot_[shotNum_].shotPosY_, shot_[shotNum_].shotPosX_ + 16, shot_[shotNum_].shotPosY_ + 16,
					0xffffff,true);

		}
		DrawFormatString(0, 0, 0xffffff, "aaaaaaaa");

		// 火花を描画する
		for (shotNum_ = 0; shotNum_ < MAX_SPARK; shotNum_++)
		{
			// 火花データが有効な時のみ描画
			/*	if (time / 10 % 3)*/ 
				if (spark_[shotNum_].Valid == 1) {
					DrawGraph(spark_[shotNum_].X / 200, spark_[shotNum_].Y/ 100,
						/*GetColor(spark_[shotNum_].Bright, spark_[shotNum_].Bright, spark_[shotNum_].Bright)*/
						Image, true);

					
						DrawGraph(spark_[shotNum_].X / 300, spark_[shotNum_].Y / 100,
							/*GetColor(spark_[shotNum_].Bright, spark_[shotNum_].Bright, spark_[shotNum_].Bright)*/
							Image1, true);
					
					
						DrawGraph(spark_[shotNum_].X / 100, spark_[shotNum_].Y / 100,
							/*GetColor(spark_[shotNum_].Bright, spark_[shotNum_].Bright, spark_[shotNum_].Bright)*/
							Image2, true);
					
				}
			
		/*	if (spark_[shotNum_].Valid == 1)
				DrawPixel(spark_[shotNum_].X / 100, spark_[shotNum_].Y / 100,
					GetColor(spark_[shotNum_].Bright, spark_[shotNum_].Bright, spark_[shotNum_].Bright));*/


		}
		

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}

// 火花を出す処理
void CreateSpark(int x, int y)
{
	int sparkNum_;

	// 使われていない火花データを探す
	for (sparkNum_ = 0; sparkNum_ < MAX_SPARK; sparkNum_++)
	{
		if (spark_[sparkNum_].Valid == 0) break;
	}

	// もし使われていない火花データがあったら火花を出す
	if (sparkNum_ != MAX_SPARK)
	{
		// 火花の位置を設定
		spark_[sparkNum_].X = x * 100;
		spark_[sparkNum_].Y = y * 100;

		// 移動力を設定
		spark_[sparkNum_].Sx = GetRand(1000) - 500;
		spark_[sparkNum_].Sy = -GetRand(500);

		// 火花の重さをセット
		spark_[sparkNum_].G = GetRand(10);

		// 火花の明るさセット
		spark_[sparkNum_].Bright = 255;

		// 火花データを使用中にセット
		spark_[sparkNum_].Valid = 1;
	}
}

// 火花移動処理
void MoveSpark(void)
{
	int sparkNum_;

	// 火花の移動処理
	for (sparkNum_ = 0; sparkNum_ < MAX_SPARK; sparkNum_++)
	{
		// 火花データが無効だったらスキップ
		if (spark_[sparkNum_].Valid == 0) continue;

		// 位置を移動力に応じてずらす
		spark_[sparkNum_].Y += spark_[sparkNum_].Sy;
		spark_[sparkNum_].X += spark_[sparkNum_].Sx;

		// 移動力を変更
		spark_[sparkNum_].Sy += spark_[sparkNum_].G;

		// 火花の明るさを下げる
		spark_[sparkNum_].Bright -= 2;

		// 火花の明るさが０以下になったら火花データを無効にする
		if (spark_[sparkNum_].Bright < 0) spark_[sparkNum_].Valid = 0;
	}
}

// ショットを撃つ処理
void CreateShot(void)
{
	int shotNum_;

	// 使われていないショットデータを探す
	for (shotNum_ = 0; shotNum_ < MAX_SHOT; shotNum_++)
	{
		if (shot_[shotNum_].Valid == 0) break;
	}

	// もし使われていないショットデータがあったらショットを出す
	if (shotNum_ != MAX_SHOT)
	{
		// ショットの位置を設定
		shot_[shotNum_].shotPosX_ = PlayerX + 16;
		shot_[shotNum_].shotPosY_ = PlayerY;

		// ショットデータを使用中にセット
		shot_[shotNum_].Valid = 1;
	}
}

// ショットの移動処理
void MoveShot(void)
{
	int shotNum_, sparkNum_, sparkMax_;

	// ショットの移動処理
	for (shotNum_ = 0; shotNum_ < MAX_SHOT; shotNum_++)
	{
		// ショットデータが無効だったらスキップ
		if (shot_[shotNum_].Valid == 0) continue;

		// 位置を上にずらす
		shot_[shotNum_].shotPosY_ -= 8;

		// 画面外に出ていたら火花を出したあとショットデータを無効にする
		if (shot_[shotNum_].shotPosY_ < 150)
		{
			// 火花を出す数をセット
			sparkMax_ = GetRand(60);
			for (sparkNum_ = 0; sparkNum_ < sparkMax_; sparkNum_++)
			{
				// 火花を生成
				CreateSpark(shot_[shotNum_].shotPosX_ + 8, shot_[shotNum_].shotPosY_ + 8);
			}

			// ショットデータを無効にする
			shot_[shotNum_].Valid = 0;
		}
	}
}




