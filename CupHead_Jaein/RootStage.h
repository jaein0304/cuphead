#pragma once
#include "Scene.h"
class CRootStage :
	public CScene
{
public:
	CRootStage();
	virtual ~CRootStage();

public:
	void	Initialize(void);
	int		Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);


	//list<CObj*>* Get_List() { return m_ObjList; }
private:
	void			Insert_Bmp();
	void			Load_File();
//	list<CObj*>	m_ObjList[OBJ_END];
	DWORD			m_dwOldTime = GetTickCount();


};

