#pragma once
#include "Obj.h"

enum CASINOKINGSTATE { CASINOKING_IDLE, CASINOKING_MOVE, CASINOKING_END };

class CCasinoKing :
	public CObj
{
public:
	CCasinoKing();
	virtual ~CCasinoKing();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void	Animation_Change();
	CObj*	 m_pPlayer = nullptr;

	CASINOKINGSTATE		m_ePreState;
	CASINOKINGSTATE		m_eCurState;
};

