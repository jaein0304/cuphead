#include "stdafx.h"
#include "BmpMgr.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
	Release();
}

HDC CBmpMgr::Find_Image(const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

void CBmpMgr::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImgKey));

	if (iter == m_mapBit.end())
	{
		CMyBmp*		pBmp = new CMyBmp;
		pBmp->Load_Bmp(pFilePath);

		m_mapBit.emplace(pImgKey, pBmp);
	}
}

void CBmpMgr::Release(void)
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();

}
