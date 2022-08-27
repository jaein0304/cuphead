#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"
#include "Scene.h"


CLine::CLine()
{
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CLine::CLine(LINEINFO & tInfo)
	: m_tInfo(tInfo)
{
}


CLine::CLine(LINEPOS& tLPoint, LINEPOS& tRPoint)
	: m_tInfo(tLPoint, tRPoint)
{

}

CLine::~CLine()
{
}



void CLine::Render(HDC hDC)
{
	//int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	//MoveToEx(hDC, (int)m_tInfo.tLeftPoint.fX + iScrollX, (int)m_tInfo.tLeftPoint.fY + iScrollY, nullptr);
	//LineTo(hDC, (int)m_tInfo.tRightPoint.fX + iScrollX, (int)m_tInfo.tRightPoint.fY + iScrollY);

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CLine::RectSetting()
{
	m_tRect.left = 0;
	m_tRect.top = 500;
	m_tRect.right = 800;
	m_tRect.bottom = 600;
}
