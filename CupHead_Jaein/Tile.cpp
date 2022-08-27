#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CTile::CTile()
	:m_eType(GREEN)
{
}

CTile::CTile(INFO & _Info)
	: m_eType(GREEN)
{
	m_tInfo.fX = _Info.fX;
	m_tInfo.fY = _Info.fY;
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_eType = GREEN;
	m_bMouseOver = false;
	m_bSelect = false;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CTile::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update(void)
{
}

void CTile::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_bSelect)
	{
		HDC hMemDC = nullptr;

		if(GREEN == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"GreenTile");
		else if(RED == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"RedTile");
		else if (PURPLE == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PurPleTile");
		else if (PEBBLE == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PebbleTile");
		else if (BLUE == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BlueTile");
		else if (VIOLET == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"VioletTile");

		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,		// 2, 3���� : ���� ���� ��ġ ��ǥ
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,				// 4,5���� : ���� ���� ����, ���� ����
			(int)m_tInfo.fCY,
			hMemDC,							// ���� �׸������ϴ� ��Ʈ�� �̹��� DC
			0,								// 7,8���� : ��Ʈ���� ����� ���� ��ǥ
			0,
			(int)m_tInfo.fCX,				// 9, 10���� : ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����
	}
	else if (m_bMouseOver)
	{
		HDC hMemDC = nullptr;

		if (GREEN == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"GreenTile");
		else if (RED == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"RedTile");
		else if (PURPLE == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PurPleTile");
		else if (PEBBLE == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PebbleTile");
		else if (BLUE == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BlueTile");
		else if (VIOLET == m_eType)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"VioletTile");

		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,		// 2, 3���� : ���� ���� ��ġ ��ǥ
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,				// 4,5���� : ���� ���� ����, ���� ����
			(int)m_tInfo.fCY,
			hMemDC,							// ���� �׸������ϴ� ��Ʈ�� �̹��� DC
			0,								// 7,8���� : ��Ʈ���� ����� ���� ��ǥ
			0,
			(int)m_tInfo.fCX,				// 9, 10���� : ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����


		//HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255)); // �����
		//HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);//�漱��

		//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

		//hPen = (HPEN)::SelectObject(hDC, hOldPen);//�漱��
		//DeleteObject(hPen);  //�����
	}
	else
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CTile::Release(void)
{
}
