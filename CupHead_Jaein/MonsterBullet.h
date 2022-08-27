#pragma once
#include "Bullet.h"
class CMonsterBullet :
	public CBullet
{
public:
	CMonsterBullet();
	virtual ~CMonsterBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void		Animation_Change(void);
	/*void		Set_BulletType(BULLETTYPE_MONSTER eType) { m_eType = eType; };
	void		Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; };*/

private:
	/*BULLETTYPE_MONSTER m_eType = BULLET_MONSTER_END;
	CObj*		m_pPlayer;*/
	
	BULLETTYPE_MONSTER				m_ePreState;
	BULLETTYPE_MONSTER				m_eCurState;

};

