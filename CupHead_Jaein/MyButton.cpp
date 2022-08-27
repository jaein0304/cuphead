#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize(void)
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 30.f;

	m_eGroup = RENDER_UI;
}

int CMyButton::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{
	//마우스 가져오기
	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//PtInRect : Rect안에 존재하는지 검사 
	if (PtInRect(&m_tRect, pt))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"player_map_walk.wav", SOUND_EFFECT, 10);

		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!(lstrcmp(L"StartButton", m_pFrameKey)))
			{
				CSceneMgr::Get_Instance()->Set_Scene(SC_ELDERHOUSE);
			}

			else if (!(lstrcmp(L"ExitButton", m_pFrameKey)))
				DestroyWindow(g_hWnd);

			return;
		}
		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;
}

void CMyButton::Render(HDC hDC)
{
	HDC	hButtonDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hButtonDC,
		(int)m_tInfo.fCX * m_iDrawID,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(9, 9, 9));

}

void CMyButton::Release(void)
{
}
