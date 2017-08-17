
// BMPReader.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "BMPReader.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBMPReaderApp

BEGIN_MESSAGE_MAP(CBMPReaderApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CBMPReaderApp::OnAppAbout)
	ON_UPDATE_COMMAND_UI(ID_INVERTX, &CBMPReaderApp::OnUpdateInvertx)
	ON_UPDATE_COMMAND_UI(ID_INVERTY, &CBMPReaderApp::OnUpdateInverty)
	ON_UPDATE_COMMAND_UI(ID_NEGATIVERED, &CBMPReaderApp::OnUpdateNegativered)
	ON_UPDATE_COMMAND_UI(ID_NEGATIVEGREEN, &CBMPReaderApp::OnUpdateNegativegreen)
	ON_UPDATE_COMMAND_UI(ID_NEGATIVEBLUE, &CBMPReaderApp::OnUpdateNegativeblue)
	ON_UPDATE_COMMAND_UI(ID_SAVE, &CBMPReaderApp::OnUpdateSave)
END_MESSAGE_MAP()



// CBMPReaderApp construction

CBMPReaderApp::CBMPReaderApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("BMPReader.AppID.NoVersion"));
	
	flagEdit = false;//���� ����������� ���� ��������������. ��� ����� ������� ���������� ������ ����� ����, ��� ����� ������ ����
	flagCheckX = 0;//���� ������� ������� ���� ��������������
	flagCheckY = 0;
	flagCheckR = 0;
	flagCheckG = 0;
	flagCheckB = 0;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CBMPReaderApp object

CBMPReaderApp theApp;


// CBMPReaderApp initialization

BOOL CBMPReaderApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	fileOpen = 0;

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);

	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

 int CBMPReaderApp::loadBMP (CString fname)//�������, ����������� ���� ��������. �������� - ���� � �����
{
	FILE *bmp = fopen (fname, "rb");//��������� ���� ��� ������ ��������
	BITMAPFILEHEADER bmpHeaderIntermediate;//������������� ��������, ����� �� ������,
	BITMAPINFOHEADER bmpInfoIntermadiate;  //���� ����� ������� ������� ���� �� ���� �������,
										   //����� �� ���������� ������ � ����������
	if (flagEdit == true)//���� ��� ������������� ����������
	{
		bmpHeaderIntermediate = bmpHeader;//���������� ����������� ������  (�� ������, ���� ������� ����������)
		bmpInfoIntermadiate = bmpInfo;
	}
	fread (&bmpHeader, 1, sizeof(BITMAPFILEHEADER), bmp);//��������� FILEHEADER
	fread (&bmpInfo, 1, sizeof(BITMAPINFOHEADER), bmp);//��������� INFOHEADER
	try//��������� ����������
	{
		if ((bmpHeader.bfType!=0x4D42) || (bmpInfo.biBitCount != 24))//�������� ��������� � ������� �����
		{
			throw "���� ������ ���� 24-� ������ .bmp";
		}
	}
	catch (const char* exeption)//���� ���� �� ���� ������� - ���������� ����������...
	{
		bmpHeader = bmpHeaderIntermediate;//...�� �������, ���������� �������� �������
		bmpInfo = bmpInfoIntermadiate;
		AfxMessageBox(exeption);
		return 0;
	}
	unsigned char *data = new unsigned char[bmpInfo.biHeight*bmpInfo.biWidth*3];//������� ������ ��� ������ � ������
	fseek (bmp, bmpHeader.bfOffBits, SEEK_SET);//���������� ��������� � ������ �� �� �����, ��� ���������� ���� �� RGB (�� ���, �� ������ ������)
	fread (data, 1, bmpInfo.biHeight*bmpInfo.biWidth*3, bmp);//������ ���������
	fclose (bmp);//��������� ����, ������ �� ��� �� � ����
	bmpInfoRGB.bmiHeader = bmpInfo;//���� � ����� �������...
	bmpInfoRGB.bmiHeader.biBitCount = 32;//...����� ��, �� ���������� ����, ��� ������ ��� 32 ����
	bmpColor = new RGBQUAD[bmpInfo.biHeight*bmpInfo.biWidth];//������� ������ ��� RGB
	int addPixels = bmpInfo.biWidth % 4;//���������� ����������� �������� (� .bmp-���� ����������� � ������ ������� ������� ��������, ����� �� ���������� ���� ������ �������)
	for (int i = 0; i < bmpInfo.biHeight; i++)//�� ��������
	{
		for (int j = 0; j< bmpInfo.biWidth*3; j=j+3)//�� ��������
		{
			bmpColor[i * bmpInfo.biWidth + j / 3].rgbBlue = data[i * bmpInfo.biWidth * 3 + i * addPixels + j];//������� ������� - ������ ����
			bmpColor[i * bmpInfo.biWidth + j / 3].rgbGreen = data[i * bmpInfo.biWidth * 3 + i * addPixels + j + 1];
			bmpColor[i * bmpInfo.biWidth + j / 3].rgbRed = data[i * bmpInfo.biWidth * 3 + i * addPixels + j + 2];
			bmpColor[i * bmpInfo.biWidth + j / 3].rgbReserved = 0;//����� ������ ����
		}
	}
	delete []data;//������� ������
	height = bmpInfo.biHeight;//������ ���������
	width = bmpInfo.biWidth;//� ������ ����
	flagEdit = true;//������ ���������� ���� ��������������
	return 0;
}

 int CBMPReaderApp::saveBMP (CString fname)//�������, ����������� ���� ��������
 {
	FILE *bmp = fopen (fname, "wb");//��������� ���� ��� ������ ��������
	bmpInfo.biBitCount = 32;
	fwrite (&bmpHeader, 1, sizeof(BITMAPFILEHEADER), bmp);//���������� 
	fwrite (&bmpInfo, 1, sizeof(BITMAPINFOHEADER), bmp);
	fwrite (bmpColor, 4, bmpInfo.biHeight*bmpInfo.biWidth, bmp);
	fclose (bmp);
	return 0;
 }



int CBMPReaderApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CBMPReaderApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CBMPReaderApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CBMPReaderApp message handlers





void CBMPReaderApp::OnUpdateInvertx(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(flagEdit);
	pCmdUI->SetCheck(flagCheckX);
	// TODO: �������� ���� ��� ����������� �� ���������� ������
}


void CBMPReaderApp::OnUpdateInverty(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(flagEdit);
	pCmdUI->SetCheck(flagCheckY);
	// TODO: �������� ���� ��� ����������� �� ���������� ������
}


void CBMPReaderApp::OnUpdateNegativered(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(flagEdit);
	pCmdUI->SetCheck(flagCheckR);
	// TODO: �������� ���� ��� ����������� �� ���������� ������
}


void CBMPReaderApp::OnUpdateNegativegreen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(flagEdit);
	pCmdUI->SetCheck(flagCheckG);
	// TODO: �������� ���� ��� ����������� �� ���������� ������
}


void CBMPReaderApp::OnUpdateNegativeblue(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(flagEdit);
	pCmdUI->SetCheck(flagCheckB);
	// TODO: �������� ���� ��� ����������� �� ���������� ������
}


void CBMPReaderApp::OnUpdateSave(CCmdUI *pCmdUI)
{
		pCmdUI->Enable(flagEdit);
	// TODO: �������� ���� ��� ����������� �� ���������� ������
}
