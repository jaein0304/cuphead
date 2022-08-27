#include "stdafx.h"
#include "RootStage2.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Tile.h"

#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

#include "Potato.h"
#include "Onion.h"
#include "Carrot.h"

#include "CarrotBullet.h"
#include "CollisionMgr.h"
#include "Item.h"

CRootStage2::CRootStage2()
{
}


CRootStage2::~CRootStage2()
{
	Release();
}

void CRootStage2::Initialize(void)
{
	Insert_Bmp();
	Load_File();


	//플레이어 
	CObj* pPlayer = nullptr;
	pPlayer = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, pPlayer);
	//pPlayer->Set_Pos(300.f, 550.f);

	//양파
	CObj* pOnion = nullptr;
	pOnion = CAbstractFactory<COnion>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_ONION, pOnion);
}

int CRootStage2::Update(void)
{
	CObjMgr::Get_Instance()->Update();

	return OBJ_NOEVENT;
}

void CRootStage2::Late_Update(void)
{
	if(CObjMgr::Get_Instance()->Get_Onion()->Get_Hp() <= 0) 
	{
	//	CSoundMgr::Get_Instance()->PlaySound(L"Onion_Die.wav", SOUND_ONIONATTACK, 1);

		if (m_dwOldTime + 20000 < GetTickCount())
		{
			CSceneMgr::Get_Instance()->Set_Scene(SC_ROOTSTAGE3);
			m_dwOldTime = GetTickCount();
		}
	}
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CRootStage2::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"RootGround_3");

	BitBlt(hDC,
		iScrollX,
		iScrollY,
		900,
		600,
		hMemDC,
		0,
		0,
		SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CRootStage2::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(CObjMgr::Get_Instance()->Get_List()[i].begin(), CObjMgr::Get_Instance()->Get_List()[i].end(), CDeleteObj());
		CObjMgr::Get_Instance()->Get_List()[i].clear();
	}
}

void CRootStage2::Insert_Bmp()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/BackGround/RootGround_3.bmp", L"RootGround_3");

}

void CRootStage2::Load_File()
{
	HANDLE	hFile = CreateFile(L"../Data/Save_Root.txt",
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Stage Load File을 불러오지 못했습니다."), _T("실패"), MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	INFO		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pTile = nullptr;
		pTile = CAbstractFactory<CTile>::Create();
		pTile->Set_Pos(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pTile)->Select_Tile(true);
		dynamic_cast<CTile*>(pTile)->Set_Type(tInfo.eType);
		CObjMgr::Get_Instance()->AddObject(OBJ_TILE, pTile);
	}
	CloseHandle(hFile);
	//MessageBox(g_hWnd, _T("Stage Load File을 불러왔습니다."), _T("성공"), MB_OK);
}
