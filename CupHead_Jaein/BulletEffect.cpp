#include "stdafx.h"
#include "BulletEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CBulletEffect::CBulletEffect()
{
}


CBulletEffect::~CBulletEffect()
{
}

void CBulletEffect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletDeath.bmp", L"BulletDeath");
	m_tInfo.fCX = 280.f;
	m_tInfo.fCY = 280.f;

	m_eGroup = RENDER_GAMEOBJECT;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameAnimation = 0;
	m_tFrame.dwSpeed = 50;
}

int CBulletEffect::Update(void)
{
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBulletEffect::Late_Update(void)
{
}

void CBulletEffect::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BulletDeath");

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
		RGB(255, 0, 255));
}

void CBulletEffect::Release(void)
{
}
