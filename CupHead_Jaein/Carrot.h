#pragma once
#include "Obj.h"

enum CARROTSTATE { CARROT_INTRO, CARROT_IDLE, CARROT_BOMB, CARROT_BEAM, CARROT_DEAD, CARROT_END };

class CCarrot :
	public CObj
{
public:
	CCarrot();
	virtual ~CCarrot();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	void			Animation_Change(void);
	void			Insert_Bmp(void);
	void			CarrotSpread(void);
	void			CarrotBeam(void);

	void			CarrotSpread2(void);
	void			CarrotBeam2(void);

	void			CarrotIdle(void);

	DWORD			m_dwOldTime = GetTickCount();
	list<CObj*>*	m_pBullet = nullptr;
	CObj*			CreateBullet();
	CObj *			ShotBullet(float _fAngle);
	
	CARROTSTATE		m_ePreState;
	CARROTSTATE		m_eCurState;
	int				m_iCarrotHp = 10;
	int				m_iAttackCount = 0;
	int				m_iAttackCount2 = 0;
	int				m_iAttackCount3 = 0;
	int				m_iAttackCount4 = 0;
	int				mWeaponType;
	int				m_iPatternCount;
	bool			m_bCarrotSpread;
	bool			m_bCarrotBeam;
	bool			m_bCarrotIdle;
	bool			m_bCarrotSpread2;
	bool			m_bCarrotBeam2;
	bool			m_bPattern;
};

