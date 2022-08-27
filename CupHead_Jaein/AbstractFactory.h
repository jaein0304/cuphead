#pragma once

#include "Obj.h"
#include "Scene.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static	CObj*		Create()
	{
		CObj*		pObj = new	T;
		pObj->Initialize();

		return pObj;
	}

	static	CObj*		Create(float _fX, float _fY)
	{
		CObj*		pObj = new	T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}

	static	CScene*		CreateStage()
	{
		CScene*		pStage = new T;
		pStage->Initialize();

		return pStage;
	}
	static	CObj*		CreateMonster(float _fX, float _fY, MONSTERPATTERN _Pattern)
	{
		CObj*		pObj = new	T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Pattern(_Pattern);


		return pObj;
	}
	static	CObj*		CreateItem(float _fX, float _fY, ITEMTYPE _Type)
	{
		CObj*		pObj = new	T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_ItemType(_Type);


		return pObj;
	}
	
};
