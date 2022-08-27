#pragma once
#include "Bullet.h"
class CGemBullet :
	public CBullet
{
public:
	CGemBullet();
	virtual ~CGemBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Animation_Change(void);
	void		Action(void);
	void		Check_Crash();

	float		diameter = 50.f;
	float		VectorX = -0.1f;
	float		VectorY = 0.36f;

	BULLETTYPE_MONSTER			m_ePreState;
	BULLETTYPE_MONSTER			m_eCurState;
};

