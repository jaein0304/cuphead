#include "stdafx.h"
#include "Title.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CTitle::CTitle()
{
}


CTitle::~CTitle()
{
	Release();
}

void CTitle::Initialize(void)
{
	m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../Video/CupheadSong.wmv");
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);
	MCIWndPlay(m_hVideo);

}

int CTitle::Update(void)
{
	return 0;
}

void CTitle::Late_Update(void)
{
	if (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo) ||
		CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_MENU); // 로고 끝나면 메인메뉴
		return;
	}
}

void CTitle::Render(HDC hDC)
{
	

}

void CTitle::Release(void)
{
	MCIWndClose(m_hVideo);

}

void CTitle::Insert_Bmp(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title/StartScene_CupHead.bmp", L"StartScene_CupHead");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title/StartScene_Cup&Mug.bmp", L"StartScene_Cup&Mug");
}
