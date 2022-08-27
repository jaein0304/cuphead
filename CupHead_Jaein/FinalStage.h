#pragma once
#include "Scene.h"
class CFinalStage :
	public CScene
{
public:
	CFinalStage();
	~CFinalStage();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


public:
	void			Load_File();
	DWORD			m_dwOldTime = GetTickCount();
	DWORD			m_dwOldTime2 = GetTickCount();

};

