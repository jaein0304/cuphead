#include "stdafx.h"
#include "Onion.h"
#include "AbstractFactory.h"
#include "OnionBullet.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

COnion::COnion()
{
}


COnion::~COnion()
{
	Release();
}

void COnion::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 330.f;
	m_tInfo.fCX = 350.f;
	m_tInfo.fCY = 400.f;

	m_pFrameKey = L"Onion_Idle";
	m_eCurState = ONION_IDLE;
	m_ePreState = ONION_IDLE;
	m_tFrame.Set_Frame(0, 13, 0, 100, GetTickCount());

	m_iHp = 30;

	//m_eGroup = RENDER_GAMEOBJECT;
}

int COnion::Update(void)
{
	Insert_Bmp();
	Move_Frame();
	Update_Rect();

	//생성 후 5초까지 idle 상태 
	if (m_dwOldTime + 3000 < GetTickCount())
	{
		//0.5초 간격으로 울어 
		if (m_dwOldTime2 + 500 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Onion_Crying.wav", SOUND_ONIONATTACK, 0.5);
			m_tFrame.Set_Frame(0, 7, 0, 100, GetTickCount());
			m_pFrameKey = L"Onion_Attack";
			m_eCurState = ONION_ATTACK;
			m_ePreState = ONION_ATTACK;
			CObjMgr::Get_Instance()->AddObject(OBJ_ONIONBULLET, CreateBullet());
			m_dwOldTime2 = GetTickCount();
		}
	}

	if (0 >= m_iHp)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_ONIONATTACK);
		//CSoundMgr::Get_Instance()->PlaySound(L"Onion_Die.wav", SOUND_ONIONDIE, 1);

		m_tInfo.fCX = 350.f;
		m_tInfo.fCY = 400.f;
		m_ePreState = ONION_DEAD;
		m_eCurState = ONION_DEAD;
		m_pFrameKey = L"Onion_Death";

	}

	return OBJ_NOEVENT;
}

void COnion::Late_Update(void)
{
	Animation_Change();

}

void COnion::Render(HDC hDC)
{
	//스크롤 안하면 양파도 같이 움직임 
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
	swprintf_s(szBuff, L"OnionHP : %d", m_iHp);
	TextOut(hDC, 20, 40, szBuff, lstrlen(szBuff));
}

void COnion::Release(void)
{
	
}


void COnion::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ONION_INTRO:
			m_tFrame.Set_Frame(0, 23, 0, 200, GetTickCount());
			break;

		case ONION_IDLE:
			m_tFrame.Set_Frame(0, 17, 0, 200, GetTickCount());
			break;

		case ONION_ATTACK:
			m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());
			break;

		case ONION_ATTACK2:
			m_tFrame.Set_Frame(0, 7, 1, 200, GetTickCount());
			break;

		case ONION_DEAD:
			m_tFrame.Set_Frame(0, 31, 0, 200, GetTickCount());
			break;
		}
	}

}

void COnion::Insert_Bmp(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_Attack.bmp", L"Onion_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_BeforeAttack.bmp", L"Onion_BeforeAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_ChangeToAttack.bmp", L"Onion_ChangeToAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_Death.bmp", L"Onion_Death");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_Idle.bmp", L"Onion_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_Intro.bmp", L"Onion_Intro");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_Tears.bmp", L"Onion_Tears");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Root/Onion/Onion_TearSplash_black.bmp", L"Onion_TearSplash_black");


}

CObj * COnion::CreateBullet()
{
	CObj*	 pBullet = CAbstractFactory<COnionBullet>::Create(rand() % WINCX, 0);
	//pBullet->Set_PosX(rand() % WINCX);
	pBullet->Set_Mine(this);
	return pBullet;

	/*for (int i = 0; i < 5; ++i)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(float(rand() % WINCX), float(rand() % WINCY)));
	}*/
}
