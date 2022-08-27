#include "stdafx.h"
#include "Object_Rectangle.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

Object_Rectangle::Object_Rectangle()
{
}


Object_Rectangle::~Object_Rectangle()
{
	Release();
}

void Object_Rectangle::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/tutorial_plynth_after_pyramid_is_destroyed2.bmp", L"tutorial_plynth_after_pyramid_is_destroyed");

	m_tInfo.fCX = 288.f;
	m_tInfo.fCY = 321.f;

}

int Object_Rectangle::Update(void)
{
	Move_Frame();
	Update_Rect();

	return 0;
}

void Object_Rectangle::Late_Update(void)
{
}

void Object_Rectangle::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"tutorial_plynth_after_pyramid_is_destroyed");

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
		RGB(255, 2, 255));

}

void Object_Rectangle::Release(void)
{
}
