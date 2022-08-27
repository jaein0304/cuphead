#include "stdafx.h"
#include "Casino2.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Item.h"
#include "SoundMgr.h"


CCasino2::CCasino2()
{
}


CCasino2::~CCasino2()
{
	Release();
}

void CCasino2::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Casino/Diamond2.bmp", L"Diamond");

	//m_tInfo.fX = 200.f;
	//m_tInfo.fY = 400.f;
	//m_tInfo.fCX = 336.f;
	//m_tInfo.fCY = 340.f;

	m_tInfo.fCX = 229.f;
	m_tInfo.fCY = 238.f;

	m_fSpeed = 1.f;

	m_pFrameKey = L"Diamond";
	m_eCurState = CASINO2_MOVE;
	m_ePreState = CASINO2_MOVE;
	m_tFrame.Set_Frame(0, 20, 0, 200, GetTickCount());

	m_iHp = 5;
}

int CCasino2::Update(void)
{
	Move_Frame();
	Update_Rect();
	Animation_Change();


	m_tInfo.fX -= m_fSpeed;


	//hp가 0이하면 
	if (m_iHp <= 0)
	{
		//dead상태로 바꾸고 
		m_bDead = true;

		//죽었을 때 코인 생성
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

void CCasino2::Late_Update(void)
{
}

void CCasino2::Render(HDC hDC)
{
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
}

void CCasino2::Release(void)
{
}

void CCasino2::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CASINO2_MOVE:
			m_tFrame.Set_Frame(0, 20, 0, 100, GetTickCount());
			break;

		}
	}
}
