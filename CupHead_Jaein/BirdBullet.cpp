#include "stdafx.h"
#include "BirdBullet.h"
#include "BmpMgr.h"


CBirdBullet::CBirdBullet()
{
}


CBirdBullet::~CBirdBullet()
{
	Release();
}

void CBirdBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/Bird_Left.bmp", L"Bird_Left");

	//m_tInfo.fX = 700.f;
	//m_tInfo.fY = 100.f;

	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 200.f;

	m_fSpeed = 5.f;

	m_pFrameKey = L"Bird_Left";
	m_eCurState = BULLET_MONSTER_BIRD;
	m_ePreState = BULLET_MONSTER_BIRD;
	m_tFrame.Set_Frame(0, 5, 0, 100, GetTickCount());

}

int CBirdBullet::Update(void)
{
	Move_Frame();
	Animation_Change();
	m_tInfo.fX -= m_fSpeed;

	//if(m_tInfo.fX >100)
	//	m_tInfo.fX -= m_fSpeed;


	//if(m_tInfo.fX <= 100) 
	//{
	//	m_tInfo.fY += m_fSpeed;
	//	//m_tInfo.fX = 100;
	//}

	//if (m_tInfo.fX <= 100 && m_tInfo.fY >= 500)
	//{
	//	m_tInfo.fX += m_fSpeed;
	//	//m_tInfo.fY = 500;
	//}
	//else if (m_tInfo.fY >= 500 && m_tInfo.fX <=100)
	//{ 
	//	m_tInfo.fY = 500;
	//	m_tInfo.fX -= m_fSpeed;
	//}
	

	
	/*else if (m_tInfo.fX >=-50)
		m_tInfo.fX -= m_fSpeed;

	if (m_tInfo.fY == 600)
		m_tInfo.fY -= m_fSpeed;

	else if (m_tInfo.fY == -600)
		m_tInfo.fY += m_fSpeed;*/


	Update_Rect();


	return OBJ_NOEVENT;
}

void CBirdBullet::Late_Update(void)
{/*
	if (0 >= m_tRect.left || WINCX <= m_tRect.right)
	{
		m_fSpeed *= -1.f;
	}
*/
	/*if (0 >= m_tRect.left || WINCX <= m_tRect.right|| 100 >= m_tRect.bottom || m_tRect.top > WINCY - 100)
	{
		m_fSpeed *= -1.f; m_tInfo.fY += m_fSpeed;
	}*/
	if (0 >= m_tRect.left)
	{
		m_tInfo.fY += m_fSpeed;
		m_tInfo.fX += m_fSpeed;
	}

	if (500 <= m_tRect.bottom)
	{
		m_tInfo.fX = 100;
		m_tInfo.fY = 500;
		
		m_tInfo.fY -= m_fSpeed;
		m_tInfo.fX += m_fSpeed;
	}
		
	/*if (m_tInfo.fX <= 100)
	{
		m_tInfo.fY += m_fSpeed;
		m_tInfo.fX = 100;
	}

	if (m_tInfo.fX <= 100 && m_tInfo.fY >= 500)
	{
		m_tInfo.fX += m_fSpeed;
		m_tInfo.fY = 500;
		m_tInfo.fX += m_fSpeed;

	}
	else if (m_tInfo.fY >= 500 && m_tInfo.fX <= 100)
	{
		m_tInfo.fY = 500;
		m_tInfo.fX -= m_fSpeed;
	}*/
}

void CBirdBullet::Render(HDC hDC)
{
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
		RGB(99, 92, 99));							// 제거하고자 하는 색상

	TCHAR    szBuff[100] = L"";

	RECT rc{ 200, 1, 800, 20 };
	wsprintf(szBuff, L"Bird X : %d", (int)m_tInfo.fX);
	DrawText(hDC, szBuff, lstrlenW(szBuff), &rc, DT_LEFT | DT_WORDBREAK);

	RECT rc2{ 200, 31, 800, 230 };
	wsprintf(szBuff, L"Bird Y : %d", (int)m_tInfo.fY);
	DrawText(hDC, szBuff, lstrlenW(szBuff), &rc2, DT_LEFT | DT_WORDBREAK);
}

void CBirdBullet::Release(void)
{
}

void CBirdBullet::Animation_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BULLET_MONSTER_BIRD:
			m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());
			break;
		}
	}
}
