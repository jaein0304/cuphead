#include "stdafx.h"
#include "SceneMgr.h"
#include "ObjMgr.h"


CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_ePreScene(SC_END), m_eCurScene(SC_TITLE)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}


void CSceneMgr::Update(void)
{
	if (m_pScene)
		m_pScene->Update();

	

}

void CSceneMgr::Late_Update(void)
{
	if (m_pScene)
		m_pScene->Late_Update();

	

}

void CSceneMgr::Render(HDC hDC)
{
	if (m_pScene)
		m_pScene->Render(hDC);

	
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}

void CSceneMgr::Set_Scene(SCENEID _Select)
{
	m_eCurScene = _Select;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);	// 이 코드에 따른 문제가 발생할 수 있다.

		switch (m_eCurScene)
		{
		case SC_TITLE:
			m_pScene = new CTitle;
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_ELDERHOUSE:
			m_pScene = new CElderHouse;
			break;
				
		case SC_ROOTSTAGE:
			m_pScene = new CRootStage;
			break;

		case SC_ROOTSTAGE2:
			m_pScene = new CRootStage2;
			break;

		case SC_ROOTSTAGE3:
			m_pScene = new CRootStage3;
			break;

		case SC_DICEHOUSE:
			m_pScene = new CDiceHouse;
			break;

		case SC_DOMINOSTAGE:
			m_pScene = new CDominoStage;
			break;

		case SC_TUTORIAL:
			m_pScene = new CTutorial;
			break;

		case SC_FINALSTAGE:
			m_pScene = new CFinalStage;
			break;

		case SC_STAGEEND:
			m_pScene = new CEnding;
			break;

		case SC_EDIT:
			m_pScene = new CMyEdit;
			break;
		}
		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}

