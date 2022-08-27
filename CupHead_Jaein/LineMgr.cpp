#include "stdafx.h"
#include "LineMgr.h"

CLineMgr*	CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	LINEPOS L1{ 0.f,450.f };
	LINEPOS L2{ 200.f,450.f };

	RECT TempRect{ 0,500,800,600 };
	m_vecRect.push_back(TempRect);

	m_LineList.push_back(new CLine(L1, L2));

	Load_File();
}



void CLineMgr::Render(HDC hDC)
{
	/*for (auto& iter : m_LineList)
		iter->Render(hDC);*/

	/*for (int i = 0; i < m_vecRect.size(); ++i)
		Rectangle(hDC, m_vecRect[i].left, m_vecRect[i].top, m_vecRect[i].right, m_vecRect[i].bottom);*/
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

void CLineMgr::Load_File(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Save.dat",			// ������ �����ϰ��� �ϴ� ��� �� ���� �̸� ����
		GENERIC_READ,				// ���� ���� ���(GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// ���� ���, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ������ ����� ���ΰ� ����(NULL ���� ��� ���� ����)
		NULL,						// ���� �Ӽ�, NULL�� ��� �⺻ ���� ����
		OPEN_EXISTING,				// ���� ���� ���, �ش� ������ ��� �۾��� ������ �ƴϸ� ���� ��������� ����, CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXITING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��) FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
		NULL);						// ������ ������ �Ӽ��� ������ ���ø� ����, �츮�� �����ϴϱ� NULL


	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	LINEINFO	tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load ����"), _T("�Ϸ�"), MB_OK);
}

bool CLineMgr::Collision_Line(float& fPlayerX, float& fPlayerY, float* pY)
{
	//float TempY = 0, f;

	if (m_LineList.empty())
		return false;

	CLine*		pTargeLine = nullptr;

	for (auto& iter : m_LineList)
	{
		/*if (fPlayerX >= iter->Get_Info().tLeftPoint.fX && fPlayerX <= iter->Get_Info().tRightPoint.fX
			&& fPlayerY > iter->Get_Info().tLeftPoint.fY || fPlayerY > iter->Get_Info().tRightPoint.fY)
		{
			pTargeLine = iter;
		}*/
		if (fPlayerX >= iter->Get_Info().tLeftPoint.fX && fPlayerX <= iter->Get_Info().tRightPoint.fX)
		{
			/*if (fPlayerY > iter->Get_Info().tLeftPoint.fY || fPlayerY > iter->Get_Info().tRightPoint.fY)
			{
				if (!pTargeLine)
				{
					pTargeLine = iter;
				}
				else if (pTargeLine->Get_Info().tLeftPoint.fY < iter->Get_Info().tLeftPoint.fY
					|| pTargeLine->Get_Info().tRightPoint.fY < iter->Get_Info().tRightPoint.fY)
					pTargeLine = iter;
			}*/
			pTargeLine = iter;
		}
			
	}

	if (nullptr == pTargeLine)
		return false;

	// PlayerY - y1 = ((y2 - y1) / (x2 - x1)) * (PlayerX - x1)
	// PlayerY = ((y2 - y1) / (x2 - x1)) * (PlayerX - x1) + y1

	float		x1 = pTargeLine->Get_Info().tLeftPoint.fX;
	float		x2 = pTargeLine->Get_Info().tRightPoint.fX;

	float		y1 = pTargeLine->Get_Info().tLeftPoint.fY;
	float		y2 = pTargeLine->Get_Info().tRightPoint.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (fPlayerX - x1) + y1;

	return true;
}
