#include "stdafx.h"
#include "Ending.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"


CEnding::CEnding()
{
}


CEnding::~CEnding()
{
	Release();
}

void CEnding::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_FINALBGM);

	m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../Video/Ending.wmv");
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);
	MCIWndPlay(m_hVideo);
}

int CEnding::Update(void)
{
	return 0;
}

void CEnding::Late_Update(void)
{
	if (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo) ||
		CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_MENU); // 로고 끝나면 메인메뉴
		return;
	}
}

void CEnding::Render(HDC hDC)
{


}

void CEnding::Release(void)
{
	MCIWndClose(m_hVideo);
}
