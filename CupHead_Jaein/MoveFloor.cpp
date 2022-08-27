#include "stdafx.h"
#include "MoveFloor.h"
#include "BmpMgr.h"

MoveFloor::MoveFloor()
{
}


MoveFloor::~MoveFloor()
{
	Release();
}

void MoveFloor::Initialize(void)
{
	m_tInfo.fCX = 20000;
	m_tInfo.fCY = 500;
}

int MoveFloor::Update(void)
{
	m_tInfo.fX -= m_fSpeed;
	return OBJ_NOEVENT;
}

void MoveFloor::Late_Update(void)
{
}

void MoveFloor::Render(HDC hDC)
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
		RGB(255, 255, 255));							// �����ϰ��� �ϴ� ����
}

void MoveFloor::Release(void)
{
}

void MoveFloor::Animation_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BULLET_MONSTER_THORN:
			m_tFrame.Set_Frame(0, 0, 0, 200, GetTickCount());
			break;
		}
	}
}
