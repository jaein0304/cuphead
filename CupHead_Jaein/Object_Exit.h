#pragma once
#include "Obj.h"
class CObject_Exit :
	public CObj
{
public:
	CObject_Exit();
	virtual ~CObject_Exit();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

