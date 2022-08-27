#include "stdafx.h"
#include "Tutorial.h"
#include "AbstractFactory.h"

#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "Player.h"
#include "Object_Cube.h"
#include "Object_Exit.h"
#include "Object_Rectangle.h"
#include "Object_Target.h"
#include "Tile.h"



CTutorial::CTutorial()
{
}


CTutorial::~CTutorial()
{
	Release();
}

void CTutorial::Initialize(void)
{
	Insert_Bmp();
	Load_File();

	CSoundMgr::Get_Instance()->StopSound(SOUND_ELDERBGM);

	CObj* pPlayer = nullptr;
	pPlayer = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, pPlayer);
	pPlayer->Set_Pos(500.f,600.f);

	CObj* pObject = nullptr;
	pObject = CAbstractFactory<CObject_Cube>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_CUBE, pObject);
	pObject->Set_Pos(700.f, 580.f);

	pObject = CAbstractFactory<Object_Rectangle>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_RECTANGLE, pObject);
	pObject->Set_Pos(920.f, 530.f);

	pObject = CAbstractFactory<CObject_Target>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_TARGET, pObject);
	pObject->Set_Pos(200.f, 550.f);

	pObject = CAbstractFactory<CObject_Exit>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_EXIT, pObject);
	pObject->Set_Pos(1500.f, 500.f);
	
}

int CTutorial::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"Tutorial.mp3", SOUND_TUTORIALBGM, 0.5);
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CTutorial::Late_Update(void)
{
	if (GetAsyncKeyState('2'))
		CSceneMgr::Get_Instance()->Set_Scene(SC_ROOTSTAGE);


	//if(CObjMgr::Get_Instance()->Get_Player()->Get_CheckStage() == 2)
	//	CSceneMgr::Get_Instance()->Set_Scene(SC_ROOTSTAGE);


	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_FinalLock();
}

void CTutorial::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"tutorial_room_back_layer_0002");

	BitBlt(hDC,
		iScrollX,
		iScrollY,
		1695,
		834,
		hMemDC,
		0,
		0,
		SRCCOPY);


	CObjMgr::Get_Instance()->Render(hDC);
}


void CTutorial::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(CObjMgr::Get_Instance()->Get_List()[i].begin(), CObjMgr::Get_Instance()->Get_List()[i].end(), CDeleteObj());
		CObjMgr::Get_Instance()->Get_List()[i].clear();
	}
}

void CTutorial::Load_File()
{
	HANDLE	hFile = CreateFile(L"../Data/tuto.txt",
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

void CTutorial::Insert_Bmp()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/Tutorial_BackGround.bmp", L"Tutorial_BackGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/tutorial_room_back_layer_0001.bmp", L"tutorial_room_back_layer_0001");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/tutorial_room_back_layer_0002.bmp", L"tutorial_room_back_layer_0002");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/Tutorial_BackGround2.bmp", L"Tutorial_BackGround2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/tutorial_background3.bmp", L"tutorial_background3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/88.bmp", L"88");

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/VioletTile.bmp", L"VioletTile");
}
