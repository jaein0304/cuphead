#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;


	CObj*		pTarget = nullptr;
	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;

		float	fWidth = iter->Get_Info().fX - pObj->Get_Info().fX;
		float	fHeight = iter->Get_Info().fY - pObj->Get_Info().fY;

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (!pTarget || fDistance > fDiagonal)
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}

	}

	return pTarget;
}
void CObjMgr::SaveMap()
{
	HANDLE	hFile = CreateFile(L"../Data/tuto.txt",			// 파일을 저장하고자 하는 경로 및 파일 이름 지정
		GENERIC_WRITE,				// 파일 접근 모드(GENERIC_WRITE 쓰기 전용, GENERIC_READ 읽기 전용)
		NULL,						// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 공유를 허용할 것인가 설정(NULL 값인 경우 공유 금지)
		NULL,						// 보안 속성, NULL일 경우 기본 보안 상태
		CREATE_ALWAYS,				// 파일 생성 방식, 해당 파일을 열어서 작업할 것인지 아니면 새로 만들것인지 설정, CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXITING : 파일이 있을 경우에만 연다
		FILE_ATTRIBUTE_NORMAL,		// 파일 속성(읽기 전용, 숨김 등) FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
		NULL);						// 생성될 파일의 속성을 제공할 템플릿 파일, 우리는 사용안하니깐 NULL


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : m_ObjList[OBJ_TILE])
	{
		WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 성공"), _T("완료"), MB_OK);
}

void CObjMgr::LoadMap(void)
{
	HANDLE	hFile = CreateFile(L"../Data/tuto.txt",			// 파일을 저장하고자 하는 경로 및 파일 이름 지정
		GENERIC_READ,				// 파일 접근 모드(GENERIC_WRITE 쓰기 전용, GENERIC_READ 읽기 전용)
		NULL,						// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 공유를 허용할 것인가 설정(NULL 값인 경우 공유 금지)
		NULL,						// 보안 속성, NULL일 경우 기본 보안 상태
		OPEN_EXISTING,				// 파일 생성 방식, 해당 파일을 열어서 작업할 것인지 아니면 새로 만들것인지 설정, CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXITING : 파일이 있을 경우에만 연다
		FILE_ATTRIBUTE_NORMAL,		// 파일 속성(읽기 전용, 숨김 등) FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
		NULL);						// 생성될 파일의 속성을 제공할 템플릿 파일, 우리는 사용안하니깐 NULL


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	INFO		tInfo{};

	for (auto& iter : m_ObjList[OBJ_TILE])
		dynamic_cast<CTile*>(iter)->Select_Tile(false);

	m_ObjList[OBJ_TILE].clear();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pTile = nullptr;
		pTile = CAbstractFactory<CTile>::Create();
		pTile->Set_Pos(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pTile)->Set_Type(tInfo.eType);
		dynamic_cast<CTile*>(pTile)->Select_Tile(true);
		CObjMgr::Get_Instance()->AddObject(OBJ_TILE, pTile);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Load 성공"), _T("완료"), MB_OK);
}


void CObjMgr::AddObject(OBJID eID, CObj * pObj)
{
	if (!pObj || OBJ_END <= eID)
		return;

	m_ObjList[eID].push_back(pObj);
}



int CObjMgr::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			//03.11
			/*RENDERID eID = iter->Get_GroupID();
			m_RenderSort[eID].push_back(iter);*/
		}
	}

	//오브젝트 충돌 
	CCollisionMgr::Get_Instance()->Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_TILE]);
	CCollisionMgr::Get_Instance()->Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_CUBE]);
	CCollisionMgr::Get_Instance()->Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_RECTANGLE]);

	//CCollisionMgr::Get_Instance()->Collision_RectEx(m_ObjList[OBJ_MONSTER_POTATO], m_ObjList[OBJ_TILE]);
	//CCollisionMgr::Get_Instance()->Collision_MonsterRect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER_POTATO]); //플레이어 -> 감자 충돌 시 

	//총알
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER_POTATO]);		//플레이어 총알 -> 감자 피깎기
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER_ONION]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER_CARROT]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER_DOMINO]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER_CASINO]);

	//타겟 
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_TARGET]);
	CCollisionMgr::Get_Instance()->Collision_SuperBullet(m_ObjList[OBJ_SUPERBULLET], m_ObjList[OBJ_TARGET]);


	//P총알->M총알
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_DOMINOBULLET1]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_ONIONBULLET]);


	//필살기 
	CCollisionMgr::Get_Instance()->Collision_SuperBullet(m_ObjList[OBJ_SUPERBULLET], m_ObjList[OBJ_MONSTER_POTATO]);
	CCollisionMgr::Get_Instance()->Collision_SuperBullet(m_ObjList[OBJ_SUPERBULLET], m_ObjList[OBJ_MONSTER_ONION]);
	CCollisionMgr::Get_Instance()->Collision_SuperBullet(m_ObjList[OBJ_SUPERBULLET], m_ObjList[OBJ_MONSTER_CARROT]);
	CCollisionMgr::Get_Instance()->Collision_SuperBullet(m_ObjList[OBJ_SUPERBULLET], m_ObjList[OBJ_MONSTER_DOMINO]);
	CCollisionMgr::Get_Instance()->Collision_SuperBullet(m_ObjList[OBJ_SUPERBULLET], m_ObjList[OBJ_MONSTER_CASINO]);

	//플레이어 총알 -> 몬스터 총알 
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_POTATOBULLET]);	
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_ONIONBULLET]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_CARROTBULLET1]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_CARROTBULLET2]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_DOMINOBULLET1]);

	// 몬스터 총알 -> 플레이어 피격 
	//CCollisionMgr::Get_Instance()->Collision_MonsterRect(m_ObjList[OBJ_POTATOBULLET], m_ObjList[OBJ_PLAYER]); 
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_ONIONBULLET], m_ObjList[OBJ_PLAYER]);	
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_CARROTBULLET1], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_CARROTBULLET2], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_DOMINOBULLET1], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_DOMINOBULLET2], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_DOMINOBULLET3], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_DOMINOBULLET4], m_ObjList[OBJ_PLAYER]);

	//아이템
	CCollisionMgr::Get_Instance()->Collision_RectItem(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM]);

	//CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ONIONBULLET]); //플레이어 즉사 

	//CCollisionMgr::Collision_ExitRect(m_ObjList[OBJ_PLAYER], m_ObjList[RED]);

}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		/*for (int j = 0; j < RENDER_END; ++j)
		{
			m_RenderSort[i].sort(CompareY<CObj*>);

			for (auto& iter : m_RenderSort[i])
				iter->Render(hDC);

			m_RenderSort[i].clear();
		}*/
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}
}

void CObjMgr::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj());
		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}