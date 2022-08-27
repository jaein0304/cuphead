#pragma once
#include "Obj.h"

enum DOMINOSTATE { DOMINO_IDLE, DOMINO_ATTACK, DOMINO_BIRDATTACK, DOMINO_DEAD, DOMINO_END };

class CDomino :
	public CObj
{
public:
	CDomino();
	virtual ~CDomino();

	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void			Insert_Bmp(void);
	void			Animation_Change(void);
	void			DominoGem(void);
	void			DominoBird(void);
	void			DominoThorn(void);
	void			DominoFloor(void);

	CObj*			CreateBullet();
	CObj*			CreateBullet2();
	CObj*			CreateBullet3();
	CObj*			CreateBullet4();
	DWORD			m_dwOldTime = GetTickCount();
	DWORD			m_dwOldTime2 = GetTickCount();
	DWORD			m_dwOldTime3 = GetTickCount();


	DOMINOSTATE		m_eCurState;
	DOMINOSTATE		m_ePreState;
};

