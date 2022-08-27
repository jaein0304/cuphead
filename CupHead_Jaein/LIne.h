#pragma once

#include "Include.h"

class CLine
{
public:
	CLine();
	CLine(LINEINFO& tInfo);
	CLine(LINEPOS& tLPoint, LINEPOS& tRPoint);
	~CLine();

public:
	const LINEINFO&		Get_Info(void) const { return m_tInfo; }

public:
	void		Render(HDC hDC);
	void		RectSetting();

private:
	LINEINFO			m_tInfo;
	RECT				m_tRect;

};

