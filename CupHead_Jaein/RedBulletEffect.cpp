#include "stdafx.h"
#include "RedBulletEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CRedBulletEffect::CRedBulletEffect()
{
}


CRedBulletEffect::~CRedBulletEffect()
{
	Release();
}

void CRedBulletEffect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/asd2.bmp", L"asd2");
	m_tInfo.fCX = 106.f;
	m_tInfo.fCY = 97.f;

	m_eGroup = RENDER_GAMEOBJECT;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iFrameAnimation = 0;
	m_tFrame.dwSpeed = 50;

}

int CRedBulletEffect::Update(void)
{
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CRedBulletEffect::Late_Update(void)
{
}

void CRedBulletEffect::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"asd2");

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * int(m_tInfo.fCX),
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));

}

void CRedBulletEffect::Release(void)
{
}
