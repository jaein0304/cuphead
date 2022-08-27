#include "stdafx.h"
#include "BasicBullet.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CBasicBullet::CBasicBullet()
{
}

CBasicBullet::~CBasicBullet()
{
	Release();
}

void CBasicBullet::Initialize(void)
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

int CBasicBullet::Update(void)
{
	Move_Frame();

	if (m_bDead)
		return OBJ_DEAD;
	//m_tInfo.fX += m_fSpeed;
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle *(PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle *(PI / 180.f));

	/*switch (m_eType)
	{
	case BULLET_BASE:
		m_tInfo.fX += m_fSpeed;
		break;

	case BULLET_FOLLOW:
		m_tInfo.fX += m_fSpeed * cosf(m_tInfo.fX * (PI / 180));
		m_tInfo.fY += m_fSpeed * sinf(m_tInfo.fY * (PI / 180));
		break;
	}*/
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBasicBullet::Late_Update(void)
{
	Animation_Change();
}

void CBasicBullet::Render(HDC hDC)
{

	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

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
		RGB(255, 0, 255));							// 제거하고자 하는 색상

	if (m_fAngle == 0)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BulletLeftRight");

		m_pFrameKey = L"BulletLeftRight";
		m_eCurState = BT_RIGHT;
		m_ePreState = BT_RIGHT;
		m_tFrame.Set_Frame(3, 7, 1, 10, GetTickCount());

		m_tRect.left -= 150;
		m_tRect.right -= 150;
	}
	else if (m_fAngle == 180)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BulletLeftRight");

		m_pFrameKey = L"BulletLeftRight";
		m_eCurState = BT_LEFT;
		m_ePreState = BT_LEFT;
		m_tFrame.Set_Frame(3, 7, 0, 30, GetTickCount());

		m_tRect.left += 150;
		m_tRect.right += 150;
	}
	else if (m_fAngle == 90)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BulletUpDown");
		m_pFrameKey = L"BulletUpDown";
		m_eCurState = BT_UP;
		m_ePreState = BT_UP;
		m_tFrame.Set_Frame(3, 7, 0,30, GetTickCount());
		m_tInfo.fCX = 30.f;
		m_tInfo.fCY = 142.f;
		m_tRect.top += 150;
		m_tRect.right += 150;
	}
}

void CBasicBullet::Release(void)
{

}

void CBasicBullet::Animation_Change(void)
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

void CBasicBullet::Insert_Bmp(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletDeath.bmp", L"BulletDeath");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletLeftRight.bmp", L"BulletLeftRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletStart.bmp", L"BulletStart");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletUpDown.bmp", L"BulletUpDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletUpLeftRight.bmp", L"BulletUpLeftRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Bullet.bmp", L"Bullet");

}


