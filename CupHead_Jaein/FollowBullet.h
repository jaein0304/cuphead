#pragma once
#include "Bullet.h"
class CFollowBullet :
	public CBullet
{
public:
	CFollowBullet();
	virtual ~CFollowBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	CObj*			m_pTarget = nullptr;
	void			Animation_Change(void);
	void			Insert_Bmp(void);
	BULLETTYPE		m_eType = BULLET_END;


	BULLETSTATE				m_ePreState;
	BULLETSTATE				m_eCurState;

};

