#pragma once
#include "Obj.h"
class Object_Rectangle :
	public CObj
{
public:
	Object_Rectangle();
	virtual ~Object_Rectangle();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

