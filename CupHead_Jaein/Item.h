#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();

public:
	enum ITEMSTATE { IDLE, DEAD, END };


public:
	virtual		void	Initialize(void)	override;
	virtual		int	    Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;

	void	Animation_Change(void);

	void	Set_State(bool _State) { m_bState = _State; }
private:
	ITEMSTATE				m_ePreState;
	ITEMSTATE				m_eCurState;
	bool					m_bState;

};
