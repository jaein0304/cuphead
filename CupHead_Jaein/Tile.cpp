#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CTile::CTile()
	:m_eType(GREEN)
{
}

CTile::CTile(INFO & _Info)
	: m_eType(GREEN)
{
	m_tInfo.fX = _Info.fX;
	m_tInfo.fY = _Info.fY;
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_eType = GREEN;
	m_bMouseOver = false;
	m_bSelect = false;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CTile::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update(void)
{
}

void CTile::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_bSelect)
	{
		HDC hMemDC = nullptr;

		if(GREEN == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"GreenTile");
		else if(RED == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"RedTile");
		else if (PURPLE == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PurPleTile");
		else if (PEBBLE == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PebbleTile");
		else if (BLUE == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BlueTile");
		else if (VIOLET == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"VioletTile");

		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,		// 2, 3인자 : 복사 받을 위치 좌표
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,				// 4,5인자 : 복사 받을 가로, 세로 길이
			(int)m_tInfo.fCY,
			hMemDC,							// 현재 그리고자하는 비트맵 이미지 DC
			0,								// 7,8인자 : 비트맵을 출력할 시작 좌표
			0,
			(int)m_tInfo.fCX,				// 9, 10인자 : 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));			// 제거하고자 하는 색상
	}
	else if (m_bMouseOver)
	{
		HDC hMemDC = nullptr;

		if (GREEN == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"GreenTile");
		else if (RED == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"RedTile");
		else if (PURPLE == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PurPleTile");
		else if (PEBBLE == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PebbleTile");
		else if (BLUE == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BlueTile");
		else if (VIOLET == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"VioletTile");

		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,		// 2, 3인자 : 복사 받을 위치 좌표
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,				// 4,5인자 : 복사 받을 가로, 세로 길이
			(int)m_tInfo.fCY,
			hMemDC,							// 현재 그리고자하는 비트맵 이미지 DC
			0,								// 7,8인자 : 비트맵을 출력할 시작 좌표
			0,
			(int)m_tInfo.fCX,				// 9, 10인자 : 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));			// 제거하고자 하는 색상


		//HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255)); // 펜생성
		//HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);//펜선택

		//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

		//hPen = (HPEN)::SelectObject(hDC, hOldPen);//펜선택
		//DeleteObject(hPen);  //펜삭제
	}
	else
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CTile::Release(void)
{
}
