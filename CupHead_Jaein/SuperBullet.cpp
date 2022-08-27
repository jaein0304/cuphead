#include "stdafx.h"
#include "SuperBullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"


SuperBullet::SuperBullet()
{
}


SuperBullet::~SuperBullet()
{
	Release();
}

void SuperBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/SpecialAttackSide.bmp", L"SpecialAttackSide");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/SpecialAttackUp.bmp", L"SpecialAttackUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/SpecialAttackDeath.bmp", L"SpecialAttackDeath");

	m_tInfo.fCX = 250.f;
	m_tInfo.fCY = 150.f;
	m_fSpeed = 10.f;

	m_pFrameKey = L"SpecialAttackSide";
	m_eCurState = SBT_RIGHT;
	m_ePreState = SBT_RIGHT;
	m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());

	
	//m_eGroup = RENDER_GAMEOBJECT;

}

int SuperBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle *(PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle *(PI / 180.f));

	Update_Rect();

	return OBJ_NOEVENT;
}

void SuperBullet::Late_Update(void)
{
	Animation_Change();
}

void SuperBullet::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	/*if (m_fAngle == 180)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SpecialAttackSide");
		m_tRect.left -= 150;
		m_tRect.right -= 150;
	}
	else if(m_fAngle == 0)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SpecialAttackSide");
		m_tRect.left += 150;
		m_tRect.right += 150;
	}*/

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(100, 255, 255));


	if (m_fAngle == 0)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SpecialAttackSide");

		m_pFrameKey = L"SpecialAttackSide";
		m_eCurState = SBT_RIGHT;
		m_ePreState = SBT_RIGHT;
		m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());

		m_tRect.left -= 150;
		m_tRect.right -= 150;
	}
	else if(m_fAngle == 180)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SpecialAttackSide");

		m_pFrameKey = L"SpecialAttackSide";
		m_eCurState = SBT_LEFT;
		m_ePreState = SBT_LEFT;
		m_tFrame.Set_Frame(0, 7, 1, 200, GetTickCount());

		m_tRect.left += 150;
		m_tRect.right += 150;
	}
	else if (m_fAngle == 90)
	{ 
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SpecialAttackUp");
		m_pFrameKey = L"SpecialAttackUp";
		m_eCurState = SBT_UP;
		m_ePreState = SBT_UP;
		m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());

		m_tInfo.fCX = 150.f;
		m_tInfo.fCY = 250.f;
		m_tRect.top += 150;
		m_tRect.right += 150;
	}
}

void SuperBullet::Release(void)
{
}

void SuperBullet::Animation_Change(void)
{

	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case SBT_LEFT:
			m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());
			break;

		case SBT_RIGHT:
			m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());
			break;

		case SBT_UP:
			m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());
			break;

		case SBT_DEAD:
			m_tFrame.Set_Frame(0, 8, 0, 200, GetTickCount());
			break;

			m_ePreState = m_eCurState;

		}
	}

}


void SuperBullet::Move_Frame(void)
{
	if (m_tFrame.dwSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			return;
	}
}