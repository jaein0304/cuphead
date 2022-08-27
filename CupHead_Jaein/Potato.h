#pragma once
#include "Obj.h"


enum POTATOSTATE { POTATO_INTRO, POTATO_INTRO2, POTATO_IDLE, POTATO_ATTACK, POTATO_DEAD, POTATO_END };

class CPotato :
	public CObj
{
public:
	CPotato();
	virtual ~CPotato();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Insert_Bmp(void);
	void		Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }

public:
	bool Set_Damage(int _iDamage)
	{
		m_iHp -= _iDamage;
		if (m_iHp <= 0)
			return true;

		return false;
	}

private:
	list<CObj*>*	m_pBullet = nullptr;
	void			Animation_Change(void);
	CObj*			CreateBullet();
	DWORD			m_dwOldTime = GetTickCount();
	DWORD			m_dwOldTime2 = GetTickCount();
	int				m_iAttackCount = 0;

	
	POTATOSTATE		m_ePreState;
	POTATOSTATE		m_eCurState;
};

