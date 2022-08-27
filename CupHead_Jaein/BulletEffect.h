#pragma once
#include "Effect.h"
class CBulletEffect :
	public CEffect
{
public:
	CBulletEffect();
	virtual ~CBulletEffect();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

