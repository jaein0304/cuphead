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

// DDB(Device Dependent Bitmap) : ��ġ �������� ��Ʈ�� ���� ����, �̹����� ũ��, ���� �� �⺻���� �̹��� �����ͷ� �����Ǿ� �־� �پ��� �ػ��� ��ġ���� �������ϰ� ������ ���Ѵ�
// ���� ��� ��� ��Ʈ���� ��� ��ġ�θ� �÷� ��Ʈ���� �÷� ��ġ�θ� ����� �� �ִ�.

// DIB(Device Independent Bitmap) : ��ġ �������� ��Ʈ�� ����, ȣȯ���� �پ