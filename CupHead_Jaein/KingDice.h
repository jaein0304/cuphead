#pragma once
#include "Obj.h"

enum KINGDICESTATE { KINGDICE_IDLE, KINGDICE_MOVE, KINGDICE_END };

class CKingDice :
	public CObj
{
public:
	CKingDice();
	virtual ~CKingDice();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void				Animation_Change();
	KINGDICESTATE		m_ePreState;
	KINGDICESTATE		m_eCurState;

};

