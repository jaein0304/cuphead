#pragma once

#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void	Initialize(void);
	void	Render(HDC hDC);
	void	Release(void);
	void	Load_File(void);

public:
	bool		Collision_Line(float& fPlayerX, float& fPlayerY, float* pY);

public:
	static	CLineMgr*	Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CLineMgr;
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
	static	CLineMgr*			m_pInstance;
	list<CLine*>				m_LineList;
	vector<RECT>				m_vecRect;
	float						m_fHighY;

};

