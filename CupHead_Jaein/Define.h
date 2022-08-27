#pragma once

#define		WINCX		800
#define		WINCY		600
#define		PI			3.14f
#define		PURE		= 0 

#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1

#define		VK_MAX			0xff


#define		SAFE_DELETE(p)	if(p) { delete p; p = nullptr;}

extern HWND		g_hWnd;