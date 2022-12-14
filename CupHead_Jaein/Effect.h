#pragma once
#include "Obj.h"
class CEffect :
	public CObj
{
public:
	CEffect();
	virtual ~CEffect();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

protected:
	void	Animation_Change(void);
};

