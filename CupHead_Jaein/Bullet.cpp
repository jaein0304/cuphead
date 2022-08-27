#include "stdafx.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "BulletEffect.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{

}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{

}

void CBullet::Render(HDC hDC)
{

}

void CBullet::Release(void)
{
	CObj* pObj = nullptr;
	pObj = CAbstractFactory<CBulletEffect>::Create((float)m_tInfo.fX, (float)m_tInfo.fY);
	CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, pObj);
}
