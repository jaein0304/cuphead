#include "stdafx.h"
#include "MyBmp.h"


CMyBmp::CMyBmp()
{
}


CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : ȭ�� DC�� ���ͼ� �̸� �ؽ�ó �׷��� DC�� ����� �ش�.

	m_hMemDC = CreateCompatibleDC(hDC);	// ���� DC�� ���ͼ� �׸��� �غ� �ϱ� ���� ����

	m_hBitmap = (HBITMAP)LoadImage(nullptr,		// ���α׷��� �ν��Ͻ� �ڵ�, �̹����� ���α׷����� ������ ���� �ƴ� ���Ϸκ��� �о���̱� ������ NULL�� ����
		pFilePath,	// ������ ���
		IMAGE_BITMAP,	// Ÿ�� ����
		0,				//4,5���� : ������ ����, ���� ũ��(���� ����ü�� �о�� ���̱� ������ ������ �Ű������� ä���� �ʿ䰡 ����)
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);	// LR_LOADFROMFILE : ���Ͽ��� �̹����� �ҷ��´ٴ� �ɼ� LR_CREATEDIBSECTION: DIB���·� ��ȯ�ϰڴٴ� �ɼ�

												// SelectObject : �� �Լ��� GDI ������Ʈ�� ���Ӱ� �����ϱ� �� ������ ������ �ִ� GDI ������Ʈ�� ��ȯ
	m_holdBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	ReleaseDC(g_hWnd, hDC);
}

void CMyBmp::Release(void)
{
	SelectObject(m_hMemDC, m_holdBitMap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
