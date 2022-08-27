#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Obj.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title/StartButton.bmp", L"StartButton");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title/ExitButton.bmp", L"ExitButton");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title/MainMenu_Background.bmp", L"MainMenu_Background");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Title/BackMenu.bmp", L"BackMenu");

	CObj* pObj = CAbstractFactory<CMyButton>::Create(400.f, 200.f);
	pObj->Set_FrameKey(L"StartButton");
	CObjMgr::Get_Instance()->AddObject(OBJ_UI, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(400.f, 250.f);
	pObj->Set_FrameKey(L"ExitButton");
	CObjMgr::Get_Instance()->AddObject(OBJ_UI, pObj);
}

int CMyMenu::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CMyMenu::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

}

void CMyMenu::Render(HDC hDC)
{
	TextOut(hDC, 100, 100, TEXT("메뉴 테스트"), 15);
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BackMenu");

	BitBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);

}

void CMyMenu::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_UI);

}

void CMyMenu::Insert_Bmp(void)
{
}
