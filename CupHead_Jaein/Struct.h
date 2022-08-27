#pragma once
enum TILETYPE;

typedef struct tagInfo
{
	float		fX;
	float		fY;

	float		fCX;	// ���� ����
	float		fCY;	// ���� ����

	//float		fAngle; //03.09 ���Ͷ������־��µ� �̰��ϸ� �÷��̾� ��ġ �̻����� 
	TILETYPE	eType;
	//float		fDegree;
	//float		a;
	//int			iAttack; //�ƴ� �׳� ���⿡ �� �߰����ص� �����ȵ� �ǳ� �ٵ� ����ϸ� ���� ����� why

}INFO;

typedef struct tagVector {
	float fX;
	float fY;
}VECTOR;

typedef struct tagLinePos
{
	float	fX;
	float	fY;

	tagLinePos()
	{
		ZeroMemory(this, sizeof(tagLinePos));
	}
	tagLinePos(float _fX, float _fY)
		: fX(_fX), fY(_fY)
	{

	}

}LINEPOS;

typedef	struct tagLineInfo
{
	LINEPOS		tLeftPoint;
	LINEPOS		tRightPoint;

	tagLineInfo()
	{
		ZeroMemory(this, sizeof(tagLineInfo));
	}
	tagLineInfo(LINEPOS& tLPoint, LINEPOS& tRPoint)
		: tLeftPoint(tLPoint), tRightPoint(tRPoint)
	{

	}

}LINEINFO;

typedef	struct tagFrame
{
	int		iFrameStart;		// ������ ���� ����
	int		iFrameEnd;			// ������ ���� ����
	int		iFrameAnimation;	// ����� �ִϸ��̼� �ε���
	DWORD	dwSpeed;			// �ִϸ��̼� ��� �ӵ�
	DWORD	dwFrameTime;		// �ִϸ��̼� ���� �ð�

	//�����Ƽ� ����� m_tFrame.Set_Frame(0, 0, 0, 100, GetTickCount()); ����ڷһ�� 
	void Set_Frame(int _Start, int _End, int _Animation, DWORD _Speed, DWORD _frameTime)
	{
		iFrameStart = _Start;
		iFrameEnd = _End;
		iFrameAnimation = _Animation;
		dwSpeed = _Speed;
		dwFrameTime = _frameTime;
	}

}FRAME;

