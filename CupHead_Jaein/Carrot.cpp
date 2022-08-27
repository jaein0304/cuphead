#include "stdafx.h"
#include "Carrot.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "CarrotBullet.h"
#include "CarrotFollowBullet.h"
#include "SoundMgr.h"

CCarrot::CCarrot()
{
}


CCarrot::~CCarrot()
{
	Release();
}

void CCarrot::Initialize(void)
{
	m_tInfo.fX = 450.f;
	m_tInfo.fY = 250.f;
	m_tInfo.fCX = 400.f;
	m_tInfo.fCY = 400.f;

	m_iHp = 20;

	m_pFrameKey = L"Carrot_Intro";
	m_eCurState = CARROT_INTRO;
	m_ePreState = CARROT_INTRO;
	m_tFrame.Set_Frame(0, 13, 0, 100, GetTickCount());


}

int CCarrot::Update(void)
{
	Insert_Bmp();
	Move_Frame();
	Update_Rect();
	Animation_Change();

	//if (m_bDead)
	//	return OBJ_DEAD;

	if (0 >= m_iHp)
	{
		//CSoundMgr::Get_Instance()->PlaySound(L"Carrot_Die.wav", SOUND_CARROTDIE, 1);
		m_tInfo.fCX = 400.f;
		m_tInfo.fCY = 400.f;
		m_ePreState = CARROT_DEAD;
		m_eCurState = CARROT_DEAD;
		m_pFrameKey = L"Carrot_Death";
	}


	if (m_bCarrotSpread)
		CarrotSpread();
	else if (m_bCarrotBeam)
		CarrotBeam();
	else if (m_bCarrotSpread2)
		CarrotSpread2();
	else if (m_bCarrotBeam2)
		CarrotBeam2();


	return OBJ_NOEVENT;

}

void CCarrot::Late_Update(void)
{
	/*if (100 >= m_tInfo.fX)
		m_fSpeed = -1.f;
	if (WINCX <= m_tInfo.fX)
		m_fSpeed = 1.f;*/
}

void CCarrot::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,								// 2, 3인자 : 복사 받을 위치 좌표
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,										// 4,5인자 : 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,													// 현재 그리고자하는 비트맵 이미지 DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX),				// 7,8인자 : 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),
		(int)m_tInfo.fCX,										// 9, 10인자 : 복사할 비트맵의 가로, 세로 길이 (사이즈 조절 가능, 03.11 한번해보기)
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));


	TCHAR    szBuff[100] = L"";
	swprintf_s(szBuff, L"CarrotHP : %d", m_iHp);
	TextOut(hDC, 20, 40, szBuff, lstrlen(szBuff));

}
void CCarrot::CarrotSpread(void)
{
	//당근 10개 뿌리기  
	if (m_iAttackCount < 10)
	{
		if (m_dwOldTime + 500 < GetTickCount()) // 1600
		{
			//CSoundMgr::Get_Instance()->PlaySound(L"Onion_Die.wav", SOUND_CARROTATTACK1, 1);

			m_tFrame.Set_Frame(0, 3, 0, 100, GetTickCount());
			m_pFrameKey = L"Carrot_Bomb";
			m_eCurState = CARROT_BOMB;
			m_ePreState = CARROT_BOMB;
			m_tInfo.fCX = 400.f;
			m_tInfo.fCY = 400.f;
			CObjMgr::Get_Instance()->AddObject(OBJ_CARROTBULLET1, CreateBullet());
			m_dwOldTime = GetTickCount();
			m_iAttackCount++;
		}
	}
	//만약 당근을 다 뿌리면 원상태로 
	else if (m_iAttackCount >= 10)
	{
		m_bCarrotSpread = false;
	}
}

void CCarrot::CarrotIdle(void)
{
	if (m_dwOldTime + 1000 < GetTickCount())
	{
		m_tFrame.Set_Frame(0, 23, 0, 200, GetTickCount());
		m_pFrameKey = L"Carrot_Idle";
		m_eCurState = CARROT_IDLE;
		m_ePreState = CARROT_IDLE;
	}
	m_bCarrotIdle = false;
}


void CCarrot::CarrotBeam(void)
{
	//유도 레이저
	if (m_iAttackCount2 < 5)
	{
		if (m_dwOldTime + 500 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_CARROTATTACK1);
			CSoundMgr::Get_Instance()->PlaySound(L"Carrot_Beam.wav", SOUND_CARROTATTACK2, 0.5);

			CObj* pObj = nullptr;
			pObj = CAbstractFactory<CCarrotFollowBullet>::Create();
			CObjMgr::Get_Instance()->AddObject(OBJ_CARROTBULLET2, ShotBullet(m_fAngle));

			m_tInfo.fCX = 400.f;
			m_tInfo.fCY = 500.f;
			m_pFrameKey = L"Carrot_ChangeToBeam";
			m_eCurState = CARROT_BEAM;
			m_ePreState = CARROT_BEAM;
			m_tFrame.Set_Frame(0, 8, 0, 50, GetTickCount());

			m_dwOldTime = GetTickCount();
			m_iAttackCount2++;
		}
	}
	//레이저 다 뿌리면 원상태로 
	if (m_iAttackCount2 >= 5)
	{
		m_bCarrotBeam = false;

	}
}

void CCarrot::CarrotSpread2(void)
{
	if (m_iAttackCount3 < 10)
	{
		if (m_dwOldTime + 500 < GetTickCount()) // 1600
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_CARROTATTACK2);
			//CSoundMgr::Get_Instance()->PlaySound(L"Onion_Die.wav", SOUND_CARROTATTACK1, 1);

			m_tFrame.Set_Frame(0, 3, 0, 100, GetTickCount());
			m_pFrameKey = L"Carrot_Bomb";
			m_eCurState = CARROT_BOMB;
			m_ePreState = CARROT_BOMB;
			m_tInfo.fCX = 400.f;
			m_tInfo.fCY = 400.f;
			CObjMgr::Get_Instance()->AddObject(OBJ_CARROTBULLET1, CreateBullet());
			m_dwOldTime = GetTickCount();
			m_iAttackCount3++;
		}
	}
	//만약 당근을 다 뿌리면 원상태로 
	else if (m_iAttackCount3 >= 10)
	{
		m_bCarrotSpread2 = false;
	}
}

void CCarrot::CarrotBeam2(void)
{//유도 레이저
	if (m_iAttackCount4 < 5)
	{
		if (m_dwOldTime + 500 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_CARROTATTACK1);
			CSoundMgr::Get_Instance()->PlaySound(L"Carrot_Beam.wav", SOUND_CARROTATTACK2, 0.5);

			CObj* pObj = nullptr;
			pObj = CAbstractFactory<CCarrotFollowBullet>::Create();
			CObjMgr::Get_Instance()->AddObject(OBJ_CARROTBULLET2, ShotBullet(m_fAngle));

			m_tInfo.fCX = 400.f;
			m_tInfo.fCY = 500.f;
			m_pFrameKey = L"Carrot_ChangeToBeam";
			m_eCurState = CARROT_BEAM;
			m_ePreState = CARROT_BEAM;
			m_tFrame.Set_Frame(0, 8, 0, 50, GetTickCount());

			m_dwOldTime = GetTickCount();
			m_iAttackCount4++;
		}
	}
	//레이저 다 뿌리면 원상태로 
	if (m_iAttackCount4 >= 5)
	{
		m_bCarrotBeam2 = false;

	}
}



void CCarrot::Release(void)
{
}

void CCarrot::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CARROT_INTRO:
			m_tFrame.Set_Frame(0, 23, 0, 200, GetTickCount());
			break;

		case CARROT_IDLE:
			m_tFrame.Set_Frame(0, 23, 0, 200, GetTickCount());
			break;

		case CARROT_BOMB:
			m_tFrame.Set_Frame(0, 3, 0, 100, GetTickCount());
			break;

		case CARROT_BEAM:
			m_tFrame.Set_Frame(0, 8, 0, 100, GetTickCount());
			break;

		case CARROT_DEAD:
			m_tFrame.Set_Frame(0, 8, 0, 100, GetTickCount());
			break;
		}
	}

}

void CCarrot::Insert_Bmp(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Carrot/Carrot_Idle.bmp", L"Carrot_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Carrot/Carrot_Bomb.bmp", L"Carrot_Bomb");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Carrot/Carrot_ChangeToBeam.bmp", L"Carrot_ChangeToBeam");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Carrot/Carrot_Death2.bmp", L"Carrot_Death");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Carrot/Carrot_Intro.bmp", L"Carrot_Intro");

}


CObj * CCarrot::CreateBullet()
{
	CObj*	 pBullet = CAbstractFactory<CCarrotBullet>::Create(rand() % WINCX, 0);

	return pBullet;
}

CObj* CCarrot::ShotBullet(float _fAngle)//, BULLETTYPE_MONSTER eType
{
	CObj*	 pBullet = CAbstractFactory<CCarrotFollowBullet>::Create(m_tInfo.fX, m_tInfo.fY);

	pBullet->Set_Target(CObjMgr::Get_Instance()->Get_Player()); //플레이어 위치 받아오기 (시은)
	pBullet->Set_Angle(_fAngle);


	//if (pBullet->Get_Angle(_fAngle))
	//	pBullet->Set_Dead();
	//dynamic_cast<CCarrotFollowBullet*>(pBullet)->Set_BulletType(eType);
	return pBullet;
}
