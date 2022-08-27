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
		m_tRect.left,								// 2, 3인자 : 복사 받을 위치 좌표
		m_tRect.top,
		(int)m_tInfo.fCX,							// 4,5인자 : 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,										// 현재 그리고자하는 비트맵 이미지 DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX),	// 7,8인자 : 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),
		(int)m_tInfo.fCX,							// 9, 10인자 : 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));							// 제거하고자 하는 색상
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
