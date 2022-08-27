#pragma once
#include "Include.h"

class CKeyMgr
{
public:
	CKeyMgr();
	~CKeyMgr();

public:
	bool			Key_Pressing(int _Key); // 누르고 있을 때 계속 true
	bool			Key_Down(int _Key); // 처음 한 번만 true
	bool			Key_Up(int _Key);	// 눌렀다가 뗐을 때 true

	void			Update(void);

public:
	static	CKeyMgr*	Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CKeyMgr;
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
	static	CKeyMgr*			m_pInstance;
	bool						m_bKeyState[VK_MAX];
};

