#include "stdafx.h"
#include "OnionBullet.h"
#include "BmpMgr.h"

COnionBullet::COnionBullet()
{
}


COnionBullet::~COnionBullet()
{
}

void COnionBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_Proj_NonParryableA.bmp", L"Onion_Proj_NonParryableA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_Proj_NonParryableB.bmp", L"Onion_Proj_NonParryableB");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_Proj_NonParryableC.bmp", L"Onion_Proj_NonParryableC");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_Proj_NonParryableD.bmp", L"Onion_Proj_NonParryableD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_Proj_NonParryableE.bmp", L"Onion_Proj_NonParryableE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_Proj_NonParryableASplash.bmp", L"Onion_Proj_NonParryableASplash");

	m_tInfo.fCX = 37.f;
	m_tInfo.fCY = 68.f;

	m_fSpeed = 10.f;
	m_iHp = 1;

	m_pFrameKey = L"Onion_Proj_NonParryableA";
	m_eCurState = BULLET_MONSTER_CRYING;
	m_ePreState = BULLET_MONSTER_CRYING;
	m_tFrame.Set_Frame(0, 2, 0, 200, GetTickCount());
}

int COnionBullet::Update(void)
{
	Move_Frame();
	Animation_Change();
	//m_tInfo.fY = 330;
	m_tInfo.fY += m_fSpeed;
	if (m_iHp <= 0)
	{
		m_bDead = true;
		if (m_bDead)
			return OBJ_DEAD;
	}
	if (m_tInfo.fY > WINCY)
		return OBJ_DEAD;

	
	Update_Rect();

	return  OBJ_NOEVENT;
}

void COnionBullet::Late_Update(void)
{

}
void COnionBullet::Render(HDC hDC)
{
	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left,								// 2, 3���� : ���� ���� ��ġ ��ǥ
		m_tRect.top,
		(int)m_tInfo.fCX,							// 4,5���� : ���� ���� ����, ���� ����
		(int)m_tInfo.fCY,
		hMemDC,										// ���� �׸������ϴ� ��Ʈ�� �̹��� DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX),	// 7,8���� : ��Ʈ���� ����� ���� ��ǥ
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),
		(int)m_tInfo.fCX,							// 9, 10���� : ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));							// �����ϰ��� �ϴ� ����
}

void COnionBullet::Release(void)
{
}

void COnionBullet::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BULLET_MONSTER_CRYING:
			m_tFrame.Set_Frame(0, 3, 0, 100, GetTickCount());
			break;
		}
	}
}
