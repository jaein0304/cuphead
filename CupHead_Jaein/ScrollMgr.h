#pragma once

#include "Include.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();



public:
	float			Get_ScrollX() { return m_fScrollX; }
	float			Get_ScrollY() { return m_fScrollY; }

public:
	void			Set_ScrollX(float _fX) { m_fScrollX += _fX; }
	void			Set_ScrollY(float _fY) { m_fScrollY += _fY; }

public:
	void			Scroll_Lock(void);
	void			Scroll_Lock2(void);
	void			Scroll_TutorialLock(void);
	void			Scroll_DiceHouseLock(void);
	void			Scroll_DominoLock(void);
	void			Scroll_FinalLock(void);

public:
	static	CScrollMgr*	Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CScrollMgr;
		}

		return m_pInstance;
	}
	static	void		Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static	CScrollMgr*			m_pInstance;
	float						m_fScrollX = 0.f;
	float						m_fScrollY = 0.f;
};


