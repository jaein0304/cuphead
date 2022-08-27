#include "stdafx.h"
#include "CarrotFollowBullet.h"
#include "BmpMgr.h"

CCarrotFollowBullet::CCarrotFollowBullet()
{
}


CCarrotFollowBullet::~CCarrotFollowBullet()
{
}

void CCarrotFollowBullet::Initialize(void)
{
	m_tInfo.fCX = 153.9f;
	m_tInfo.fCY = 163.f;

	m_fSpeed = 1.f;	
	//m_tInfo.fCX = 82.f;
	//m_tInfo.fCY = 137.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Carrot/Carrot_FollowBeam.bmp", L"Carrot_FollowBeam");

	m_pFrameKey = L"Carrot_FollowBeam";
	m_eCurState = BULLET_MONSTER_FOLLOW;
	m_ePreState = BULLET_MONSTER_FOLLOW;
	m_tFrame.Set_Frame(0, 2, 0, 200, GetTickCount());
}

int CCarrotFollowBullet::Update(void)
{
	Move_Frame();
	Animation_Change();

	if (m_bDead)
		return OBJ_DEAD;

	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

	float radian = atan2f(fY, fX);

	m_tInfo.fX += m_fSpeed * cosf(radian);
	m_tInfo.fY += m_fSpeed * sinf(radian);

	//만약 총알의 각도와 플레이어의 각도가 같으면 바닥으로 추락...
	/*if (m_pTarget->Get_Info().fX < fX)
		m_tInfo.fX -= 3.f;*/

	Update_Rect();

	return OBJ_NOEVENT;
}

void CCarrotFollowBullet::Late_Update(void)
{
	Update_Rect();

	if (0 >= m_tRect.left || WINCX <= m_tRect.right ||0 >= m_tRect.top || WINCY <= m_tRect.bottom) 
		m_bDead = true;
	
}

void CCarrotFollowBullet::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left,								// 2, 3인자 : 복사 받을 위치 좌표
		m_tRect.top,
		(int)m_tInfo.fCX,							// 4,5인자 : 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,										// 현재 그리고자하는 비트맵 이미지 DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX),	// 7,8인자 : 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),
		(int)m_tInfo.fCX,							// 9, 10인자 : 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));							// 제거하고자 하는 색상
}


void CCarrotFollowBullet::Release(void)
{
}

void CCarrotFollowBullet::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BULLET_MONSTER_FOLLOW:
			m_tFrame.Set_Frame(0, 7, 0, 100, GetTickCount());
			break;

			//case BULLET_MONSTER_FOLLOW:
			//	m_tFrame.Set_Frame(0, 8, 0, 100, GetTickCount());
			//	break;
		}
	}
}
