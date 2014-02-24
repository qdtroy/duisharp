
#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#pragma once

#define WIN32_LEAN_AND_MEAN	
#define _CRT_SECURE_NO_DEPRECATE

#include "..\..\Include\DuiSharp.h"
using namespace duisharp;
#if _MSC_VER <= 1400
#ifdef _DEBUG
# pragma comment(lib, "..\\..\\Lib\\duisharp_2005_d.lib")
#else
# pragma comment(lib, "..\\..\\Lib\\duisharp_2005.lib")
#endif
#else
#if _MSC_VER <= 1500
#ifdef _DEBUG
# pragma comment(lib, "..\\..\\Lib\\duisharp_2008_d.lib")
#else
# pragma comment(lib, "..\\..\\Lib\\duisharp_2008.lib")
#endif
#else
#ifdef _DEBUG
# pragma comment(lib, "..\\..\\Lib\\duisharp_d.lib")
#else
# pragma comment(lib, "..\\..\\Lib\\duisharp.lib")
#endif
#endif
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
