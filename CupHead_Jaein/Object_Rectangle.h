#pragma once
#include "Obj.h"
class Object_Rectangle :
	public CObj
{
public:
	Object_Rectangle();
	virtual ~Object_Rectangle();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

