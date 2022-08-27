#include "stdafx.h"
#include "ElderHouse.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "ElderKettle.h"
#include "SoundMgr.h"

CElderHouse::CElderHouse()
{
}


CElderHouse::~CElderHouse()
{
	Release();
}

void CElderHouse::Initialize(void)
{
	Load_File();
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/VioletTile.bmp", L"VioletTile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/House/ElderHouse_Inside.bmp", L"ElderHouse_Inside");
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/BackGround/ElderKettleMusic.mp3", SOUND_EFFECT, 10);
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/BackGround/ElderKettleMusic.wav", SOUND_EFFECT, 10);

	CObj* pPlayer = nullptr;
	pPlayer = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, pPlayer);
	pPlayer->Set_Pos(500.f, 600.f);

	CObj* pElderKettle = nullptr;
	pElderKettle = CAbstractFactory<CElderKettle>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_ELDERKETTLE, pElderKettle);

	CSoundMgr::Get_Instance()->StopSound(SOUND_CARROTDIE);
	CSoundMgr::Get_Instance()->StopSound(SOUND_ROOTBGM);
	CSoundMgr::Get_Instance()->StopSound(SOUND_TUTORIALBGM);

}

int CElderHouse::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"ElderKettleMusic.wav", SOUND_ELDERBGM, 0.5);

	if (GetAsyncKeyState('1'))
		CSceneMgr::Get_Instance()->Set_Scene(SC_TUTORIAL);

	if (GetAsyncKeyState('3'))
		CSceneMgr::Get_Instance()->Set_Scene(SC_DICEHOUSE);

	if (GetAsyncKeyState('E'))
		CSceneMgr::Get_Instance()->Set_Scene(SC_EDIT);

	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_Lock2();

	return OBJ_NOEVENT;
}

void CElderHouse::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

}

void CElderHouse::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ElderHouse_Inside");

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

void CElderHouse::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(CObjMgr::Get_Instance()->Get_List()[i].begin(), CObjMgr::Get_Instance()->Get_List()[i].end(), CDeleteObj());
		CObjMgr::Get_Instance()->Get_List()[i].clear();
	}
}

void CElderHouse::Load_File()
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
