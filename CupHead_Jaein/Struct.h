#pragma once
enum TILETYPE;

typedef struct tagInfo
{
	float		fX;
	float		fY;

	float		fCX;	// 가로 길이
	float		fCY;	// 세로 길이

	//float		fAngle; //03.09 몬스터때문에넣었는데 이거하면 플레이어 위치 이상해짐 
	TILETYPE	eType;
	//float		fDegree;
	//float		a;
	//int			iAttack; //아니 그냥 여기에 뭐 추가만해도 점프안돼 되네 근데 사용하면 점프 사라짐 why

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
	int		iFrameStart;		// 프레임 시작 시점
	int		iFrameEnd;			// 프레임 종료 지점
	int		iFrameAnimation;	// 재생할 애니메이션 인덱스
	DWORD	dwSpeed;			// 애니메이션 재생 속도
	DWORD	dwFrameTime;		// 애니메이션 시작 시간

	//귀찮아서 만든거 m_tFrame.Set_Frame(0, 0, 0, 100, GetTickCount()); 요로코롬사용 
	void Set_Frame(int _Start, int _End, int _Animation, DWORD _Speed, DWORD _frameTime)
	{
		iFrameStart = _Start;
		iFrameEnd = _End;
		iFrameAnimation = _Animation;
		dwSpeed = _Speed;
		dwFrameTime = _frameTime;
	}

}FRAME;

