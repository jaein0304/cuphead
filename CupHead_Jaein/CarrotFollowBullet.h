#pragma once
#include "Bullet.h"
class CCarrotFollowBullet :
	public CBullet
{
public:
	CCarrotFollowBullet();
	virtual ~CCarrotFollowBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	//void		Set_BulletType(BULLETTYPE_MONSTER eType) { m_eType = eType; };
	void		Animation_Change(void);


private:
	//BULLETTYPE_MONSTER m_eType = BULLET_MONSTER_END;

	BULLETTYPE_MONSTER				m_ePreState;
	BULLETTYPE_MONSTER				m_eCurState;


};

