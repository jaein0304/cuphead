#pragma once
#include "Include.h"
#include "Player.h"


class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

private:
	HDC			m_DC;
	DWORD		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[16];

	list<CObj*>	m_ObjList[OBJ_END];


};

