#include "stdafx.h"
#include "DominoThorn.h"
#include "BmpMgr.h"

CDominoThorn::CDominoThorn()
{
}


CDominoThorn::~CDominoThorn()
{
	Release();
}

void CDominoThorn::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/kd_domino_mg_floor_loop.bmp", L"kd_domino_mg_floor_loop");

	//m_tInfo.fX = 700.f;
	//m_tInfo.fY = 700.f;

	m_tInfo.fCX = 262.f;
	m_tInfo.fCY = 144.f;

	m_fSpeed = 5.f;

	m_pFrameKey = L"kd_domino_mg_floor_loop";
	m_eCurState = BULLET_MONSTER_THORN;
	m_ePreState = BULLET_MONSTER_THORN;
	m_tFrame.Set_Frame(0, 0, 0, 100, GetTickCount());

}

int CDominoThorn::Update(void)
{
	Move_Frame();
	Animation_Change();
	Update_Rect();

	m_tInfo.fX -= m_fSpeed;



	return OBJ_NOEVENT;
}

void CDominoThorn::Late_Update(void)
{
}

void CDominoThorn::Render(HDC hDC)
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
		RGB(255, 255, 255));							// 제거하고자 하는 색상

	TCHAR    szBuff[100] = L"";

	RECT rc{ 500, 1, 600, 20 };
	wsprintf(szBuff, L"Thorn X : %d", (int)m_tInfo.fX);
	DrawText(hDC, szBuff, lstrlenW(szBuff), &rc, DT_LEFT | DT_WORDBREAK);

	RECT rc2{ 500, 31, 600, 230 };
	wsprintf(szBuff, L"Thorn Y : %d", (int)m_tInfo.fY);
	DrawText(hDC, szBuff, lstrlenW(szBuff), &rc2, DT_LEFT | DT_WORDBREAK);
}

void CDominoThorn::Release(void)
{
}

void CDominoThorn::Animation_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BULLET_MONSTER_THORN:
			m_tFrame.Set_Frame(0, 0, 0, 200, GetTickCount());
			break;
		}
	}
}
