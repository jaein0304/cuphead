#include "stdafx.h"
#include "CasinoKing.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "CDirectionMgr.h"
#include "ObjMgr.h"

CCasinoKing::CCasinoKing()
{
}


CCasinoKing::~CCasinoKing()
{
	Release();
}

void CCasinoKing::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Casino/King_Idle2.bmp", L"King_Idle2");


	m_tInfo.fX = 500.f;
	m_tInfo.fY = 200.f;

	m_tInfo.fCX = 409.f;
	m_tInfo.fCY = 200.f;

	m_pFrameKey = L"King_Idle2";
	m_eCurState = CASINOKING_IDLE;
	m_ePreState = CASINOKING_IDLE;
	m_tFrame.Set_Frame(0, 32, 0, 200, GetTickCount());

}

int CCasinoKing::Update(void)
{
	Move_Frame();
	Update_Rect();
	Animation_Change();

	float Distance = CDirectionMgr::Vector2Distance(VECTOR{ m_tInfo.fX, m_tInfo.fY },
		VECTOR{ CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX,  CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY });

	//플레이어가 가까이왔을 때 움직이게
	if (Distance < 100)
	{
		m_pFrameKey = L"ElderKettle";
		m_eCurState = CASINOKING_IDLE;
		m_ePreState = CASINOKING_IDLE;
		m_tFrame.Set_Frame(0, 2, 1, 200, GetTickCount());
	}

	return OBJ_NOEVENT;
}

void CCasinoKing::Late_Update(void)
{
}

void CCasinoKing::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * int(m_tInfo.fCX),
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),
		m_tInfo.fCX,
		m_tInfo.fCY,
		RGB(99, 92, 99));
}

void CCasinoKing::Release(void)
{
}

void CCasinoKing::Animation_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CASINOKING_IDLE:
			m_tFrame.Set_Frame(0, 1, 0, 200, GetTickCount());
			break;

		case CASINOKING_MOVE:
			m_tFrame.Set_Frame(0, 2, 1, 200, GetTickCount());
			break;
		}
	}
}
