#pragma once
#include "Bullet.h"
class CBasicBullet :
	public CBullet
{
public:
	CBasicBullet();
	virtual ~CBasicBullet();

public:
	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual void Late_Update(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

private:
	CObj*			m_pTarget = nullptr;
	void			Animation_Change(void);
	void			Insert_Bmp(void);
	BULLETTYPE		m_eType = BULLET_END;


	BULLETSTATE				m_ePreState;
	BULLETSTATE				m_eCurState;
};

