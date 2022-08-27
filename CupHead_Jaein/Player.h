#pragma once
#include "Obj.h"

class CPlayer :
	public CObj
{
public:
//	enum PLAYERSTATE { IDLE, WALK, ATTACK, HIT, JUMP, DEAD, END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void	Initialize(void)	override;
	virtual int		Update(void)		override;
	virtual	void	Late_Update(void)	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release(void)	override;
	//void	Set_Ground(bool _bState) { m_bGround = _bState; }
	//void	Set_Jump(bool _bState) { m_bJump = _bState; }
	//bool	Get_Ground() { return m_bGround; }
	bool	JumpCheck();

	


private:
	CObj*	CreateBullet(float _fAngle);
	CObj*   CreateSuperBullet(float _fAngle);
	CObj*	CreateFollowBullet(float _fAngle);
	CObj*	RedBullet(float _fAngle);

	void	Key_Input(void);
	void	Jump(void);
	void	Offset(void);
	void	Insert_Bmp(void);
	void	Insert_Sound(void);
	void	Animation_Change(void);

private:
	POINT					m_tPosin;
	//bool					m_bGround;
	//bool					m_bJump; // 점프 상태 확인
	float					m_fJumpPower;
	float					m_fJumpTime;
	float					dwOldTime = GetTickCount();
	bool					m_bKing;
	PLAYERSTATE				m_ePreState;
	PLAYERSTATE				m_eCurState;
};

