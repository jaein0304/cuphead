#include "stdafx.h"
#include "MonsterBullet.h"
#include "BmpMgr.h"


CMonsterBullet::CMonsterBullet()
{
}


CMonsterBullet::~CMonsterBullet()
{
	Release();
}

void CMonsterBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Potato/Potato_NonParryable.bmp", L"Potato_NonParryable");

	m_tInfo.fCX = 134.f;
	m_tInfo.fCY = 139.f;

	m_fSpeed = 5.f;

	m_pFrameKey = L"Potato_NonParryable";
	m_eCurState = BULLET_MONSTER_BASIC;
	m_ePreState = BULLET_MONSTER_BASIC;
	m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());
}

int CMonsterBullet::Update(void)
{
	Move_Frame();
	Animation_Change();

	m_tInfo.fX -= m_fSpeed;
	m_tInfo.fY = 520;
	//m_tInfo.fX += m_fSpeed * cosf(m_fAngle *(PI / 180.f));
	//m_tInfo.fY -= m_fSpeed * sinf(m_fAngle *(PI / 180.f));
	//switch (m_eType)
	//{
	//case BULLET_MONSTER_BASIC: //x���Ѿ�
	//	m_tInfo.fX += m_fSpeed;
	//	break;

	//case BULLET_MONSTER_FOLLOW: //����ź
	//	m_tInfo.fX += m_fSpeed * cosf(m_tInfo.fX * (PI / 180));
	//	m_tInfo.fY += m_fSpeed * sinf(m_tInfo.fY * (PI / 180));
	//	break;
	//}
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonsterBullet::Late_Update(void)
{
	

}

void CMonsterBullet::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	/*switch (m_eType)
	{
	case BULLET_MONSTER_BASIC:
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		break;

	case BULLET_MONSTER_FOLLOW:
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		break;
	}*/

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left,					// 2, 3���� : ���� ���� ��ġ ��ǥ
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

void CMonsterBullet::Release(void)
{
}

void CMonsterBullet::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BULLET_MONSTER_BASIC:
			m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());
			break;
		}
	}
}

