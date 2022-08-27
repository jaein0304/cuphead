#pragma once
#include "Obj.h"
class MoveFloor :
	public CObj
{
public:
	MoveFloor();
	virtual ~MoveFloor();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	void	Animation_Change();
	BULLETTYPE_MONSTER				m_ePreState;
	BULLETTYPE_MONSTER				m_eCurState;
};

