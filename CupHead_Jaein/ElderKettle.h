#pragma once
#include "Obj.h"

enum ELDERSTATE { ELDER_IDLE, ELDER_MOVE, ELDER_END };

class CElderKettle :
	public CObj
{
public:
	CElderKettle();
	virtual ~CElderKettle();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void	Animation_Change();
	CObj*	 m_pPlayer = nullptr;

	ELDERSTATE		m_ePreState;
	ELDERSTATE		m_eCurState;
};

