#include "stdafx.h"
#include "Object_Target.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CObject_Target::CObject_Target()
{
}


CObject_Target::~CObject_Target()
{
	Release();
}

void CObject_Target::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/tutorial_target.bmp", L"tutorial_target");

	m_tInfo.fCX = 76.f;
	m_tInfo.fCY = 87.f;

}

int CObject_Target::Update(void)
{
	Move_Frame();
	Update_Rect();

	return 0;
}

void CObject_Target::Late_Update(void)
{
}

void CObject_Target::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"tutorial_target");

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
		RGB(99, 92, 99));

}

void CObject_Target::Release(void)
{
}
