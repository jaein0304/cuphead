#include "stdafx.h"
#include "Casino.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Item.h"

CCasino::CCasino()
{
}


CCasino::~CCasino()
{
	Release();
}

void CCasino::Initialize(void)
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Casino/Spade.bmp", L"Spade");

	//m_tInfo.fX = 200.f;
	//m_tInfo.fY = 400.f;
	//m_tInfo.fCX = 336.f;
	//m_tInfo.fCY = 340.f;

	m_tInfo.fCX = 229.f;
	m_tInfo.fCY = 240.f;

	m_fSpeed = 2.f;

	m_pFrameKey = L"Spade";
	m_eCurState = CASINO_MOVE;
	m_ePreState = CASINO_MOVE;
	m_tFrame.Set_Frame(0, 20, 0, 100, GetTickCount());

	m_iHp = 5;
}

int CCasino::Update(void)
{
	Move_Frame();
	Update_Rect();
	Animation_Change();


	m_tInfo.fX += m_fSpeed;


	//hp가 0이하면 
	if (m_iHp <= 0)
	{
		//dead상태로 바꾸고 
		m_bDead = true;

		//죽었을 때 코인 랜덤 드랍
		if (m_bDead)
		{
			if (rand() % 2)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"coin_pickup_01.wav", SOUND_EFFECT, 10);
				CObj* pItem = nullptr;
				pItem = CAbstractFactory<CItem>::CreateItem(m_tInfo.fX, m_tInfo.fY, ITEM_1);
				CObjMgr::Get_Instance()->AddObject(OBJ_ITEM, pItem);
				return OBJ_DEAD;
			}
			else
				return OBJ_DEAD;
		}
	}

	return OBJ_NOEVENT;
}

void CCasino::Late_Update(void)
{
	/*if (m_tInfo.fX == 100.f) {
		m_fSpeed -= 1.f;
	}*/
	//원래 100에서 시작한 얘들이 반대편으로 돌아옴;
	if (m_tInfo.fX >= 1600.f)
		m_fSpeed *= -1.f;
	
}

void CCasino::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

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
		RGB(99, 92, 99));

	TCHAR    szBuff[100] = L"";
	swprintf_s(szBuff, L"CardHp : %d", m_iHp);
	TextOut(hDC, 100, 120, szBuff, lstrlen(szBuff));

	RECT rc{ 650, 1, 820, 200 };
	wsprintf(szBuff, L"Card x : %d", (int)m_tInfo.fX);
	DrawText(hDC, szBuff, lstrlenW(szBuff), &rc, DT_LEFT | DT_WORDBREAK);

	RECT rc2{ 650, 31, 820, 230 };
	wsprintf(szBuff, L"Card y : %d", (int)m_tInfo.fY);
	DrawText(hDC, szBuff, lstrlenW(szBuff), &rc2, DT_LEFT | DT_WORDBREAK);

	HBRUSH hBrush1 = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush1 = (HBRUSH)SelectObject(hDC, hBrush1);
	Rectangle(hDC, 20, 560, 120, 580);
	SelectObject(hDC, oldBrush1);
	DeleteObject(hBrush1);

	HBRUSH hBrush2 = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldBrush2 = (HBRUSH)SelectObject(hDC, hBrush2);
	Rectangle(hDC, 20, 560, (30 + m_iHp / 10), 580);
	SelectObject(hDC, oldBrush2);
	DeleteObject(hBrush2);
}

void CCasino::Release(void)
{
}


void CCasino::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CASINO_MOVE:
			m_tFrame.Set_Frame(0, 20, 0, 100, GetTickCount());
			break;

		}
	}
}

