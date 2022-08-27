#include "stdafx.h"
#include "RootStage.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Tile.h"

#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

#include "Potato.h"
#include "Onion.h"
#include "Carrot.h"

#include "CarrotBullet.h"
#include "CollisionMgr.h"
#include "Item.h"
#include "SoundMgr.h"

CRootStage::CRootStage()
{
}


CRootStage::~CRootStage()
{
	Release();
}

void CRootStage::Initialize(void)
{
	Insert_Bmp();
	Load_File();

	//플레이어 
	CObj* pPlayer = nullptr;
	pPlayer = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, pPlayer);
	pPlayer->Set_Pos(300.f, 550.f);

	//감자
	CObj* pPotato = nullptr;
	pPotato = CAbstractFactory<CPotato>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_POTATO, pPotato);

	CSoundMgr::Get_Instance()->StopSound(SOUND_ELDERBGM);
	CSoundMgr::Get_Instance()->StopSound(SOUND_TUTORIALBGM);



}

int CRootStage::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"Root.mp3", SOUND_ROOTBGM, 0.5);


	CObjMgr::Get_Instance()->Update();

	return OBJ_NOEVENT;
}

void CRootStage::Late_Update(void)
{
	if (GetAsyncKeyState('1'))
		CSceneMgr::Get_Instance()->Set_Scene(SC_TUTORIAL);

	if (GetAsyncKeyState('E'))
		CSceneMgr::Get_Instance()->Set_Scene(SC_EDIT);

	//if (1 <= CObjMgr::Get_Instance()->Get_Player()->Get_ItemCount())
	//	CSceneMgr::Get_Instance()->Set_Scene(SC_MENU);

	if (CObjMgr::Get_Instance()->Get_Player()->Get_Dead())
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_MENU);
		return;
	}

	if (CObjMgr::Get_Instance()->Get_Potato()->Get_Hp() <= 0)
	{
		if (m_dwOldTime + 20000 < GetTickCount())
		{
			CSceneMgr::Get_Instance()->Set_Scene(SC_ROOTSTAGE2);
			m_dwOldTime = GetTickCount();
		}
	}

	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CRootStage::Render(HDC hDC)
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


void CRootStage::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(CObjMgr::Get_Instance()->Get_List()[i].begin(), CObjMgr::Get_Instance()->Get_List()[i].end(), CDeleteObj());
		CObjMgr::Get_Instance()->Get_List()[i].clear();
	}
}

void CRootStage::Load_File()
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

void CRootStage::Insert_Bmp()
//백그라운드
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/BackGround/RootGround.bmp", L"RootGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/BackGround/RootGround1.bmp", L"RootGround1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/BackGround/RootGround2.bmp", L"RootGround2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/BackGround/RootGround3.bmp", L"RootGround3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/BackGround/RootGround_2.bmp", L"RootGround_2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/BackGround/RootGround_3.bmp", L"RootGround_3");

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/BlueTile.bmp", L"BlueTile");
}
