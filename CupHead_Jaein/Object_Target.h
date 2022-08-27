#pragma once
#include "Obj.h"
class CObject_Target :
	public CObj
{
public:
	CObject_Target();
	virtual ~CObject_Target();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

