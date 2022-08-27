#pragma once
#include "Include.h"
class CDirectionMgr {
public:
	CDirectionMgr();
	~CDirectionMgr();
public:
	static float Degree2Radian(float fDegree);
	static VECTOR Degree2Vector(float fDegree);

	static float Radian2Degree(float fRadian);
	static VECTOR Radian2Vector(float fRadian);

	static float Vector2Degree(VECTOR start, VECTOR end);
	static float Vector2Radian(VECTOR start, VECTOR end);
	static float Vector2Distance(VECTOR start, VECTOR end);
};