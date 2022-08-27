#pragma once
#include "Scene.h"
class CDominoStage :
	public CScene
{
public:
	CDominoStage();
	virtual ~CDominoStage();

	// CScene을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Load_File();
	void		Move_Frame();
	float		m_fScrollY = 0.f;


	TCHAR*			m_pFrameKey = L"";
	FRAME			m_tFrame;
	DWORD			m_dwOldTime = GetTickCount();


};

