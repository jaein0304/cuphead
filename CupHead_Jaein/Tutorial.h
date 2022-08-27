#pragma once
#include "Scene.h"
class CTutorial :
	public CScene
{
public:
	CTutorial();
	virtual ~CTutorial();


public:
	void	Initialize(void);
	int		Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);

	

private:
	void	Insert_Bmp();
	void	Load_File();
};

