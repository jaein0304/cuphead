#include "stdafx.h"
#include "Obj.h"

float CObj::g_fSound = 0.5f;

CObj::CObj()
	: m_fSpeed(0.f), m_bDead(false), m_bJump(false), m_bGround(false), m_bFall(false), m_GravityTime(0.f)
	, m_bLeft(false), m_bRight(false), m_fOffsetSpeed(0.f), m_eGroup(RENDERID(RENDER_END))
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CObj::CObj(INFO & _Info)
{
	m_tInfo.fX = _Info.fX;
	m_tInfo.fY = _Info.fY;
}


CObj::~CObj()
{
}

void CObj::Gravity()
{
	/*if (m_bGround)
		m_bFall = false;*/

	if (m_bFall)
	{
		float fGravity = (9.8f * m_GravityTime * m_GravityTime) * 0.5f;
		m_tInfo.fY += fGravity;
		m_GravityTime += 0.2f;
	}
	else
		m_GravityTime = 0.f;
}

void CObj::Update_Rect(void)
{
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}


void CObj::Move_Frame(void)
{
	if (m_tFrame.dwSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

bool CObj::Long_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;
			return true;
		}
	}

	return false;
}
