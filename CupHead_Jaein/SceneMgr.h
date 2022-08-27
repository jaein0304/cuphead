#pragma once
#include "Include.h"
#include "Scene.h"

#include "Title.h"
#include "MyMenu.h"
#include "RootStage.h"
#include "RootStage2.h"
#include "RootStage3.h"
#include "Tutorial.h"
#include "ElderHouse.h"
#include "DiceHouse.h"
#include "DominoStage.h"
#include "FinalStage.h"
#include "Ending.h"

#include "MyEdit.h"


class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();


public:
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);
	void Set_Scene(SCENEID _Select);
	//CScene* Get_Scene() { return m_pScene; }
	SCENEID Get_SceneID(void) { return m_eCurScene; }

	//ΩÃ±€≈Ê
public:
	static	CSceneMgr*	Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CSceneMgr;
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
	static CSceneMgr*		 m_pInstance;
	CScene*					 m_pScene = nullptr;
	
	SCENEID						m_eCurScene;		// «ˆ¿Á¿« æ¿ id
	SCENEID						m_ePreScene;		// ¿Ã¿¸ æ¿ id
};

