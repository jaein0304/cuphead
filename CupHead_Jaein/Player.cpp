#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "BasicBullet.h"
#include "SuperBullet.h"
#include "FollowBullet.h"
#include "RedBullet.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	Insert_Bmp();
	Insert_Sound();
	m_tInfo.fX = 300.f;
	m_tInfo.fY = 550.f;

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 155.f;

	m_fSpeed = 8.f;
	//m_fOffsetSpeed = m_fSpeed;

	m_fJumpPower = -2.0f;
	m_fJumpTime = 0.f;

	m_pFrameKey = L"Player_IDLE";
	m_eCurState = IDLE;
	m_ePreState = IDLE;
	m_tFrame.Set_Frame(0, 4, 0, 200, GetTickCount());

	
	m_iHp = 100;
	m_eGroup = RENDER_GAMEOBJECT;

	//m_tInfo.iAttack = 1;

	//총알 체크, 시연 시 지우기 
	m_fDiagonal = 50.f;


}

int CPlayer::Update(void)
{
	Key_Input();
	Jump();
	Offset();
	Move_Frame();
	Update_Rect();

	if (m_iHp <= 0 || m_bDead == true)
	{
		m_bDead = true;
		return OBJ_DEAD;
	}

	/*if (m_iHp <= 0)
		return OBJ_DEAD;*/

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{

	//m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf(m_fAngle * (PI / 180.f)));
	//m_tPosin.y = long(m_tInfo.fY - m_fDiagonal * sinf(m_fAngle * (PI / 180.f)));
	
	Animation_Change();

}

void CPlayer::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
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
		RGB(99, 92, 99));							// 제거하고자 하는 색상

	if (0 == m_iHp)
		CSceneMgr::Get_Instance()->Set_Scene(SC_MENU);


	//temp, 총알 위치 보기 위함
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, m_tPosin.x, m_tPosin.y);


	//temp, 체력바 
	TCHAR    szBuff[100] = L"";
	swprintf_s(szBuff, L"HP : %d", m_iHp);
	TextOut(hDC, 20, 20, szBuff, lstrlen(szBuff));

	RECT rc{ 650, 1, 820, 200 };
	wsprintf(szBuff, L"Player x : %d", (int)m_tInfo.fX);
	DrawText(hDC, szBuff, lstrlenW(szBuff), &rc, DT_LEFT | DT_WORDBREAK);

	RECT rc2{ 650, 31, 820, 230 };
	wsprintf(szBuff, L"Player y : %d", (int)m_tInfo.fY);
	DrawText(hDC, szBuff, lstrlenW(szBuff), &rc2, DT_LEFT | DT_WORDBREAK);

	HBRUSH hBrush1 = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush1 = (HBRUSH)SelectObject(hDC, hBrush1);
	Rectangle(hDC, 20, 560, 120, 580);
	SelectObject(hDC, oldBrush1);
	DeleteObject(hBrush1);

	HBRUSH hBrush2 = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldBrush2 = (HBRUSH)SelectObject(hDC, hBrush2);
	Rectangle(hDC, 20, 560, (20 + m_iHp ), 580);
	SelectObject(hDC, oldBrush2);
	DeleteObject(hBrush2);
}

void CPlayer::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);

}

void CPlayer::Key_Input(void)
{
	/*if (GetAsyncKeyState == false)
	{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 155.f;
	m_pFrameKey = L"Player_IDLE";
	m_eCurState = IDLE;
	}*/

	if (GetAsyncKeyState('H') & 0x0001)
		m_iHp -= 1;

	if (GetAsyncKeyState('J') & 0x0001)
		m_iHp += 1;

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_fAngle = 180;
		m_tInfo.fCX = 137.f;
		m_tInfo.fCY = 168.f;
		m_pFrameKey = L"Player_LRUN";
		m_tInfo.fX -= m_fSpeed;
		m_eCurState = LRUN;
		m_eDir = DIR_LEFT;

	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_LEFT))
	{

		m_fAngle = 180;
		m_tInfo.fCX = 137.f;
		m_tInfo.fCY = 168.f;
		m_pFrameKey = L"Player_LRUN";
		m_tInfo.fX -= m_fSpeed;
		m_eCurState = IDLE;
		m_eDir = DIR_LEFT;

	}
	if (GetAsyncKeyState(VK_RIGHT))
	{

		//m_fAngle += 5.f;
		m_fAngle = 0;
		m_tInfo.fCX = 137.f;
		m_tInfo.fCY = 168.f;
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"Player_RRUN";
		m_eCurState = RRUN;
		m_eDir = DIR_RIGHT;

	}
	if (GetAsyncKeyState(VK_UP))
	{
		m_fAngle = 90;
		m_tInfo.fCX = 108.f;
		m_tInfo.fCY = 175.f;
		m_pFrameKey = L"Player_AIMUP";
		m_eCurState = AIMUP;
		m_eDir = DIR_UP;

		//m_tInfo.fY -= m_fSpeed;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fCX = 168.f;
		m_tInfo.fCY = 122.f;
		m_pFrameKey = L"RDuckIdle";
		m_eCurState = RDUCKIDLE;
		//m_tInfo.fY += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN) && GetAsyncKeyState('X'))
	{
		m_tInfo.fCX = 193.f;
		m_tInfo.fCY = 81.f;
		m_pFrameKey = L"RDuckShoot";
		m_eCurState = RDUCKSHOOT;
	}

	if (GetAsyncKeyState(VK_UP) && GetAsyncKeyState('X'))
	{
		if (dwOldTime + 190 < GetTickCount())
		{
		m_fAngle = 90;
		m_tInfo.fCX = 108.f;
		m_tInfo.fCY = 175.f;
		m_pFrameKey = L"Player_UPSHOOT";
		m_eCurState = UPSHOOT;
		CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CreateBullet(m_fAngle));
		dwOldTime = GetTickCount();
		}
	}

	if (GetAsyncKeyState('Z'))
	{
		m_bJump = true;
		m_tInfo.fCX = 88.f;
		m_tInfo.fCY = 104.f;
		m_pFrameKey = L"Player_RJUMP";
		m_eCurState = RJUMP;
		//CSoundMgr::Get_Instance()->PlaySound(L"player_jump.wav", SOUND_PLAYER, 10); 
	}

	//점프
	if (CKeyMgr::Get_Instance()->Key_Down('Z'))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"player_jump.wav", SOUND_PLAYER, 10);
		m_eCurState = IDLE;
	}
	
	//공격
	if (GetAsyncKeyState('X'))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"player_default_fire.mp3", SOUND_PLAYER, 10);
		if (dwOldTime + 190 < GetTickCount())
		{
			m_tInfo.fCX = 137.f;
			m_tInfo.fCY = 170.f;
			if(m_fAngle==0)
			{
				m_pFrameKey = L"Player_SHOOT";
				m_eCurState = RSHOOT;
			}
			if (m_fAngle == 180)
			{
				m_pFrameKey = L"Player_SHOOT";
				m_eCurState = LSHOOT;
			}
			if (m_fAngle == 90)
			{
				m_tInfo.fCX = 118.f;
				m_tInfo.fCY = 189.f;
				m_pFrameKey = L"Player_UPSHOOT";
				m_eCurState = UPSHOOT;
			}
			CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, CreateBullet(m_fAngle));
			dwOldTime = GetTickCount();
		}
	}


	if (GetAsyncKeyState('C'))
	{
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 155.f;
		m_pFrameKey = L"Player_IDLE";
		m_eCurState = IDLE;
	}

	if (GetAsyncKeyState('N'))
	{
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 155.f;
		m_pFrameKey = L"Player_IDLE";
		m_eCurState = LIDLE;
	}

	if (GetAsyncKeyState('F'))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"player_default_spread_fire.mp3", SOUND_PLAYER, 10);

		if (dwOldTime + 190 < GetTickCount())
		{
			m_tInfo.fCX = 137.f;
			m_tInfo.fCY = 170.f;
			if (m_fAngle == 0)
			{
				m_pFrameKey = L"Player_SHOOT";
				m_eCurState = RSHOOT;
			}
			if (m_fAngle == 180)
			{
				m_pFrameKey = L"Player_SHOOT";
				m_eCurState = LSHOOT;
			}
			if (m_fAngle == 90)
			{
				m_tInfo.fCX = 118.f;
				m_tInfo.fCY = 189.f;
				m_pFrameKey = L"Player_UPSHOOT";
				m_eCurState = UPSHOOT;
			}
			CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, RedBullet(m_fAngle + 15));
			CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, RedBullet(m_fAngle));
			CObjMgr::Get_Instance()->AddObject(OBJ_BULLET, RedBullet(m_fAngle - 15));

			dwOldTime = GetTickCount();
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('V'))
	{
		if (dwOldTime + 190 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->PlaySound(L"player_specialattack.wav", SOUND_PLAYER, 10);

			if (m_fAngle == 0)
			{
				m_tInfo.fCX = 190.f;
				m_tInfo.fCY = 150.f;
				m_pFrameKey = L"GroundSpecialAttack";
				m_eCurState = RSPECIALSHOOT;
				CObjMgr::Get_Instance()->AddObject(OBJ_SUPERBULLET, CreateSuperBullet(m_fAngle));
				dwOldTime = GetTickCount();
			}
			if (m_fAngle == 180)
			{
				m_tInfo.fCX = 190.f;
				m_tInfo.fCY = 150.f;
				m_pFrameKey = L"GroundSpecialAttack";
				m_eCurState = LSPECIALSHOOT;
				CObjMgr::Get_Instance()->AddObject(OBJ_SUPERBULLET, CreateSuperBullet(m_fAngle));
				dwOldTime = GetTickCount();
			}
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Up('V'))
				m_eCurState = IDLE;

}

CObj* CPlayer::CreateBullet(float _fAngle)
{
	//CObj*	 pBullet = CAbstractFactory<CBasicBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y);
	CObj*	 pBullet = CAbstractFactory<CBasicBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	pBullet->Set_Angle(_fAngle);

	return pBullet;
}

CObj* CPlayer::CreateSuperBullet(float _fAngle)
{
	//CObj*	 pBullet = CAbstractFactory<CBasicBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y);
	CObj*	 pBullet = CAbstractFactory<SuperBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	pBullet->Set_Angle(_fAngle);

	return pBullet;
}

CObj* CPlayer::CreateFollowBullet(float _fAngle)
{
	//CObj*	 pBullet = CAbstractFactory<CBasicBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y);
	CObj*	 pBullet = CAbstractFactory<CFollowBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	pBullet->Set_Angle(_fAngle);

	return pBullet;
}

CObj* CPlayer::RedBullet(float _fAngle)
{
	//CObj*	 pBullet = CAbstractFactory<CBasicBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y);
	CObj*	 pBullet = CAbstractFactory<CRedBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	pBullet->Set_Angle(_fAngle);

	return pBullet;
}
void CPlayer::Jump(void)
{
	if (!m_bJump) return; //점프2번방지, 근데 이거 하면 아래로 내려갈때 점프해야댐 

	if (JumpCheck())
	{
		m_fJumpTime = 0.f;
		if (m_bJump)
		{
			m_fDirY = m_fJumpPower;
			m_bJump = false;
		}
		else
		{
			m_fDirY = 0.f;
		}
	}
	else
	{
		m_fDirY += 0.98f * m_fJumpTime;
		 //m_fDirY += 0.5f * m_fJumpTime;
		m_fJumpTime += 0.01f;
	}
	m_fDirX = 0.f; //이거 1로하면 오른쪽으로 자동이동, 도미노 몬스터 할 때 사용 
				   //m_tInfo.fX += m_fSpeed*m_fDirX;
	m_tInfo.fY += m_fSpeed*m_fDirY;
}

void CPlayer::Offset(void)
{
	int		iOffSetMaxX = 200;
	int		iOffSetMinX = 600;
	int		iOffSetMaxY = 300;
	int		iOffSetMinY = 400;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffSetMaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffSetMinX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetMaxY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffSetMinY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

bool CPlayer::JumpCheck()
{
	for (auto& pBlock : CObjMgr::Get_Instance()->Get_Tile())
	{
		float fX = 0.f, fY = 0.f;

		if (CCollisionMgr::Check_Rect(this, pBlock, &fX, &fY))
		{
			if (fX > fY)
			{
				// 상
				if (this->Get_Info().fY < pBlock->Get_Info().fY)
				{
					this->Set_PosY(-fY);
					return true;
				}
				// 하
				else
				{
					this->Set_PosY(fY);
				}
			}
			else
			{
				// 좌
				if (this->Get_Info().fX < pBlock->Get_Info().fX)
				{
					this->Set_PosX(-fX);
				}
				// 우
				else
				{
					this->Set_PosX(fX);
				}
			}
		}
	}
	return false;
}

void CPlayer::Animation_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.Set_Frame(0, 4, 0, 200, GetTickCount());
			break;

		case LIDLE:
			m_tFrame.Set_Frame(0, 4, 1, 200, GetTickCount());
			break;

		case LRUN:
			m_tFrame.Set_Frame(0, 17, 0, 200, GetTickCount());
			break;

		case RRUN:
			m_tFrame.Set_Frame(0, 17, 0, 200, GetTickCount());
			break;

		case RJUMP:
			m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());
			break;

		case RDASH:
			m_tFrame.Set_Frame(0, 7, 0, 200, GetTickCount());
			break;

		case LDASH:
			m_tFrame.Set_Frame(0, 7, 1, 200, GetTickCount());
			break;

		case RDUCKSHOOT:
			m_tFrame.Set_Frame(0, 5, 0, 200, GetTickCount());
			break;

		case RDUCKIDLE:
			m_tFrame.Set_Frame(0, 12, 0, 200, GetTickCount());
			break;

		case AIMUP:
			m_tFrame.Set_Frame(0, 4, 0, 200, GetTickCount());
			break;

		case LSHOOT:
			m_tFrame.Set_Frame(0, 5, 1, 30, GetTickCount());
			break;

		case RSHOOT:
			m_tFrame.Set_Frame(0, 5, 0, 30, GetTickCount());
			break;

		case UPSHOOT:
			m_tFrame.Set_Frame(0, 5, 0, 30, GetTickCount());
			break;

		case RSPECIALSHOOT:
			m_tFrame.Set_Frame(0, 12, 0, 50, GetTickCount());
			break;

		case LSPECIALSHOOT:
			m_tFrame.Set_Frame(0, 12, 1, 50, GetTickCount());
			break;

		case HIT:
			m_tFrame.Set_Frame(0, 5, 0, 200, GetTickCount());
			break;

		case DEAD:
			m_tFrame.Set_Frame(0, 15, 0, 200, GetTickCount());
			break;
		}

		m_ePreState = m_eCurState;
	}

}

void CPlayer::Insert_Bmp(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_IDLE.bmp", L"Player_IDLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_HIT.bmp", L"Player_HIT");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_JUMP.bmp", L"Player_JUMP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RJUMP.bmp", L"Player_RJUMP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LJUMP.bmp", L"Player_LJUMP");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LRUN.bmp", L"Player_LRUN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RRUN.bmp", L"Player_RRUN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DASH.bmp", L"Player_DASH");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LDuckIdle.bmp", L"LDuckIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RDuckIdle.bmp", L"RDuckIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LDuckShoot.bmp", L"LDuckShoot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RDuckShoot.bmp", L"RDuckShoot");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_AIM.bmp", L"Player_AIM");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_AIMUP.bmp", L"Player_AIMUP");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UPSHOOT.bmp", L"Player_UPSHOOT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RUNSHOOT.bmp", L"Player_RUNSHOOT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_SHOOT.bmp", L"Player_SHOOT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/GroundSpecialAttack.bmp", L"GroundSpecialAttack");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DIE.bmp", L"Player_DIE");

	//총알
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletDeath.bmp", L"BulletDeath");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletLeftRight.bmp", L"BulletLeftRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletStart.bmp", L"BulletStart");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletUpDown.bmp", L"BulletUpDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletUpLeftRight.bmp", L"BulletUpLeftRight");

}

void CPlayer::Insert_Sound(void)
{	
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Player/player_attack.wav", SOUND_PLAYER, 5);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Player/player_damage.wav", SOUND_PLAYER, 5);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Player/player_dash.wav", SOUND_PLAYER, 5);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Player/player_death.wav", SOUND_PLAYER, 5);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Player/player_gameover.wav", SOUND_PLAYER, 5);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Player/player_hit.wav", SOUND_PLAYER, 5);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Player/player_jump.wav", SOUND_PLAYER, 5);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Player/player_map_walk.wav", SOUND_PLAYER, 5);

}

