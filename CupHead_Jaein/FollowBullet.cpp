#include "stdafx.h"
#include "FollowBullet.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CDirectionMgr.h"


CFollowBullet::CFollowBullet()
{
}


CFollowBullet::~CFollowBullet()
{
	Release();
}

void CFollowBullet::Initialize(void)
{
	Insert_Bmp();
	Animation_Change();
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 30.f;
	m_fSpeed = 10.f;

	m_pFrameKey = L"BulletLeftRight";
	m_eCurState = BT_RIGHT;
	m_ePreState = BT_RIGHT;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iFrameAnimation = 1;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CFollowBullet::Update(void)
{
	Move_Frame();

	if (m_bDead)
		return OBJ_DEAD;

	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

	float radian = atan2f(fY, fX);

	m_tInfo.fX += m_fSpeed * cosf(radian);
	m_tInfo.fY += m_fSpeed * sinf(radian);

	Update_Rect();
	return OBJ_NOEVENT;
}

void CFollowBullet::Late_Update(void)
{
}

void CFollowBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void CFollowBullet::Release(void)
{
}

void CFollowBullet::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BT_START:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameAnimation = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case BT_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameAnimation = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case BT_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameAnimation = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case BT_UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameAnimation = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case BT_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameAnimation = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case BT_LU:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameAnimation = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case BT_RU:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameAnimation = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case BT_DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameAnimation = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

			m_ePreState = m_eCurState;
		}
	}
}

void CFollowBullet::Insert_Bmp(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletDeath.bmp", L"BulletDeath");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletLeftRight.bmp", L"BulletLeftRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletStart.bmp", L"BulletStart");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletUpDown.bmp", L"BulletUpDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletUpLeftRight.bmp", L"BulletUpLeftRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Bullet.bmp", L"Bullet");

}

