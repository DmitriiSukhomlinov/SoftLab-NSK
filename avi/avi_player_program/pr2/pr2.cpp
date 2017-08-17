
// pr2.cpp : ���������� ��������� ������� ��� ����������.
//

#include "stdafx.h"
#include "pr2.h"
#include "pr2Dlg.h"
#include "Vfw.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cpr2App

BEGIN_MESSAGE_MAP(Cpr2App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// �������� Cpr2App

Cpr2App::Cpr2App()
{
	// ��������� ���������� ������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �������� ��� ��������,
	// ��������� ���� ������ ��� ������������� � InitInstance
}


// ������������ ������ Cpr2App

Cpr2App theApp;


// ������������� Cpr2App

BOOL Cpr2App::InitInstance()
{
	// InitCommonControlsEx() ��������� ��� Windows XP, ���� ��������
	// ���������� ���������� ComCtl32.dll ������ 6 ��� ����� ������� ������ ��� ���������
	// ������ �����������. � ��������� ������ ����� ��������� ���� ��� �������� ������ ����.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �������� ���� �������� ��� ��������� ���� ����� ������� ����������, ������� ���������� ������������
	// � ����� ����������.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();




	AfxEnableControlContainer();

	// ������� ��������� ��������, � ������, ���� ���������� ���� ��������
	// ������������� ������ �������� ��� �����-���� ��� �������� ����������.
	CShellManager *pShellManager = new CShellManager;

	// ����������� �������������
	// ���� ��� ����������� �� ������������ � ���������� ��������� ������
	// ��������� ������������ �����, ���������� ������� �� ���������
	// ���������� �������� �������������, ������� �� ���������
	// �������� ������ �������, � ������� �������� ���������
	// TODO: ������� �������� ��� ������ �� ���-������ ����������,
	// �������� �� �������� �����������
	SetRegistryKey(_T("��������� ����������, ��������� � ������� ������� ����������"));


	CoInitialize(NULL);
	{

		Cpr2Dlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();

		if (nResponse == IDOK)
		{
			// TODO: ������� ��� ��� ��������� �������� ����������� ����
			//  � ������� ������ "��"
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: ������� ��� ��� ��������� �������� ����������� ����
			//  � ������� ������ "������"
		}
	}
	CoUninitialize();



	// ������� ��������� ��������, ��������� ����.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��������� ���������� ���� �������, ���������� �������� FALSE, ����� ����� ���� ����� ��
	//  ���������� ������ ������� ���������� ��������� ����������.
	return FALSE;
}


