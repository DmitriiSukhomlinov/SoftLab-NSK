
// MainFrm.cpp : implementation of the CMainFrame class
//
#include <string>
#include <iostream>
#include "stdafx.h"
#include "BMPReader.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_PAINT()
	ON_COMMAND(ID_OPEN, MenuOpen)
	ON_COMMAND(ID_SAVE, MenuSave)
	ON_COMMAND(ID_INVERTX, InvertX)
	ON_COMMAND(ID_INVERTY, InvertY)
	ON_COMMAND(ID_NEGATIVERED, NegativeR)
	ON_COMMAND(ID_NEGATIVEGREEN, NegativeG)
	ON_COMMAND(ID_NEGATIVEBLUE, NegativeB)	
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW | WS_VSCROLL | WS_HSCROLL,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	return 0;
}

void CMainFrame::InvertX()//Инверитровать по X
{
	for (int i=0; i < theApp.height-1; i++)
	{
		for (int j = 0; j <theApp.width/2; j++)
		{
		RGBQUAD bmpIntermediate;
		bmpIntermediate = theApp.bmpColor[i * theApp.width + j];
		theApp.bmpColor[i * theApp.width + j] = theApp.bmpColor[(i + 1) * theApp.width - j];
		theApp.bmpColor[(i + 1) * theApp.width - j] = bmpIntermediate;
		}
	}
	if (theApp.flagCheckX == 1)//Ставим/снимаем галочку
	{
		theApp.flagCheckX = 0;
	}
	else
	{
		theApp.flagCheckX = 1;
	}
	Invalidate();

}

void CMainFrame::InvertY()//Инверитровать по Y
{
	for (int i=0; i < theApp.height/2; i++)
	{
		for (int j = 0; j <theApp.width-1; j++)
		{
		RGBQUAD bmpIntermediate;
		bmpIntermediate = theApp.bmpColor[i * theApp.width + j];
		theApp.bmpColor[i * theApp.width + j] = theApp.bmpColor[theApp.width * (theApp.height - i) - (theApp.width - j)];
		theApp.bmpColor[theApp.width * (theApp.height - i) - (theApp.width - j)] = bmpIntermediate;
		}

	}
	if (theApp.flagCheckY == 1)//Ставим/снимаем галочку
	{
		theApp.flagCheckY = 0;
	}
	else
	{
		theApp.flagCheckY = 1;
	}
	Invalidate();
}

void CMainFrame::NegativeR()//Негатив по красному
{
	for (int i=0; i < theApp.height * theApp.width; i++)
	{
		theApp.bmpColor[i].rgbRed = 255 - theApp.bmpColor[i].rgbRed;
	}
	if (theApp.flagCheckR == 1)//Ставим/снимаем галочку
	{
		theApp.flagCheckR = 0;
	}
	else
	{
		theApp.flagCheckR = 1;
	}
	Invalidate();
}

void CMainFrame::NegativeG()//Негатив по зеленому
{
	for (int i=0; i < theApp.height * theApp.width; i++)
	{
		theApp.bmpColor[i].rgbGreen = 255 - theApp.bmpColor[i].rgbGreen;
	}
	if (theApp.flagCheckG == 1)//Ставим/снимаем галочку
	{
		theApp.flagCheckG = 0;
	}
	else
	{
		theApp.flagCheckG = 1;
	}
	Invalidate();
}

void CMainFrame::NegativeB()//Негатив по синиму	
{
	for (int i=0; i < theApp.height * theApp.width; i++)
	{
		theApp.bmpColor[i].rgbBlue = 255 - theApp.bmpColor[i].rgbBlue;
	}
	if (theApp.flagCheckB == 1)//Ставим/снимаем галочку
	{
		theApp.flagCheckB = 0;
	}
	else
	{
		theApp.flagCheckB = 1;
	}
	Invalidate();
}

void CMainFrame::MenuOpen()//Открыть 
{
	CFileDialog fileDialog (TRUE);
	int result = fileDialog.DoModal();
	if (result == IDOK)
	{
		CString path = fileDialog.GetPathName();//Записываем в path путь к файлу
		theApp.loadBMP(path);
		theApp.fileOpen = 1;//Файл прочитан
		Invalidate();
	}
}

void CMainFrame::MenuSave()//Сохранить
{
	CFileDialog fileDialog (FALSE);
	int result = fileDialog.DoModal();
	if (result == IDOK)
	{
		CString path = fileDialog.GetPathName();
		path = path + ".bmp";
		theApp.saveBMP(path);
	}
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
