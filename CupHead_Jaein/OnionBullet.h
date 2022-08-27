#pragma once
#include "Bullet.h"
class COnionBullet :
	public CBullet
{
public:
	COnionBullet();
	virtual ~COnionBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Animation_Change(void);

private:
	BULLETTYPE_MONSTER				m_ePreState;
	BULLETTYPE_MONSTER				m_eCurState;
};

