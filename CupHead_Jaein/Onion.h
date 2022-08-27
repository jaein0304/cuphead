#pragma once
#include "Obj.h"

enum ONIONSTATE { ONION_INTRO, ONION_IDLE, ONION_ATTACK, ONION_ATTACK2, ONION_DEAD, ONION_END };

class COnion :
	public CObj
{
public:
	COnion();
	virtual ~COnion();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	

private:
	void			Animation_Change(void);
	void			Insert_Bmp(void);
	list<CObj*>*	m_pBullet = nullptr;
	CObj*			CreateBullet();
	DWORD			m_dwOldTime = GetTickCount();
	DWORD			m_dwOldTime2 = GetTickCount();
	ONIONSTATE		m_ePreState;
	ONIONSTATE		m_eCurState;
	int				m_iOnionHp = 10;

};

