#include "stdafx.h"
#include "ElderKettle.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "CDirectionMgr.h"
#include "ObjMgr.h"

CElderKettle::CElderKettle()
{
}


CElderKettle::~CElderKettle()
{
	Release();
}

void CElderKettle::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/House/ElderKettle.bmp", L"ElderKettle");


	m_tInfo.fX = 1370.f;
	m_tInfo.fY = 550.f;
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 300.f;

	m_pFrameKey = L"ElderKettle";
	m_eCurState = ELDER_IDLE;
	m_ePreState = ELDER_IDLE;
	m_tFrame.Set_Frame(0, 1, 0, 200, GetTickCount());


}

int CElderKettle::Update(void)
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
		m_eCurState = ELDER_MOVE;
		m_ePreState = ELDER_MOVE;
		m_tFrame.Set_Frame(0, 2, 1, 200, GetTickCount());
	}

	return OBJ_NOEVENT;
}

void CElderKettle::Late_Update(void)
{

}

void CElderKettle::Render(HDC hDC)
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

void CElderKettle::Release(void)
{
}

void CElderKettle::Animation_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ELDER_IDLE:
			m_tFrame.Set_Frame(0, 1, 0, 200, GetTickCount());
			break;

		case ELDER_MOVE:
			m_tFrame.Set_Frame(0, 2, 1, 200, GetTickCount());
			break;
		}
	}
}
