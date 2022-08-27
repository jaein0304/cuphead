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
	HANDLE	hFile = CreateFile(L"../Data/tuto.txt",			// ������ �����ϰ��� �ϴ� ��� �� ���� �̸� ����
		GENERIC_WRITE,				// ���� ���� ���(GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// ���� ���, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ������ ����� ���ΰ� ����(NULL ���� ��� ���� ����)
		NULL,						// ���� �Ӽ�, NULL�� ��� �⺻ ���� ����
		CREATE_ALWAYS,				// ���� ���� ���, �ش� ������ ��� �۾��� ������ �ƴϸ� ���� ��������� ����, CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXITING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��) FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
		NULL);						// ������ ������ �Ӽ��� ������ ���ø� ����, �츮�� �����ϴϱ� NULL


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

	MessageBox(g_hWnd, _T("Save ����"), _T("�Ϸ�"), MB_OK);
}

void CObjMgr::LoadMap(void)
{
	HANDLE	hFile = CreateFile(L"../Data/tuto.txt",			// ������ �����ϰ��� �ϴ� ��� �� ���� �̸� ����
		GENERIC_READ,				// ���� ���� ���(GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// ���� ���, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ������ ����� ���ΰ� ����(NULL ���� ��� ���� ����)
		NULL,						// ���� �Ӽ�, NULL�� ��� �⺻ ���� ����
		OPEN_EXISTING,				// ���� ���� ���, �ش� ������ ��� �۾��� ������ �ƴϸ� ���� ��������� ����, CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXITING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��) FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
		NULL);						// ������ ������ �Ӽ��� ������ ���ø� ����, �츮�� �����ϴϱ� NULL


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
	MessageBox(g_hWnd, _T("Load ����"), _T("�Ϸ�"), MB_OK);
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

	//������Ʈ �浹 
	CCollisionMgr::Get_Instance()->Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_TILE]);
	CCollisionMgr::Get_Instance()->Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_CUBE]);
	CCollisionMgr::Get_Instance()->Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_RECTANGLE]);

	//CCollisionMgr::Get_Instance()->Collision_RectEx(m_ObjList[OBJ_MONSTER_POTATO], m_ObjList[OBJ_TILE]);
	//CCollisionMgr::Get_Instance()->Collision_MonsterRect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER_POTATO]); //�÷��̾� -> ���� �浹 �� 

	//�Ѿ�
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER_POTATO]);		//�÷��̾� �Ѿ� -> ���� �Ǳ��
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER_ONION]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER_CARROT]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER_DOMINO]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER_CASINO]);

	//Ÿ�� 
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_TARGET]);
	CCollisionMgr::Get_Instance()->Collision_SuperBullet(m_ObjList[OBJ_SUPERBULLET], m_ObjList[OBJ_TARGET]);


	//P�Ѿ�->M�Ѿ�
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_DOMINOBULLET1]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_ONIONBULLET]);


	//�ʻ�� 
	CCollisionMgr::Get_Instance()->Collision_SuperBullet(m_ObjList[OBJ_SUPERBULLET], m_ObjList[OBJ_MONSTER_POTATO]);
	CCollisionMgr::Get_Instance()->Collision_SuperBullet(m_ObjList[OBJ_SUPERBULLET], m_ObjList[OBJ_MONSTER_ONION]);
	CCollisionMgr::Get_Instance()->Collision_SuperBullet(m_ObjList[OBJ_SUPERBULLET], m_ObjList[OBJ_MONSTER_CARROT]);
	CCollisionMgr::Get_Instance()->Collision_SuperBullet(m_ObjList[OBJ_SUPERBULLET], m_ObjList[OBJ_MONSTER_DOMINO]);
	CCollisionMgr::Get_Instance()->Collision_SuperBullet(m_ObjList[OBJ_SUPERBULLET], m_ObjList[OBJ_MONSTER_CASINO]);

	//�÷��̾� �Ѿ� -> ���� �Ѿ� 
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_POTATOBULLET]);	
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_ONIONBULLET]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_CARROTBULLET1]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_CARROTBULLET2]);
	CCollisionMgr::Get_Instance()->Collision_Bullet(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_DOMINOBULLET1]);

	// ���� �Ѿ� -> �÷��̾� �ǰ� 
	//CCollisionMgr::Get_Instance()->Collision_MonsterRect(m_ObjList[OBJ_POTATOBULLET], m_ObjList[OBJ_PLAYER]); 
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_ONIONBULLET], m_ObjList[OBJ_PLAYER]);	
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_CARROTBULLET1], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_CARROTBULLET2], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_DOMINOBULLET1], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_DOMINOBULLET2], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_DOMINOBULLET3], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_DOMINOBULLET4], m_ObjList[OBJ_PLAYER]);

	//������
	CCollisionMgr::Get_Instance()->Collision_RectItem(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM]);

	//CCollisionMgr::Get_Instance()->Collision_MonsterBullet(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ONIONBULLET]); //�÷��̾� ��� 

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