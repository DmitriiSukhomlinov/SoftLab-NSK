
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "BMPReader.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	X = 0;
	Y = 0;
//	RECT testRect = {0, 0, 100, 100};
//	GetClientRect (&testRect);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	RECT testRect;
	GetClientRect(&testRect);//����� ������ ������� ����

	if (theApp.fileOpen == 1)//���� ������� ����
	{
		if ((theApp.width > testRect.right) && (theApp.height > testRect.bottom))//���� ������ � ������ �������� ������ ����
		{																		 //�� ��� � �������, ��� ������� �� �����
			ShowScrollBar (SB_VERT, true);//���������� ��� �������
			ShowScrollBar (SB_HORZ, true);	
			SetDIBitsToDevice				  		    (dc,//����� �� �����. ��� ����������� ���������� ���������������� � ������� loadBMP
  0 - (X * theApp.width / 100) + (testRect.right * X / 100),
0 - (Y * theApp.height / 100) + (testRect.bottom * Y / 100),
											   theApp.width,
											  theApp.height,
														  0,
														  0,
														  0,
											  theApp.height,
											theApp.bmpColor,
										 &theApp.bmpInfoRGB,
										    DIB_RGB_COLORS);
		}
		else//���� ���-�� �� ����� ������
		{
			if ((theApp.width < testRect.right) && (theApp.height < testRect.bottom))//���� � ������, � ������ ������
			{
				ShowScrollBar (SB_VERT, false);//�������� ��� �������
				ShowScrollBar (SB_HORZ, false);
				SetDIBitsToDevice (dc,
									0,
									0,
						 theApp.width,
						theApp.height,
									0,
									0,
									0,
						theApp.height,
					  theApp.bmpColor,
				   &theApp.bmpInfoRGB,
					  DIB_RGB_COLORS);
			}
			else//���� ������ ���-�� ����
			{
				if (theApp.width < testRect.right)//���� ������ ������
				{
					ShowScrollBar (SB_VERT, true);//���������� ������������
					ShowScrollBar (SB_HORZ, false);//�������� ��������������
					SetDIBitsToDevice					(dc,
								   						  0,
0 - (Y * theApp.height / 100) + (testRect.bottom * Y / 100),
									 		   theApp.width,
											  theApp.height,
														  0,
														  0,
														  0,
											  theApp.height,
											theApp.bmpColor,
										 &theApp.bmpInfoRGB,
											DIB_RGB_COLORS);
				}
				else//���� ������ ������
				{
					ShowScrollBar (SB_VERT, false);//�������� ������������
					ShowScrollBar (SB_HORZ, true);//���������� ��������������
					SetDIBitsToDevice				  (dc,
0 - (X * theApp.width / 100) + (testRect.right * X / 100),
														0,
							  theApp.width, theApp.height,
														0,
														0,
														0,
											theApp.height,
										  theApp.bmpColor,
									   &theApp.bmpInfoRGB,
										  DIB_RGB_COLORS);
				}
			}			
		}
	}


	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)//������������ ������
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	SetScrollRange (SB_VERT, 0, 100);//��������� ������ �� 100 �����
	Y = nPos;
	switch (nSBCode)//��� ������
	{
	case SB_THUMBPOSITION://�������� � �������� ��������	
		SetScrollPos (SB_VERT, nPos);//� ������� �������
		break;
	case SB_ENDSCROLL://��������� ������ � ���������
		Y = GetScrollPos (SB_VERT);//����� ������� �������
		break;
	case SB_LINEUP://��������� �����
		nPos = GetScrollPos (SB_VERT);
		nPos--;
		if (nPos < 0)
		{
			nPos = 0;
		}
		SetScrollPos (SB_VERT, nPos);
		Y = nPos;
		break;
	case SB_LINEDOWN://��������� ����
		nPos = GetScrollPos (SB_VERT);//����� �������
		nPos++;//�����������
		if (nPos > 100)//���� ������ ���������
		{
			nPos = 100;
		}
		SetScrollPos (SB_VERT, nPos);//������ �������
		Y = nPos;
		break;
	}
	Invalidate();//��������� �����
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
	
}


void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	SetScrollRange (SB_HORZ, 0, 100);//��������� ������ �� 100 �����
	X = nPos;
	switch (nSBCode)//��� ������
	{
	case SB_THUMBPOSITION://�������� � �������� ��������
		SetScrollPos (SB_HORZ, nPos);//� ������� �������
		break;
	case SB_ENDSCROLL://��������� ������ � ���������
		X = GetScrollPos (SB_HORZ);//����� ������� �������
		break;
	case SB_LINERIGHT://��������� �����
		nPos = GetScrollPos (SB_HORZ);
		nPos++;
		if (nPos > 100)
		{
			nPos = 100;
		}
		SetScrollPos (SB_HORZ, nPos);
		X = nPos;
		break;
	case SB_LINELEFT://��������� ����
		nPos = GetScrollPos (SB_HORZ);//����� �������
		nPos--;//�����������
		if (nPos < 0)//���� ������ ���������
		{
			nPos = 0;
		}
		SetScrollPos (SB_HORZ, nPos);//������ �������
		X = nPos;
		break;
	}
	Invalidate();//��������� �����

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);

}
