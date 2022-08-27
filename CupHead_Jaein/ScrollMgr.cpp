#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr*	 CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

//RootStage
void CScrollMgr::Scroll_Lock(void)
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (-100> m_fScrollX) 
		m_fScrollX = -100;

	if ( 0 > m_fScrollY)
		m_fScrollY = 0;
}

//ElderHouse
void CScrollMgr::Scroll_Lock2(void)
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (100.f < m_fScrollY)
		m_fScrollY = 100.f;

	if (-820.f> m_fScrollX)
		m_fScrollX = -820.f;

	if (-200.f > m_fScrollY)
		m_fScrollY = -200.f;
}

//Tutorial
void CScrollMgr::Scroll_TutorialLock(void)
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY) //À§ 
		m_fScrollY = 0.f;

	if (-4000.f > m_fScrollX)
		m_fScrollX = -4000.f;

	if (-100.f > m_fScrollY)
		m_fScrollY = -100.f;
}

void CScrollMgr::Scroll_DiceHouseLock(void)
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (100.f < m_fScrollY)
		m_fScrollY = 100.f;

	if (-650.f> m_fScrollX)
		m_fScrollX = -650.f;

	if (-200.f > m_fScrollY)
		m_fScrollY = -200.f;
}

void CScrollMgr::Scroll_DominoLock(void)
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (-0> m_fScrollX)
		m_fScrollX = 0;

	if (0 > m_fScrollY)
		m_fScrollY = 0;
}

//FinalStage
void CScrollMgr::Scroll_FinalLock(void)
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (-820.f> m_fScrollX)
		m_fScrollX = -820.f;

	if (-200.f > m_fScrollY)
		m_fScrollY = -200.f;
}