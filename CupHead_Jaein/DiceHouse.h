#pragma once
#include "Scene.h"
class CDiceHouse :
	public CScene
{
public:
	CDiceHouse();
	virtual ~CDiceHouse();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void	Load_File();
};

