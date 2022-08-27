#include "stdafx.h"
#include "Potato.h"
#include "AbstractFactory.h"
#include "MonsterBullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
CPotato::CPotato()
{
}


CPotato::~CPotato()
{
	Release();
}

void CPotato::Initialize(void)
{
	m_tInfo.fX = 600.f;
	m_tInfo.fY = 350.f;
	m_tInfo.fCX = 526.f;
	m_tInfo.fCY = 512.f;

	/*m_tInfo.fCX = 526.f;
	m_tInfo.fCY = 512.f;*/

	m_pFrameKey = L"Potato_Idle";
	m_eCurState = POTATO_IDLE;
	m_ePreState = POTATO_IDLE;
	m_tFrame.Set_Frame(0, 6, 0, 200, GetTickCount());

	m_iHp = 30;

}

int CPotato::Update(void)
{
	Insert_Bmp();
	Move_Frame();
	Update_Rect();

	//if (m_iHp <= 0 || m_bDead == true)
	//{
	//	m_bDead = true;
	//	return OBJ_DEAD;
	//}
	//if (m_bDead)
	//	return OBJ_DEAD;
	
	//감자 4번 공격 
	if (m_iAttackCount < 4)
	{
		if (m_dwOldTime2 + 1000 < GetTickCount())
		{
			if(m_dwOldTime2 + 100 < GetTickCount())
				CObjMgr::Get_Instance()->AddObject(OBJ_POTATOBULLET, CreateBullet());

			CSoundMgr::Get_Instance()->PlaySound(L"Potato_attack.wav", SOUND_POTATOATTACK, 0.5);
			m_tFrame.Set_Frame(0, 6, 0, 100, GetTickCount());
			m_pFrameKey = L"Potato_Spit_Attack";
			m_eCurState = POTATO_ATTACK;
			m_ePreState = POTATO_ATTACK;
			m_dwOldTime2 = GetTickCount();
			m_iAttackCount++;
		}
	}
	//만약 4번을 다 공격했다면 idle 상태로 바꾸고, 3초뒤 공격횟수를 초기화 
	else if (m_iAttackCount >= 4)
	{
		m_pFrameKey = L"Potato_Idle";
		/*m_eCurState = POTATO_IDLE;
		m_ePreState = POTATO_IDLE;*/
		//m_tFrame.Set_Frame(0, 6, 0, 200, GetTickCount());

		if (m_dwOldTime2 + 3000 < GetTickCount())
			m_iAttackCount = 0;
	}

	if (0 >= m_iHp)
	{
		m_tInfo.fCX = 332.f;
		m_tInfo.fCY = 512.f;
		m_ePreState = POTATO_DEAD;
		m_eCurState = POTATO_DEAD;
		m_pFrameKey = L"Potato_Death";
	}
	return OBJ_NOEVENT;
}

CObj* CPotato::CreateBullet()
{
	//CObj*	 pBullet = CAbstractFactory<CBasicBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y);
	CObj*	 pBullet = CAbstractFactory<CMonsterBullet>::Create(m_tInfo.fX - 120, m_tInfo.fY);
	//pBullet->Set_Mine(this);

	return pBullet;
}

void CPotato::Late_Update(void)
{
	Animation_Change();


}

void CPotato::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,					// 2, 3인자 : 복사 받을 위치 좌표
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,							// 4,5인자 : 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,										// 현재 그리고자하는 비트맵 이미지 DC
		m_tFrame.iFrameStart * int(m_tInfo.fCX),	// 7,8인자 : 비트맵을 출력할 시작 좌표
		m_tFrame.iFrameAnimation * int(m_tInfo.fCY),
		(int)m_tInfo.fCX,							// 9, 10인자 : 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	TCHAR    szBuff[100] = L"";
	swprintf_s(szBuff, L"PotatoHp : %d", m_iHp);
	TextOut(hDC, 20, 80, szBuff, lstrlen(szBuff));
}

void CPotato::Release(void)
{
}

void CPotato::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case POTATO_INTRO:
			m_tInfo.fCX = 557.f;
			m_tInfo.fCY = 461.f;
			m_tFrame.Set_Frame(0, 17, 0, 200, GetTickCount());
			break;

		case POTATO_INTRO2:
			m_tInfo.fCX = 526.f;
			m_tInfo.fCY = 512.f;
			m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());
			break;

		case POTATO_IDLE:
			m_tInfo.fCX = 526.f;
			m_tInfo.fCY = 512.f;
			m_tFrame.Set_Frame(0, 6, 0, 200, GetTickCount());
			break;

		case POTATO_ATTACK:
			m_tInfo.fCX = 526.f;
			m_tInfo.fCY = 512.f;
			m_tFrame.Set_Frame(0, 6, 0, 200, GetTickCount());
			break;

		case POTATO_DEAD:
			m_tFrame.Set_Frame(0, 8, 0, 100, GetTickCount());
			//CBmpMgr::Get_Instance()->Find_Image(L"Carrot");
			break;
		}
	}
}


void CPotato::Insert_Bmp(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Potato/Potato_Death.bmp", L"Potato_Death");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Potato/Potato_Idle.bmp", L"Potato_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Potato/Potato_Intro.bmp", L"Potato_Intro");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Potato/Potato_Intro_Earth.bmp", L"Potato_Intro_Earth");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Potato/Potato_NonParryable.bmp", L"Potato_NonParryable");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Potato/Potato_Spit_Attack3.bmp", L"Potato_Spit_Attack");
}

