#include "stdafx.h"
#include "GemBullet.h"
#include "BmpMgr.h"


CGemBullet::CGemBullet()
{
}


CGemBullet::~CGemBullet()
{
}

void CGemBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/Gem_Blue.bmp", L"Gem_Blue");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/Gem_Orange.bmp", L"Gem_Orange");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/Gem_Pink.bmp", L"Gem_Pink");

	m_tInfo.fX = 700.f;
	m_tInfo.fY = 100.f;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_fSpeed = 3.f;

	m_pFrameKey = L"Gem_Blue";
	m_eCurState = BULLET_MONSTER_GEM;
	m_ePreState = BULLET_MONSTER_GEM;
	m_tFrame.Set_Frame(0, 7, 0, 50, GetTickCount());

	m_iHp = 3;
}

int CGemBullet::Update(void)
{
	Move_Frame();
	Animation_Change();
	//m_tInfo.fY -= m_fSpeed; //이거하면 나중에 사라짐 

	//한바퀴돌고 ㅌㅌ
	Action();
	Check_Crash();
	if (m_iHp <= 0)
	{
		m_bDead = true;
		if (m_bDead)
			return OBJ_DEAD;
	}
	Update_Rect();


	return OBJ_NOEVENT;
}

void CGemBullet::Late_Update(void)
{
	

}

void CGemBullet::Action(void)
{
	//공 속도 
	m_tInfo.fX += VectorX * 30.f;
	m_tInfo.fY += VectorY * 30.f;
}

void CGemBullet::Check_Crash()
{
	if (m_tInfo.fX <= 0 || (m_tInfo.fX + diameter) >= 800)
		VectorX *= -1;

	if (m_tInfo.fY <= 0 || (m_tInfo.fY + diameter) >= 600)
		VectorY *= -1;
}

void CGemBullet::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	//Ellipse(hDC, (int)x, (int)y, (int)(x + diameter), (int)(y + diameter));
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
	wsprintf(szBuff, L"Gem X : %d", (int)m_tInfo.fX);
	DrawText(hDC, szBuff, lstrlenW(szBuff), &rc, DT_LEFT | DT_WORDBREAK);

	RECT rc2{ 200, 31, 800, 230 };
	wsprintf(szBuff, L"Gem Y : %d", (int)m_tInfo.fY);
	DrawText(hDC, szBuff, lstrlenW(szBuff), &rc2, DT_LEFT | DT_WORDBREAK);
}

void CGemBullet::Release(void)
{
}

void CGemBullet::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BULLET_MONSTER_GEM:
			m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());
			break;
		}
	}
}
