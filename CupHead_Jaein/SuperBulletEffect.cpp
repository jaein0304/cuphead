#include "stdafx.h"
#include "SuperBulletEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CSuperBulletEffect::CSuperBulletEffect()
{
}


CSuperBulletEffect::~CSuperBulletEffect()
{
}

void CSuperBulletEffect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/SuperBulletDeath.bmp", L"SuperBulletDeath");
	m_tInfo.fCX = 530.f;
	m_tInfo.fCY = 530.f;

	m_eGroup = RENDER_GAMEOBJECT;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.iFrameAnimation = 0;
	m_tFrame.dwSpeed = 100;
}

int CSuperBulletEffect::Update(void)
{
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CSuperBulletEffect::Late_Update(void)
{
}

void CSuperBulletEffect::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SuperBulletDeath");

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

void CSuperBulletEffect::Release(void)
{
}
