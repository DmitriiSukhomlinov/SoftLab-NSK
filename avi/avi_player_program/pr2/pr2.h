
// pr2.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������
#include "WTypes.h"
#include <Windows.h>
#include "Aviriff.h"

// Cpr2App:
// � ���������� ������� ������ ��. pr2.cpp
//

class Cpr2App : public CWinApp
{
public:
	Cpr2App();


// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern Cpr2App theApp;