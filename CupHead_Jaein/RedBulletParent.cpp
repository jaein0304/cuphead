#include "stdafx.h"
#include "RedBulletParent.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "RedBulletEffect.h"

CRedBulletParent::CRedBulletParent()
{
}


CRedBulletParent::~CRedBulletParent()
{
	Release();
}

void CRedBulletParent::Initialize(void)
{
}

int CRedBulletParent::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;
}

void CRedBulletParent::Late_Update(void)
{
}

void CRedBulletParent::Render(HDC hDC)
{
}

void CRedBulletParent::Release(void)
{
	CObj* pObj = nullptr;
	pObj = CAbstractFactory<CRedBulletEffect>::Create((float)m_tInfo.fX, (float)m_tInfo.fY);
	CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, pObj);
}
