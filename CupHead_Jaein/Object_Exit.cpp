#include "stdafx.h"
#include "Object_Exit.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CObject_Exit::CObject_Exit()
{
}


CObject_Exit::~CObject_Exit()
{
	Release();
}

void CObject_Exit::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/tutorial_exit_door.bmp", L"tutorial_exit_door");

	m_tInfo.fCX = 320.f;
	m_tInfo.fCY = 273.f;
}

int CObject_Exit::Update(void)
{
	Move_Frame();
	Update_Rect();

	return 0;
}

void CObject_Exit::Late_Update(void)
{
}

void CObject_Exit::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"tutorial_exit_door");

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,					// 2, 3인자 : 복사 받을 위치 좌표
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,							// 4,5인자 : 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,										// 현재 그리고자하는 비트맵 이미지 DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX),	// 7,8인자 : 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),
		(int)m_tInfo.fCX,							// 9, 10인자 : 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CObject_Exit::Release(void)
{
}
