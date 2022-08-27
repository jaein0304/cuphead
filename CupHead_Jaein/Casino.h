#pragma once
#include "Obj.h"

enum CASINOSTATE { CASINO_MOVE, CASINO_END };

class CCasino :
	public CObj
{
public:
	CCasino();
	virtual ~CCasino();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	void Animation_Change(void);
	CASINOSTATE	m_eCurState;
	CASINOSTATE	m_ePreState;


};

