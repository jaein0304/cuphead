#pragma once
#include "Obj.h"

class CTile : public CObj
{
public:
	CTile();
	CTile(INFO& _Info);
	~CTile();

public:
	void MouseOver_Tile(bool _State) { m_bMouseOver = _State; }
	void Select_Tile(bool _State) { m_bSelect = _State; }
	bool Get_Select() { return m_bSelect; }
	TILETYPE Get_Type() { return m_eType; }
	void Set_Type(TILETYPE _eType) 
	{ 
		m_eType = _eType; 
		m_tInfo.eType = _eType;
	}

public:
	virtual		void	Initialize(void)	override;
	virtual		int	    Update(void)		override;
	virtual		void	Late_Update(void)	override;
	virtual		void	Render(HDC hDC)		override;
	virtual		void	Release(void)		override;

private:
	bool m_bMouseOver;
	bool m_bSelect;
	TILETYPE m_eType;
	//HDC	hMemDC;

};

