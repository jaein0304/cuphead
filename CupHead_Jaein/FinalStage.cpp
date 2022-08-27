#include "stdafx.h"
#include "FinalStage.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Item.h"
#include "Casino.h"
#include "Casino2.h"
#include "CasinoKing.h"

#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"


CFinalStage::CFinalStage()
{
}


CFinalStage::~CFinalStage()
{
	Release();
}

void CFinalStage::Initialize(void)
{
	Load_File();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/House/Casino2.bmp", L"Casino");
	CSoundMgr::Get_Instance()->StopSound(SOUND_DOMINOBGM);

	CObj* pPlayer = nullptr;
	pPlayer = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, pPlayer);
	pPlayer->Set_Pos(100.f, 600.f);

	/*CObj* pKing = nullptr;
	pKing = CAbstractFactory<CCasinoKing>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_KINGDICE, pKing);*/
	
	//CObj* pItem = nullptr;
	//for (int i = 0; i < 5; ++i)
	//{
	//	//pItem = CAbstractFactory<CItem>::CreateItem(500.f, 430.f, ITEM_1);
	//	pItem = CAbstractFactory<CItem>::CreateItem(rand() % 1695, rand() % (500) + 200, ITEM_1);
	//	CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, pItem);
	//}
}

int CFinalStage::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"Die House Electro Swing Remix ft OR3O.mp3", SOUND_FINALBGM, 0.5);

	CObj* pCasino = nullptr;
	if (m_dwOldTime + 3000 < GetTickCount())
	{
		pCasino = CAbstractFactory<CCasino>::Create();
		CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_CASINO, pCasino);
		pCasino->Set_Pos(100.f, 600.f);
		/*if (rand() % 2)
			pCasino->Set_Pos(100.f, 550.f);
		else
			pCasino->Set_Pos(1600.f, 550.f);*/
		
		m_dwOldTime = GetTickCount();
	}

	CObj* pCasino2 = nullptr;
	if (m_dwOldTime2 + 3000 < GetTickCount())
	{
		pCasino2 = CAbstractFactory<CCasino2>::Create();
		CObjMgr::Get_Instance()->AddObject(OBJ_MONSTER_CASINO, pCasino2);
		pCasino2->Set_Pos(1600.f, 600.f);

		m_dwOldTime2 = GetTickCount();
	}

	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_FinalLock();

	return OBJ_NOEVENT;
}

void CFinalStage::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	CObj* player = nullptr;
	player = CObjMgr::Get_Instance()->Get_Player();
	if (player)
	{
		if (10 <= player->Get_ItemCount())
		{
			//if (m_dwOldTime + 5000 < GetTickCount()) // update에 있는 m_dwOldTime이랑 겹쳐서 안돼 , 하려면 변수 새로 선언 
			//{
				CSceneMgr::Get_Instance()->Set_Scene(SC_STAGEEND);
				m_dwOldTime = GetTickCount();
			//}
		}
	}
}

void CFinalStage::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Casino");

	BitBlt(hDC,
		iScrollX,
		iScrollY,
		1695,
		834,
		hMemDC,
		0,
		0,
		SRCCOPY);

	CObj* player = nullptr;
	player = CObjMgr::Get_Instance()->Get_Player();
	CObjMgr::Get_Instance()->Render(hDC);
	if (player)
	{
		int iItemCount = dynamic_cast<CPlayer*>(player)->Get_ItemCount();

		TCHAR	m_szHp[32] = L"";
		wsprintf(m_szHp, L" Coin : %d", iItemCount);
		TextOut(hDC, 650.f, 100.f, m_szHp, lstrlen(m_szHp));

	}
}

void CFinalStage::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(CObjMgr::Get_Instance()->Get_List()[i].begin(), CObjMgr::Get_Instance()->Get_List()[i].end(), CDeleteObj());
		CObjMgr::Get_Instance()->Get_List()[i].clear();
	}
}

void CFinalStage::Load_File()
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

