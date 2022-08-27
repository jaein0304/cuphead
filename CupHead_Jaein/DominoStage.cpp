#include "stdafx.h"
#include "DominoStage.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Domino.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CDominoStage::CDominoStage()
{
}


CDominoStage::~CDominoStage()
{
	Release();
}

void CDominoStage::Initialize(void)
{
	Load_File();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/BackGround/domino_white_background.bmp", L"domino_white_background");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/BackGround/dominos_close_background.bmp", L"dominos_close_background");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/BackGround/dominos_far_background.bmp", L"dominos_far_background");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/BackGround/dominos_mid_background.bmp", L"dominos_mid_background");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/BackGround/domino_background.bmp", L"domino_background");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/BackGround/domino_background2.bmp", L"domino_background2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/BackGround/domino_background2.bmp", L"domino_background3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/BackGround/floor.bmp", L"floor");

	CSoundMgr::Get_Instance()->StopSound(SOUND_DICEBGM);

	//플레이어 
	CObj* pPlayer = nullptr;
	pPlayer = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, pPlayer);
	pPlayer->Set_Pos(300.f, 550.f);

	//도미노  
	CObj* pDomino = nullptr;
	pDomino = CAbstractFactory<CDomino>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_ONION, pDomino); // ..? 양파말고 도미노로 바꾸면 오류남
}

int CDominoStage::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"The Kings Court.mp3", SOUND_DOMINOBGM, 0.5);

	if (m_fScrollY >= 100)
		m_fScrollY = 0.f;

	m_fScrollY += 10.f;

	Move_Frame();
	CObjMgr::Get_Instance()->Update();

	return OBJ_NOEVENT;
}

void CDominoStage::Late_Update(void)
{
	if (CObjMgr::Get_Instance()->Get_Onion()->Get_Hp() <= 0)
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_FINALSTAGE);
		return;
	}

	CScrollMgr::Get_Instance()->Scroll_Lock();
	CObjMgr::Get_Instance()->Late_Update();
}

void CDominoStage::Render(HDC hDC)
{
	//int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"domino_background3");

	BitBlt(hDC,
		0,
		0,
		900,
		600,
		hMemDC,
		0,
		0,
		SRCCOPY);


	CObjMgr::Get_Instance()->Render(hDC);
}

void CDominoStage::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(CObjMgr::Get_Instance()->Get_List()[i].begin(), CObjMgr::Get_Instance()->Get_List()[i].end(), CDeleteObj());
		CObjMgr::Get_Instance()->Get_List()[i].clear();
	}
}

void CDominoStage::Load_File()
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

void CDominoStage::Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}
