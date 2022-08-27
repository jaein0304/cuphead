#pragma once
#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Rect(list<CObj*> Dest, list<CObj*> Sour);
	static void	Collision_RectEx(list<CObj*> Dest, list<CObj*> Sour);
	bool Collision_RectCheck(CObj * pDest, CObj * pSour);
	static void	Collision_Sphere(list<CObj*> Dest, list<CObj*> Sour);
	static bool Check_Sphere(CObj* pDest, CObj* pSour);
	static bool	Check_Rect(CObj* pDest, CObj* pSour, float* pfX, float* pfY);
	static bool CCollisionMgr::TileCollision(POINT _pt, CObj* _Tile);

	static void Collision_MonsterRect(list<CObj*> pDest, list<CObj*> pSour);
	static void Collision_Bullet(list<CObj*> Dest, list<CObj*> Sour);

	void Collision_SuperBullet(list<CObj*> Dest, list<CObj*> Sour);

	static bool Collision_Rect2(CObj * pDest, CObj * pSour);
	void Collision_MonsterBullet(list<CObj*> pDest, list<CObj*> pSour);
	void Collision_RectItem(list<CObj*> Player, list<CObj*> Item);
	void Collision_MonsterBullet2Player(CObj * player, list<CObj*> pMonsterbullet);
	static void Collision_ExitRect(list<CObj*> pDest, list<CObj*> pSour);


public:
	static	CCollisionMgr*	Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CCollisionMgr;
		}

		return m_pInstance;
	}
	static	void		Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static	CCollisionMgr*			m_pInstance;
	DWORD							m_dwOldTime = GetTickCount();

};

