#pragma once
#include "Scene.h"
class CRootStage2 :
	public CScene
{
public:
	CRootStage2();
	virtual ~CRootStage2();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void			Insert_Bmp();
	void			Load_File();
	DWORD			m_dwOldTime = GetTickCount();
};

