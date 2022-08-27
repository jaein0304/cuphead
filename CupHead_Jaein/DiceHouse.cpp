#include "stdafx.h"
#include "DiceHouse.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "KingDice.h"
#include "SoundMgr.h"

CDiceHouse::CDiceHouse()
{
}


CDiceHouse::~CDiceHouse()
{
	Release();
}

void CDiceHouse::Initialize(void)
{
	Load_File();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/BackGround/DiceHouse_background.bmp", L"DiceHouse_background");
	CSoundMgr::Get_Instance()->StopSound(SOUND_ROOTBGM);

	CObj* pObj = nullptr;
	pObj = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, pObj);
	pObj->Set_Pos(500.f, 600.f);


	CObj* pKingDice = nullptr;
	pKingDice = CAbstractFactory<CKingDice>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_KINGDICE, pKingDice);

}

int CDiceHouse::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"DiceHouse.mp3", SOUND_DICEBGM, 0.5);

	if (GetAsyncKeyState(VK_SPACE))
		CSceneMgr::Get_Instance()->Set_Scene(SC_DOMINOSTAGE);

	
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_DiceHouseLock();

	return OBJ_NOEVENT;
}

void CDiceHouse::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

}

void CDiceHouse::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"DiceHouse_background");

	BitBlt(hDC,
		iScrollX,
		iScrollY,
		1540,
		800,
		hMemDC,
		0,
		0,
		SRCCOPY);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CDiceHouse::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(CObjMgr::Get_Instance()->Get_List()[i].begin(), CObjMgr::Get_Instance()->Get_List()[i].end(), CDeleteObj());
		CObjMgr::Get_Instance()->Get_List()[i].clear();
	}
}

void CDiceHouse::Load_File()
{

	HANDLE	hFile = CreateFile(L"../Data/Save.txt",
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


