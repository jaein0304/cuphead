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
		m_tRect.left + iScrollX,					// 2, 3���� : ���� ���� ��ġ ��ǥ
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,							// 4,5���� : ���� ���� ����, ���� ����
		(int)m_tInfo.fCY,
		hMemDC,										// ���� �׸������ϴ� ��Ʈ�� �̹��� DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX),	// 7,8���� : ��Ʈ���� ����� ���� ��ǥ
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),
		(int)m_tInfo.fCX,							// 9, 10���� : ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CObject_Exit::Release(void)
{
}
