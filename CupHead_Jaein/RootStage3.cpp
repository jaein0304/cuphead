#include "stdafx.h"
#include "RootStage3.h"
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
CRootStage3::CRootStage3()
{
}


CRootStage3::~CRootStage3()
{
	Release();
}

void CRootStage3::Initialize(void)
{
	Insert_Bmp();
	Load_File();

	//플레이어 
	CObj* pPlayer = nullptr;
	pPlayer = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, pPlayer);

	//당근 
	CObj* pCarrot = nullptr;
	pCarrot = CAbstractFactory<CCarrot>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_CARROT, pCarrot);

	CSoundMgr::Get_Instance()->StopSound(SOUND_ONIONDIE);


}

int CRootStage3::Update(void)
{
	CObjMgr::Get_Instance()->Update();

	//안먹힘 
	if (GetAsyncKeyState('K') & 0x0001)
		CObjMgr::Get_Instance()->Get_Carrot()->Set_Hp(1);

	return OBJ_NOEVENT;
}

void CRootStage3::Late_Update(void)
{
	if (CObjMgr::Get_Instance()->Get_Carrot()->Get_Hp() <= 0)
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_DICEHOUSE);
		return;
	}

	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CRootStage3::Render(HDC hDC)
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

void CRootStage3::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(CObjMgr::Get_Instance()->Get_List()[i].begin(), CObjMgr::Get_Instance()->Get_List()[i].end(), CDeleteObj());
		CObjMgr::Get_Instance()->Get_List()[i].clear();
	}
}

void CRootStage3::Insert_Bmp()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/BackGround/RootGround_3.bmp", L"RootGround_3");

}

void CRootStage3::Load_File()
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
