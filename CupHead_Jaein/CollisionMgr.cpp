#include "stdafx.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "Tile.h"

#include "BasicBullet.h"
#include "Carrot.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CCollisionMgr* CCollisionMgr::m_pInstance = nullptr;

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::TileCollision(POINT _pt, CObj* _Tile)
{
	float x = (float)_pt.x;
	float y = (float)_pt.y;


	if (x >= _Tile->Get_Rect().left && x <= _Tile->Get_Rect().right
		&& y >= _Tile->Get_Rect().top && y <= _Tile->Get_Rect().bottom)
	{
		return true;
	}


	return false;
}




void CCollisionMgr::Collision_Rect(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_Rect())))
			{
				DestIter->Set_Dead();
			}
		}
	}

}


void CCollisionMgr::Collision_Sphere(list<CObj*> Dest, list<CObj*> Sour)
{
	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (Check_Sphere(DestIter, SourIter))
			{
				DestIter->Set_Dead();
				SourIter->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{

	float	fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;

	return fRadius >= fDiagonal;
}

bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSour, float* pfX, float* pfY)
{
	float		fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float		fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float		fRadiusX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f;

	if (fRadiusX > fWidth && fRadiusY > fHeight)
	{
		*pfX = fRadiusX - fWidth;
		*pfY = fRadiusY - fHeight;

		return true;
	}
	return false;
}

void CCollisionMgr::Collision_RectEx(list<CObj*> Dest, list<CObj*> Sour)
{
	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(DestIter, SourIter, &fX, &fY))
			{

				// 상하 좌우 구분
				if (DestIter->Get_Info().fY >= SourIter->Get_Info().fY - SourIter->Get_Info().fCY
					&& DestIter->Get_Info().fY < SourIter->Get_Info().fY)
				{
					if (true == DestIter->Get_Jump() || true == DestIter->Get_Fall())
					{
						if (DestIter->Get_Info().fX <= SourIter->Get_Rect().right
							&& DestIter->Get_Info().fX >= SourIter->Get_Rect().left)
						{
							if (DestIter->Get_Info().fY < SourIter->Get_Info().fY)
							{
								DestIter->Set_Jump(false);
								DestIter->Set_Fall(false);
								//DestIter->Set_Ground(true);
								float tempY = fabs(DestIter->Get_Info().fY + (DestIter->Get_Info().fCY * 0.5f) - float(SourIter->Get_Rect().top));
								DestIter->Set_PosY(-tempY);
							}
						}
					}
				}
				else if (DestIter->Get_Info().fY <= SourIter->Get_Info().fY + SourIter->Get_Info().fCY
					&& DestIter->Get_Info().fY > SourIter->Get_Info().fY)
				{
					if (true == DestIter->Get_Jump() || true == DestIter->Get_Fall())
					{
						if (DestIter->Get_Info().fY > SourIter->Get_Info().fY)
						{
							if (DestIter->Get_Info().fX <= SourIter->Get_Rect().right
								&& DestIter->Get_Info().fX >= SourIter->Get_Rect().left)
							{
								//DestIter->Set_Ground(true);
								float tempY = fabs(DestIter->Get_Info().fY - (DestIter->Get_Info().fCY * 0.5f) - float(SourIter->Get_Rect().bottom));
								DestIter->Set_PosY(tempY);
							}
						}
					}
				}
				if (DestIter->Get_Info().fX >= SourIter->Get_Info().fX - SourIter->Get_Info().fCX
					&& DestIter->Get_Info().fX < SourIter->Get_Info().fX)
				{
					if (DestIter->Get_Info().fY >= SourIter->Get_Rect().top
						&& DestIter->Get_Info().fY <= SourIter->Get_Rect().bottom)
					{
						if (DestIter->Get_Info().fX < SourIter->Get_Info().fX)
						{
							float tempX = fabs(DestIter->Get_Info().fX + (DestIter->Get_Info().fCX * 0.5f) - float(SourIter->Get_Rect().left));
							DestIter->Set_PosX(-tempX);
						}
					}
				}
				else if (DestIter->Get_Info().fX <= SourIter->Get_Info().fX + SourIter->Get_Info().fCX
					&& DestIter->Get_Info().fX > SourIter->Get_Info().fX)
				{
					if (DestIter->Get_Info().fY >= SourIter->Get_Rect().top
						&& DestIter->Get_Info().fY <= SourIter->Get_Rect().bottom)
					{
						if (DestIter->Get_Info().fX > SourIter->Get_Info().fX)
						{
							float tempX = fabs(DestIter->Get_Info().fX - (DestIter->Get_Info().fCX * 0.5f) - float(SourIter->Get_Rect().right));
							DestIter->Set_PosX(tempX);
						}
					}
				}
			}
		}
	}
}

void CCollisionMgr::Collision_MonsterRect(list<CObj*> pDest, list<CObj*> pSour)
{
	for (auto& Destiter : pDest)
	{
		for (auto& Souriter : pSour)
		{
			if (Check_Sphere(Destiter, Souriter))
			{
				Souriter->Set_Dead();
				Destiter->Set_Hp(1);
			}
		}
	}
}

//플레이어 총알 -> 몬스터 피깎기 
void CCollisionMgr::Collision_Bullet(list<CObj*> Dest, list<CObj*> Sour)
{
	for (auto& Destiter : Dest)
	{
		for (auto& Souriter : Sour)
		{
			if (Check_Sphere(Destiter, Souriter))
			{
				/*FRAME				m_tFrame;
				m_tFrame.Set_Frame(0, 17, 0, 200, GetTickCount());*/
				Destiter->Set_Dead();
				Souriter->Set_Hp(1); //몬스터 피 1씩 깎기 
			}
		}
	}
}
void CCollisionMgr::Collision_SuperBullet(list<CObj*> Dest, list<CObj*> Sour)
{
	for (auto& Destiter : Dest)
	{
		for (auto& Souriter : Sour)
		{
			if (Check_Sphere(Destiter, Souriter))
			{
				/*FRAME				m_tFrame;
				m_tFrame.Set_Frame(0, 17, 0, 200, GetTickCount());*/
				Destiter->Set_Dead();
				Souriter->Set_Hp(5); //몬스터 피 5씩 깎기 
			}
		}
	}
}

bool CCollisionMgr::Collision_Rect2(CObj * pDest, CObj * pSour)
{
	float		fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float		fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float		fRadiusX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f;

	if (fRadiusX > fWidth && fRadiusY > fHeight)
		return true;


	return false;
}

//몬스터 총알->플레이어 피깎기
void CCollisionMgr::Collision_MonsterBullet(list<CObj*> pDest, list<CObj*> pSour)
{
	for (auto& Destiter : pDest)
	{
		for (auto& Souriter : pSour)
		{
			if (Check_Sphere(Destiter, Souriter))
			{
				//Destiter->Set_Dead();
				//Destiter->Set_Damage(dynamic_cast<CBasicBullet*>(Souriter)->Get_Damage()); //플레이어가 총알 피격 시 데미지 들어가게 
				Destiter->Set_Dead();
				Souriter->Set_Hp(1); //총알에 부딪히면 플레이어 피깎기
			}
		}
	}
}

void CCollisionMgr::Collision_RectItem(list<CObj*> Player, list<CObj*> Item)
{
	for (auto& pPlayerIter : Player)
	{
		for (auto& pItemIter : Item)
		{
			float	fX = 0.f, fY = 0.f;
			if (Check_Rect(pPlayerIter, pItemIter, &fX, &fY))
			{
				if (pItemIter->Get_ItemType() == ITEM_1)
				{
					pPlayerIter->Item_Plus();
				}
			
				pItemIter->Set_Dead();
			}
		}
	}
}

//void CCollisionMgr::Collision_ExitRect(list<CObj*> pDest, list<CObj*> pSour)
//{
//	for (auto& Destiter : pDest)
//	{
//		for (auto& Souriter : pSour)
//		{
//			if (dynamic_cast<CTile*>(Souriter)->Get_Type() == RED)
//			{
//				if (Collision_Rect2(Destiter, Souriter))	
//				{
//					if (Destiter->Get_CheckStage() == 1)
//						Destiter->Set_CheckStage(2);
//				}
//			}
//		}
//	}
//}
