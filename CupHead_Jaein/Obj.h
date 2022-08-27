#pragma once
#include "Include.h"

class CObj
{
public:
	CObj();
	CObj(INFO& _Info);
	virtual ~CObj();

public:
	const INFO&			Get_Info(void) const { return m_tInfo; }
	const RECT&			Get_Rect(void) const { return m_tRect; }

	void				Set_Dead() { m_bDead = true; }
	bool				Get_Dead(void) { return m_bDead; }

	void				Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void		Set_Direction(DIRECTION eDir) { m_eDir = eDir; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; } // 0318
	float		Get_Angle(float _fAngle) { return m_fAngle; }
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

	void				Set_PosY(float _fY) { m_tInfo.fY += _fY; }
	void				Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void				Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }
	bool				Get_Ground() { return m_bGround; }
	void				Set_Jump(bool _State) { m_bJump = _State; }
	void				Set_Ground(bool _State) { m_bGround = _State; }
	void				Set_Fall(bool _State) { m_bFall = _State; }
	void				Set_LeftCol(bool _State) { m_bLeft = _State; }
	void				Set_RightCol(bool _State) { m_bRight = _State; }
	void				Gravity();
	void				Set_FrameKey(TCHAR* _FrameKey) { m_pFrameKey = _FrameKey; }
	void				Set_Pattern(MONSTERPATTERN _Pattern) { m_tPattern = _Pattern; }
	void				Set_ItemType(ITEMTYPE _Type) { m_tItemType = _Type; }

	bool				Get_Fall() { return m_bFall; }
	bool				Get_Jump() { return m_bJump; }

	////////////
	void				Set_Hp(int _iHp) { m_iHp -= _iHp; }
	void				Set_PlayerHp(int _iPlayerHp) { m_iPlayerHp -= _iPlayerHp; }

	void				Set_hp(int _iHp) { m_iHp = _iHp-1; }
	void				Set_Damage(int iDamage) { m_iHp -= iDamage; } //03.11 12:25
	void				Set_CheckStage(int _iStageCheck) { m_iStageCheck = m_iStageCheck; }
	int					Get_CheckStage(void) { return m_iStageCheck; }

	////
	void				Set_Mine(CObj* _Mine) { m_pMine = _Mine; }
	//0313, 스테이지 활성화 시키기 (실패)
	bool GetIsActive()const { return mIsActive; }
	void SetIsActive(bool b) { mIsActive = b; }
	//0315
	//int				Get_Attack() { return m_tInfo.iAttack; }
	int					Get_Hp() { return m_iHp; }
	int					Get_OnionHp() { return m_iOnionHp; }

	int					Get_Attack() { return m_iAttack; }
	const ITEMTYPE&		Get_ItemType()	const { return m_tItemType; }
	void				Item_Plus() { m_iItem += 1; }
	int					Get_ItemCount() { return m_iItem; }
	bool				m_bEffect = false;


public:
	virtual		void	Initialize(void)	PURE;
	virtual		int	    Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

protected:
	void		Update_Rect(void);
	void		Move_Frame(void);
	bool		Long_Frame();



protected:
	INFO				m_tInfo;
	RECT				m_tRect;
	RECT				m_Rect;			
	MONSTERPATTERN		m_tPattern;
	DIRECTION			m_eDir = DIR_END;
	ITEMTYPE			m_tItemType;
	RENDERID			m_eGroup;
	int					m_iItem = 0;

	float				m_fSpeed;
	bool				m_bDead;
	bool				m_bGround;
	bool				m_bJump;
	bool				m_bFall;
	float				m_GravityTime;
	bool				m_bLeft;
	bool				m_bRight;
	float				m_fOffsetSpeed;
	int					m_iPoint; //점수
	int					m_iHp;
	int					m_iPlayerHp;
	FRAME				m_tFrame;
	TCHAR*				m_pFrameKey = L"";
	TCHAR				m_szHp[32] = L"";

	CObj*				m_pTarget;
	float				m_fAngle;
	float				m_fDiagonal;
	float				m_fDirX;
	float				m_fDirY;
	int					m_iStageCheck;
	CObj*				m_pMine;
	static		float	g_fSound;

	bool mIsActive;
	int m_iAttack;
	int m_iOnionHp;
};

