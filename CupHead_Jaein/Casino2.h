#pragma once
#include "Obj.h"

enum CASINOSTATE2 { CASINO2_MOVE, CASINO2_END };

class CCasino2 :
	public CObj
{
public:
	CCasino2();
	virtual ~CCasino2();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void Animation_Change(void);
	CASINOSTATE2	m_eCurState;
	CASINOSTATE2	m_ePreState;

};

