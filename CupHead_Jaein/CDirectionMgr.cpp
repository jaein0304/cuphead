#include "stdafx.h"
#include "CDirectionMgr.h"

CDirectionMgr::CDirectionMgr() {
}

CDirectionMgr::~CDirectionMgr() {
}

float CDirectionMgr::Degree2Radian(float fDegree) {
	return fDegree * (PI / 180.f);;
}

VECTOR CDirectionMgr::Degree2Vector(float fDegree) {
	float fRadian = fDegree * (PI / 180.f);
	return  VECTOR{ cosf(fRadian),sinf(fRadian) };
}

float CDirectionMgr::Radian2Degree(float fRadian) {
	return  fRadian / PI * 180.f;
}

VECTOR CDirectionMgr::Radian2Vector(float fRadian) {
	return VECTOR{ cosf(fRadian),sinf(fRadian) };
}

float CDirectionMgr::Vector2Degree(VECTOR start, VECTOR end) {
	float fRadian = atan2f(end.fY - start.fY, end.fX - start.fX);
	return fRadian / PI * 180.f;
}

float CDirectionMgr::Vector2Radian(VECTOR start, VECTOR end) {
	float fRadian = atan2f(end.fY - start.fY, end.fX - start.fX);
	return fRadian;
}

float CDirectionMgr::Vector2Distance(VECTOR start, VECTOR end) {
	float fWidht = fabsf(start.fX - end.fX);
	float fHeight = fabsf(start.fY - end.fY);
	return sqrtf(fWidht * fWidht + fHeight * fHeight);
}
