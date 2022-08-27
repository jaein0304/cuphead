#pragma once
#include "Include.h"

class CKeyMgr
{
public:
	CKeyMgr();
	~CKeyMgr();

public:
	bool			Key_Pressing(int _Key); // ������ ���� �� ��� true
	bool			Key_Down(int _Key); // ó�� �� ���� true
	bool			Key_Up(int _Key);	// �����ٰ� ���� �� true

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

