#include "stdafx.h"
#include "Item.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"


CItem::CItem()
{
}


CItem::~CItem()
{
}

void CItem::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Object/Coin3.bmp", L"Coin");

	/*m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;*/

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 150.f;

	m_bDead = false;
	m_bState = false;

	m_pFrameKey = L"Coin";
	m_eCurState = IDLE;
	m_ePreState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.iFrameAnimation = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();

}

int CItem::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	Move_Frame();
	Update_Rect();

	if (m_bState)
	{
		m_eCurState = DEAD;
		m_pFrameKey = L"Coin";
	}
	else
	{
		m_eCurState = IDLE;
		m_pFrameKey = L"Coin";

	}

	return OBJ_NOEVENT;
}

void CItem::Late_Update(void)
{
	Animation_Change();
}

void CItem::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	switch (m_tItemType)
	{
	case ITEM_1:
	{
		//HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Carrot");
		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			m_tFrame.iFrameStart * int(m_tInfo.fCX),
			m_tFrame.iFrameAnimation * int(m_tInfo.fCY),
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 252, 0));
	}
	break;
	}
}
void CItem::Release(void)
{
}

void CItem::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameAnimation = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iFrameAnimation = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}
