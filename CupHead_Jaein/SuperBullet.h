#pragma once
#include "SuperBulletParent.h"
class SuperBullet :
	public SuperBulletParent
{
public:
	SuperBullet();
	virtual ~SuperBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void				Animation_Change(void);
	void				Move_Frame(void);
	DWORD				dwOldTime = GetTickCount();
	SPECIALBULLETSTATE	m_ePreState;
	SPECIALBULLETSTATE	m_eCurState;
};

