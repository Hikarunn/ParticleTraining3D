#pragma once
class Effect;

class EffectBase
{
public:

	EffectBase(Effect* _effect);
	~EffectBase();

	// 基本情報の初期化
	virtual bool Init(Effect::EffectBaseInfo* _baseInfo);

	// 基本情報の後始末
	virtual void Terminate(Effect::EffectBaseInfo* _baseInfo);

	// エフェクトの作成
	virtual bool Create(Effect::EffectInfo* _effectInfo);

	// エフェクト削除時に呼ばれる関数
	virtual void Delete(Effect::EffectInfo* _effectInfo);

	// 状態遷移
	virtual void Step(Effect::EffectInfo* _effectInfo, float stepTime);

	// 描画
	virtual void Render(Effect::EffectInfo* _effectInfo);

	// 準備用
	virtual void Setup(Effect::EffectInfo* _effectInfo,COLOR_U8 color,int modelHandle);

	Effect* GetEffect(void);

private:
	Effect* effect_;

};

