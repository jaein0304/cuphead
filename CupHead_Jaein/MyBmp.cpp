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

	// CreateCompatibleDC : 화면 DC를 얻어와서 미리 텍스처 그려둔 DC를 만들어 준다.

	m_hMemDC = CreateCompatibleDC(hDC);	// 원본 DC를 얻어와서 그리기 준비를 하기 위한 수단

	m_hBitmap = (HBITMAP)LoadImage(nullptr,		// 프로그램의 인스턴스 핸들, 이미지는 프로그램에서 얻어오는 것이 아닌 파일로부터 읽어들이기 때문에 NULL값 전달
		pFilePath,	// 파일의 경로
		IMAGE_BITMAP,	// 타입 지정
		0,				//4,5인자 : 파일의 가로, 세로 크기(파일 그자체를 읽어올 것이기 때문에 별도로 매개변수를 채워줄 필요가 없음)
		0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);	// LR_LOADFROMFILE : 파일에서 이미지를 불러온다는 옵션 LR_CREATEDIBSECTION: DIB형태로 변환하겠다는 옵션

												// SelectObject : 이 함수는 GDI 오보젝트를 새롭게 선택하기 전 기존에 가지고 있던 GDI 오브젝트를 반환
	m_holdBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	ReleaseDC(g_hWnd, hDC);
}

void CMyBmp::Release(void)
{
	SelectObject(m_hMemDC, m_holdBitMap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
