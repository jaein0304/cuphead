#include "stdafx.h"
#include "RedBullet.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CRedBullet::CRedBullet()
{
}


CRedBullet::~CRedBullet()
{
	Release();
}

void CRedBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/RedBullet.bmp", L"RedBullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/RedBullet_Death.bmp", L"RedBullet_Death");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/RedBullet_Spawn.bmp", L"RedBullet_Spawn");

	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	m_fSpeed = 10.f;

	m_pFrameKey = L"RedBullet";
	m_eCurState = BT_RIGHT;
	m_ePreState = BT_RIGHT;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameAnimation = 1;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CRedBullet::Update(void)
{
	Move_Frame();

	if (m_bDead)
		return OBJ_DEAD;
	//m_tInfo.fX += m_fSpeed;
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle *(PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle *(PI / 180.f));
	Update_Rect();

	return OBJ_NOEVENT;
}

void CRedBullet::Late_Update(void)
{
	Animation_Change();

}

void CRedBullet::Render(HDC hDC)
{
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
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"RedBullet");

		m_pFrameKey = L"RedBullet";
		m_eCurState = BT_RIGHT;
		m_ePreState = BT_RIGHT;
		m_tFrame.Set_Frame(0, 3, 0, 10, GetTickCount());
		m_tFrame.Set_Frame(0, 3, 1, 10, GetTickCount());
		m_tFrame.Set_Frame(0, 3, 7, 10, GetTickCount());

		m_tRect.left -= 150;
		m_tRect.right -= 150;
	}
	else if (m_fAngle == 180)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"RedBullet");

		m_pFrameKey = L"RedBullet";
		m_eCurState = BT_LEFT;
		m_ePreState = BT_LEFT;
		m_tFrame.Set_Frame(0, 3, 3, 10, GetTickCount());
		m_tFrame.Set_Frame(0, 3, 4, 10, GetTickCount());
		m_tFrame.Set_Frame(0, 3, 5, 10, GetTickCount());

		m_tRect.left += 150;
		m_tRect.right += 150;
	}
	else if (m_fAngle == 90)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"RedBullet");
		m_pFrameKey = L"RedBullet";
		m_eCurState = BT_UP;
		m_ePreState = BT_UP;
		m_tFrame.Set_Frame(0, 3, 3, 10, GetTickCount());
		m_tFrame.Set_Frame(0, 3, 2, 10, GetTickCount());
		m_tFrame.Set_Frame(0, 3, 1, 10, GetTickCount());

		//m_tInfo.fCX = 30.f;
		//m_tInfo.fCY = 142.f;
		m_tRect.top += 150;
		m_tRect.right += 150;
	}
}

void CRedBullet::Release(void)
{
}

void CRedBullet::Animation_Change(void)
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
