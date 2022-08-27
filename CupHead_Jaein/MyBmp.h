#pragma once

#include "Include.h"

class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();

public:
	HDC			Get_MemDC() { return m_hMemDC; }

public:
	void		Load_Bmp(const TCHAR* pFilePath);
	void		Release(void);

private:
	HDC			m_hMemDC;

	HBITMAP		m_hBitmap;
	HBITMAP		m_holdBitMap;

};

// DDB(Device Dependent Bitmap) : 장치 의존적인 비트맵 포맷 형식, 이미지의 크기, 색상 등 기본적인 이미지 데이터로 구성되어 있어 다양한 해상도의 장치에는 광범위하게 사용되지 못한다
// 예를 들어 흑백 비트맵은 흑백 장치로만 컬러 비트맵은 컬러 장치로만 출력할 수 있다.

// DIB(Device Independent Bitmap) : 장치 독립적인 비트맵 포맷, 호환성이 뛰어남