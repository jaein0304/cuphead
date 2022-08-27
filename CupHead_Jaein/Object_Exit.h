#pragma once
#include "Obj.h"
class CObject_Exit :
	public CObj
{
public:
	CObject_Exit();
	virtual ~CObject_Exit();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

