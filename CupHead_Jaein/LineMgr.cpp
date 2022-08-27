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
	HANDLE	hFile = CreateFile(L"../Data/Save.dat",			// 파일을 저장하고자 하는 경로 및 파일 이름 지정
		GENERIC_READ,				// 파일 접근 모드(GENERIC_WRITE 쓰기 전용, GENERIC_READ 읽기 전용)
		NULL,						// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 공유를 허용할 것인가 설정(NULL 값인 경우 공유 금지)
		NULL,						// 보안 속성, NULL일 경우 기본 보안 상태
		OPEN_EXISTING,				// 파일 생성 방식, 해당 파일을 열어서 작업할 것인지 아니면 새로 만들것인지 설정, CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXITING : 파일이 있을 경우에만 연다
		FILE_ATTRIBUTE_NORMAL,		// 파일 속성(읽기 전용, 숨김 등) FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
		NULL);						// 생성될 파일의 속성을 제공할 템플릿 파일, 우리는 사용안하니깐 NULL


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

	MessageBox(g_hWnd, _T("Load 성공"), _T("완료"), MB_OK);
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
