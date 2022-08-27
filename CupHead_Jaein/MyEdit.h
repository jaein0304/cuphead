#pragma once
#include "Scene.h"

class CObj;

class CMyEdit :	public CScene
{
public:
	CMyEdit();
	~CMyEdit();

public:
	void Initialize(void);
	int	 Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

public:
	void CompareCube(list<CObj*>* _list);

private:
	list<CObj*>	m_GridList;
	TILETYPE m_eType;
	int	m_iCount;

};

