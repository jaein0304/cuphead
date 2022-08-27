#include "stdafx.h"
#include "Domino.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

#include "GemBullet.h"
#include "BirdBullet.h"
#include "DominoThorn.h"
#include "MoveFloor.h"

CDomino::CDomino()
{
}


CDomino::~CDomino()
{
	Release();
}

void CDomino::Initialize(void)
{
	m_tInfo.fX = 600.f;
	m_tInfo.fY = 200.f;
	//m_tInfo.fCX = 400.f;
	//m_tInfo.fCY = 500.f;

	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 600.f;

	m_pFrameKey = L"Domino_Idle";
	m_eCurState = DOMINO_IDLE;
	m_ePreState = DOMINO_IDLE;
	m_tFrame.Set_Frame(0, 15, 0, 100, GetTickCount());

	m_iHp = 30;

	//CObjMgr::Get_Instance()->AddObject(OBJ_DOMINOBULLET1, CreateBullet()); //젬
	//CObjMgr::Get_Instance()->AddObject(OBJ_DOMINOBULLET2, CreateBullet2()); //새

}

int CDomino::Update(void)
{
	Insert_Bmp();
	Move_Frame();
	Update_Rect();
	Animation_Change();


	//DominoFloor();
	DominoThorn();
	DominoGem();
	//DominoBird();
	if (m_dwOldTime + 2000 < GetTickCount())
	{
		m_pFrameKey = L"Domino_Idle";
	}

	
	return OBJ_NOEVENT;
}

void CDomino::DominoGem(void)
{
	if (m_dwOldTime + 10000 < GetTickCount())
	{
		m_pFrameKey = L"Domino_Attack";
		m_eCurState = DOMINO_ATTACK;
		m_ePreState = DOMINO_ATTACK;

		CObjMgr::Get_Instance()->AddObject(OBJ_DOMINOBULLET1, CreateBullet()); //젬
		m_dwOldTime = GetTickCount();
	}
	
}

void CDomino::DominoBird(void)
{
	//if (m_dwOldTime2 + 12000 < GetTickCount())
	//{
	//	CObjMgr::Get_Instance()->AddObject(OBJ_DOMINOBULLET2, CreateBullet2()); //새
	//	m_dwOldTime2 = GetTickCount();
	//}
}

void CDomino::DominoThorn(void)
{
	if (m_dwOldTime3 + 5000 < GetTickCount())
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_DOMINOBULLET3, CreateBullet3()); //바닥
		m_dwOldTime3 = GetTickCount();
	}
}

void CDomino::DominoFloor(void)
{
}

void CDomino::Late_Update(void)
{
}

void CDomino::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

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
		RGB(99, 92, 99));

	TCHAR    szBuff[100] = L"";
	swprintf_s(szBuff, L"DominoHp : %d", m_iHp);
	TextOut(hDC, 20, 40, szBuff, lstrlen(szBuff));
}

void CDomino::Release(void)
{
}

void CDomino::Insert_Bmp(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/Domino_Idle7.bmp", L"Domino_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/Domino_Dead.bmp", L"Domino_Dead");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/Domino_BirdAttack3.bmp", L"Domino_BirdAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Domino/Domino_Attack6.bmp", L"Domino_Attack");

}

void CDomino::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case DOMINO_IDLE:
			m_tFrame.Set_Frame(0, 17, 0, 100, GetTickCount());
			break;

		case DOMINO_ATTACK:
			m_tFrame.Set_Frame(0, 16, 0, 300, GetTickCount());
			break;

		case DOMINO_BIRDATTACK:
			m_tFrame.Set_Frame(0, 22, 0, 200, GetTickCount());
			break;

		case DOMINO_DEAD:
			m_tFrame.Set_Frame(0, 17, 0, 200, GetTickCount());
			break;
		}
	}
}



CObj* CDomino::CreateBullet()
{
	CObj*	 pBullet = CAbstractFactory<CGemBullet>::Create(m_tInfo.fX, m_tInfo.fY);

	return pBullet;
}

CObj* CDomino::CreateBullet2()
{
	CObj*	 pBullet = CAbstractFactory<CBirdBullet>::Create(700, 100);

	return pBullet;
}


CObj* CDomino::CreateBullet3()
{
	CObj*	 pBullet = CAbstractFactory<CDominoThorn>::Create(500, 600);

	return pBullet;
}


CObj* CDomino::CreateBullet4()
{
	CObj*	 pBullet = CAbstractFactory<MoveFloor>::Create(500, 600);

	return pBullet;
}