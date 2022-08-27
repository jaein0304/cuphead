#pragma once
#include "Scene.h"
class CEnding :
	public CScene
{
public:
	CEnding();
	virtual ~CEnding();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool		bEnterState;
	HWND		m_hVideo;
};

