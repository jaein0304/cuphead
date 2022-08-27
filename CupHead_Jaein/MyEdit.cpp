#include "stdafx.h"
#include "MyEdit.h"
#include "Obj.h"
#include "Tile.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize(void)
{
	m_eType = GREEN;
	m_iCount = 0;
	int x=100, y=30;
	/*int x = 800 / 25;
	int y = 600 / 25;*/
	int Total = x * y;
	CObj* pTile = nullptr;

	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			pTile = new CTile;
			pTile->Initialize();
			float fD = pTile->Get_Info().fCX;
			float fR = pTile->Get_Info().fCX * 0.5f;
			float fX = fR + (fD * i);
			float fY = fR + (fD * j);
			pTile->Set_Pos(fX, fY);
			m_GridList.push_back(pTile);
		}
	}

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/GreenTile.bmp", L"GreenTile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/RedTile.bmp", L"RedTile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/PurPleTile.bmp", L"PurPleTile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/PebbleTile.bmp", L"PebbleTile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/BlueTile.bmp", L"BlueTile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/VioletTile.bmp", L"VioletTile");

}

int CMyEdit::Update(void)
{
	for (auto& iter : m_GridList)
		iter->Update();

	CObjMgr::Get_Instance()->Update();


	if (CKeyMgr::Get_Instance()->Key_Down(VK_CONTROL))
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_MENU);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		CObjMgr::Get_Instance()->SaveMap();
	}

	if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		CObjMgr::Get_Instance()->LoadMap();
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(15.f);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(-15.f);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-15.f);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(15.f);
	}


	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		m_eType = GREEN;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		m_eType = RED;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('3'))
	{
		m_eType = PURPLE;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('4'))
	{
		m_eType = PEBBLE;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('5'))
	{
		m_eType = BLUE;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('6'))
	{
		m_eType = VIOLET;
	}



	return 0;
}

void CMyEdit::Late_Update(void)
{
	for (auto& iter : m_GridList)
		iter->Late_Update();

	CObjMgr::Get_Instance()->Late_Update();

	CompareCube(CObjMgr::Get_Instance()->Get_List());

	for (auto& iter : m_GridList)
	{
		//¸¶¿ì½º 
		POINT		pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		if (CCollisionMgr::TileCollision(pt, iter))
		{
			dynamic_cast<CTile*>(iter)->MouseOver_Tile(true);
			dynamic_cast<CTile*>(iter)->Set_Type(m_eType);
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
			{
				if (false == dynamic_cast<CTile*>(iter)->Get_Select())
				{
					dynamic_cast<CTile*>(iter)->Select_Tile(true);
					dynamic_cast<CTile*>(iter)->Set_Type(m_eType);
					CObjMgr::Get_Instance()->SaveList(iter);
				}
				else
				{
					dynamic_cast<CTile*>(iter)->Select_Tile(false);
					CObjMgr::Get_Instance()->DeleteList(iter);
				}
			}
		}
		else
			dynamic_cast<CTile*>(iter)->MouseOver_Tile(false);
	}
}

void CMyEdit::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/BackGround/domino_white_background.bmp", L"domino_white_background");

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Stage1");

	BitBlt(hDC,
		0,
		0,
		1412,
		865,
		hMemDC,
		0,
		0,
		SRCCOPY);


	for (auto& iter : m_GridList)
		iter->Render(hDC);

	CObjMgr::Get_Instance()->Render(hDC);

}

void CMyEdit::Release(void)
{
	for (auto& iter : m_GridList)
		Safe_Delete(iter);

}

void CMyEdit::CompareCube(list<CObj*>* _list)
{
	for (auto& Destiter : m_GridList)
	{
		for (auto& Souriter : (*_list))
		{
			if (Destiter->Get_Info().fX == Souriter->Get_Info().fX
				&& Destiter->Get_Info().fY == Souriter->Get_Info().fY)
			{
				dynamic_cast<CTile*>(Destiter)->Select_Tile(true);
			}
		}
	}
}
