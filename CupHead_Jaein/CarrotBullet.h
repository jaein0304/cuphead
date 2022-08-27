#pragma once
#include "Bullet.h"
class CCarrotBullet :
	public CBullet
{
public:
	CCarrotBullet();
	virtual ~CCarrotBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Animation_Change(void);
	CObj * CreateBullet();
	void		Set_TargetPos(float _fX, float _fY)
	{
		m_TargetPos.x = (LONG)_fX;
		m_TargetPos.y = (LONG)_fY;
	}
private:
	DWORD							m_dwOldTime = GetTickCount();
	BULLETTYPE_MONSTER				m_ePreState;
	BULLETTYPE_MONSTER				m_eCurState;
	int								m_iAttackCount = 0;
	POINT		m_TargetPos;

};

