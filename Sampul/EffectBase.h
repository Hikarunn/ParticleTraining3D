#pragma once
class Effect;

class EffectBase
{
public:

	EffectBase(Effect* _effect);
	~EffectBase();

	// ��{���̏�����
	virtual bool Init(Effect::EffectBaseInfo* _baseInfo);

	// ��{���̌�n��
	virtual void Terminate(Effect::EffectBaseInfo* _baseInfo);

	// �G�t�F�N�g�̍쐬
	virtual bool Create(Effect::EffectInfo* _effectInfo);

	// �G�t�F�N�g�폜���ɌĂ΂��֐�
	virtual void Delete(Effect::EffectInfo* _effectInfo);

	// ��ԑJ��
	virtual void Step(Effect::EffectInfo* _effectInfo, float stepTime);

	// �`��
	virtual void Render(Effect::EffectInfo* _effectInfo);

	// �����p
	virtual void Setup(Effect::EffectInfo* _effectInfo,COLOR_U8 color,int modelHandle);

	Effect* GetEffect(void);

private:
	Effect* effect_;

};

