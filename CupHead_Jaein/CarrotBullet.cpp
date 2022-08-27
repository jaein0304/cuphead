#include "stdafx.h"
#include "CarrotBullet.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

CCarrotBullet::CCarrotBullet()
{
}


CCarrotBullet::~CCarrotBullet()
{
}

void CCarrotBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Carrot/Carrot_Missile.bmp", L"Carrot_Missile");

	m_tInfo.fX = 100;
	m_tInfo.fCX = 82.f;
	m_tInfo.fCY = 137.f;

	m_fSpeed = 10.f;

	m_pFrameKey = L"Carrot_Missile";
	m_eCurState = BULLET_MONSTER_CARROTBOMB;
	m_ePreState = BULLET_MONSTER_CARROTBOMB;
	m_tFrame.Set_Frame(0, 2, 0, 200, GetTickCount());
}

int CCarrotBullet::Update(void)
{
	Move_Frame();
	Animation_Change();

	m_tInfo.fY += m_fSpeed;
	//m_tInfo.fX -=5;
	Update_Rect();

	/*if (m_iAttackCount < 5)
	{
		if (m_dwOldTime + 1000 < GetTickCount())
		{
			m_tFrame.Set_Frame(0, 3, 0, 100, GetTickCount());
			m_pFrameKey = L"Carrot_Bomb";
			m_eCurState = BULLET_MONSTER_CARROTBOMB;
			m_ePreState = BULLET_MONSTER_CARROTBOMB;
			CObjMgr::Get_Instance()->AddObject(OBJ_CARROTBULLET1, CreateBullet());
			m_dwOldTime = GetTickCount();
			m_iAttackCount++;
		}
	}*/

	return  OBJ_NOEVENT;
}

void CCarrotBullet::Late_Update(void)
{
}

void CCarrotBullet::Render(HDC hDC)
{
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

void CCarrotBullet::Release(void)
{
}

void CCarrotBullet::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BULLET_MONSTER_CARROTBOMB:
			m_tFrame.Set_Frame(0, 5, 0, 100, GetTickCount());
			break;

			//case BULLET_MONSTER_FOLLOW:
			//	m_tFrame.Set_Frame(0, 8, 0, 100, GetTickCount());
			//	break;
		}
	}
}

CObj * CCarrotBullet::CreateBullet()
{
	CObj*	 pBullet = CAbstractFactory<CCarrotBullet>::Create(m_tInfo.fX += 100, 0);

	return pBullet;
}
