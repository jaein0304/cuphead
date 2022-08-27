#pragma once
#include "Effect.h"
class CRedBulletEffect :
	public CEffect
{
public:
	CRedBulletEffect();
	virtual ~CRedBulletEffect();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

