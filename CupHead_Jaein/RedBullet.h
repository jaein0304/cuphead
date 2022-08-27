#pragma once
#include "RedBulletParent.h"
class CRedBullet :
	public CRedBulletParent
{
public:
	CRedBullet();
	virtual ~CRedBullet();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	CObj*					m_pTarget = nullptr;
	void					Animation_Change(void);
	BULLETTYPE				m_eType = BULLET_END;
	BULLETSTATE				m_ePreState;
	BULLETSTATE				m_eCurState;

};

