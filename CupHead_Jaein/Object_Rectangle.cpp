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
		m_tRect.left + iScrollX,					// 2, 3���� : ���� ���� ��ġ ��ǥ
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,							// 4,5���� : ���� ���� ����, ���� ����
		(int)m_tInfo.fCY,
		hMemDC,										// ���� �׸������ϴ� ��Ʈ�� �̹��� DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX),	// 7,8���� : ��Ʈ���� ����� ���� ��ǥ
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),
		(int)m_tInfo.fCX,							// 9, 10���� : ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 2, 255));

}

void Object_Rectangle::Release(void)
{
}
