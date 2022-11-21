#pragma once


	enum class EffectNum {
		effect_Sphere_,
		effectNum_
	};



	
	


static constexpr int MAXNUM = 256;

class Effect
{
public:

	// エフェクトの基本情報
	struct EffectBaseInfo
	{
		// エフェクトが使用するグラフィックハンドル
		int graphHandle_;
	};

	// エフェクトの情報
	struct EffectInfo
	{
		// 構造体を使用しているかどうかのフラグ
		bool useFlag_;

		// エフェクトの終了がリクエストされているかどうかのフラグ
		bool endRequest;

		// エフェクトの本体
		EffectNum effect_;

		// エフェクトの基本構造体
		EffectBaseInfo* baseInfo;

		// エフェクト別のデータを格納しているメモリ領域のアドレス
		void* subData;
	};


	// エフェクトの初期化
	bool Init(void);
	// エフェクトの作成
	EffectInfo Create(Effect effect);

	// 全エフェクトの描画
	void RenderAll(void);

	// エフェクトの終了リクエスト
	void EffectEndRequest(EffectInfo* effectInfo);

	// エフェクト処理の後始末
	void Terminalize(void);

	// エフェクトの削除
	void Delete(EffectInfo *effectInfo);

	// 全エフェクトの削除
	void DeleteAll(void);

	// 全エフェクトの状態遷移
	void StepAll(float stepTime);

private:
	

	// エフェクト別の処理を分けるためのコールバック関数テーブル
	struct EffectFunction
	{
		// 初期化時に呼ばれる関数へのポインタ
		bool (*Init)(EffectBaseInfo* baseInfo_);

		// 後始末時に呼ばれる関数へのポインタ
		void (*Terminate)(EffectBaseInfo* baseInfo_);

		// 作成時に呼ばれる関数へのポインタ
		bool (*Create)(EffectInfo* effectInfo_);

		// 削除時に呼ばれる関数へのポインタ
		void (*Delete)(EffectInfo* effectInfo_);

		// 状態遷移時に呼ばれる関数へのポインタ
		void (*Step)(EffectInfo* effectInfo_, float stepTime);

		// 描画時に呼ばれる関数へのポインタ
		void (*Render)(EffectInfo* effectInfo);

	};

	struct EffectFunction effectFunctionTable_[(int)EffectNum::effectNum_] =
	{

	};


	
};

