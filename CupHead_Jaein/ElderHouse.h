#pragma once
#include "Scene.h"
class CElderHouse :
	public CScene
{
public:
	CElderHouse();
	virtual ~CElderHouse();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Load_File();


};
