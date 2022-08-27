#include "stdafx.h"
#include "KingDice.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CDirectionMgr.h"
#include "ObjMgr.h"

CKingDice::CKingDice()
{
}


CKingDice::~CKingDice()
{
}

void CKingDice::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/House/KingDice.bmp", L"KingDice");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/House/KingDice2.bmp", L"KingDice2");

	m_tInfo.fX = 1200.f;
	m_tInfo.fY = 500.f;
	m_tInfo.fCX = 426.f;
	m_tInfo.fCY = 400.f;

	m_pFrameKey = L"KingDice";
	m_eCurState = KINGDICE_IDLE;
	m_ePreState = KINGDICE_IDLE;
	m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());

}

int CKingDice::Update(void)
{
	Move_Frame();
	Update_Rect();
	Animation_Change();

	float Distance = CDirectionMgr::Vector2Distance(VECTOR{ m_tInfo.fX, m_tInfo.fY },
		VECTOR{ CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX,  CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY });

	//플레이어가 가까이왔을 때 움직이게
	if (Distance < 200)
	{
		m_tInfo.fCX = 448.f;
		m_tInfo.fCY = 400.f;

		m_pFrameKey = L"KingDice2";
		m_eCurState = KINGDICE_MOVE;
		m_ePreState = KINGDICE_MOVE;
	}
	
	return OBJ_NOEVENT;
}

void CKingDice::Late_Update(void)
{
}

void CKingDice::Render(HDC hDC)
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

void CKingDice::Release(void)
{
}

void CKingDice::Animation_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case KINGDICE_IDLE:
			m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());
			break;

		case KINGDICE_MOVE:
			m_tFrame.Set_Frame(0, 9, 0, 200, GetTickCount());
			break;
		}
	}
}
