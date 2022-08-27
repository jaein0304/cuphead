#include "stdafx.h"
#include "SuperBulletParent.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "SuperBulletEffect.h"


SuperBulletParent::SuperBulletParent()
{
}


SuperBulletParent::~SuperBulletParent()
{
	Release();
}

void SuperBulletParent::Initialize(void)
{
}

int SuperBulletParent::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;
}

void SuperBulletParent::Late_Update(void)
{
}

void SuperBulletParent::Render(HDC hDC)
{
}

void SuperBulletParent::Release(void)
{
	CObj* pObj = nullptr;
	pObj = CAbstractFactory<CSuperBulletEffect>::Create((float)m_tInfo.fX, (float)m_tInfo.fY);
	CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, pObj);

}
