
// BMPReader.h : main header file for the BMPReader application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

//	char* fname;
// CBMPReaderApp:
// See BMPReader.cpp for the implementation of this class
//

class CBMPReaderApp : public CWinApp
{
public:
	CBMPReaderApp();
	int loadBMP(CString fname);
	int saveBMP(CString fname);
	bool fileOpen;
	int height;
	int width;
	BITMAPFILEHEADER bmpHeader;//Хедер нашего файла
	BITMAPINFOHEADER bmpInfo;//Инфо нашего файла
	RGBQUAD* bmpColor;
	BITMAPINFO bmpInfoRGB;//Инфо нашего файла
	//Флаги
	bool flagEdit;//Флаг доступности меню редактирования
	int	 flagCheckX,//Флаг галочек пунктов меню
		 flagCheckY,
		 flagCheckR,
		 flagCheckG,
		 flagCheckB;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnUpdateInvertx(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInverty(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNegativered(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNegativegreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNegativeblue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSave(CCmdUI *pCmdUI);
};

extern CBMPReaderApp theApp;
