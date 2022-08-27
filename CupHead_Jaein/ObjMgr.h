#pragma once
#include "Include.h"
#include "Tile.h"

class CObj;

class CObjMgr
{
public:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Target(OBJID eID, CObj* pObj);

	void SaveList(CObj* _cube)
	{
		m_ObjList[OBJ_TILE].push_back(_cube);
	}

	void DeleteList(CObj* _cube)
	{
		auto& iter = m_ObjList[OBJ_TILE].begin();
		for (iter; iter != m_ObjList[OBJ_TILE].end();)
		{
			if ((*iter)->Get_Info().fX == _cube->Get_Info().fX && (*iter)->Get_Info().fY == _cube->Get_Info().fY)
			{
				m_ObjList[OBJ_TILE].erase(iter);
				break;
			}
			else
				++iter;
		}
	}

	CObj*		Get_Player() 
	{
		if (0 >= m_ObjList[OBJ_PLAYER].size())
			return nullptr;
		return m_ObjList[OBJ_PLAYER].front(); 
	}

	CObj*		Get_Potato()
	{
		if (0 >= m_ObjList[OBJ_MONSTER_POTATO].size())
			return nullptr;
		return m_ObjList[OBJ_MONSTER_POTATO].front();
	}

	CObj*		Get_Onion()
	{
		if (0 >= m_ObjList[OBJ_MONSTER_ONION].size())
			return nullptr;
		return m_ObjList[OBJ_MONSTER_ONION].front();
	}

	CObj*		Get_Carrot()
	{
		if (0 >= m_ObjList[OBJ_MONSTER_CARROT].size())
			return nullptr;
		return m_ObjList[OBJ_MONSTER_CARROT].front();
	}

	void SaveMap();
	void LoadMap();

	list<CObj*>* Get_List() { return m_ObjList; }
	list<CObj*>	 Get_Tile() { return m_ObjList[OBJ_TILE]; }

public:
	void		AddObject(OBJID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);
	void		Delete_ID(OBJID eID);

private:
	list<CObj*>	m_ObjList[OBJ_END];
	//list<CObj*> m_RenderSort[RENDER_END]; //소팅위함 
	


public:
	static	CObjMgr*	Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CObjMgr;
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
	static	CObjMgr*			m_pInstance;
};

