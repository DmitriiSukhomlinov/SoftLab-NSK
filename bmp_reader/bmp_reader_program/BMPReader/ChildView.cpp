
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
	GetClientRect(&testRect);//Нужно узнать размеры окна

	if (theApp.fileOpen == 1)//Если открыли файл
	{
		if ((theApp.width > testRect.right) && (theApp.height > testRect.bottom))//Если высота и ширина картинки меньше окна
		{																		 //То все в порядке, все скроллы на месте
			ShowScrollBar (SB_VERT, true);//Показываем оба скролла
			ShowScrollBar (SB_HORZ, true);	
			SetDIBitsToDevice				  		    (dc,//Вывод на экран. Все необходимые переменные инициализируются в функции loadBMP
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
		else//Если что-то из этого больше
		{
			if ((theApp.width < testRect.right) && (theApp.height < testRect.bottom))//Если и высота, и ширина больше
			{
				ShowScrollBar (SB_VERT, false);//Скрываем оба скролла
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
			else//Если только что-то одно
			{
				if (theApp.width < testRect.right)//Если ширина больше
				{
					ShowScrollBar (SB_VERT, true);//Показываем вертикальный
					ShowScrollBar (SB_HORZ, false);//Скрываем горизонтальный
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
				else//Если высота больше
				{
					ShowScrollBar (SB_VERT, false);//Скрываем вертикальный
					ShowScrollBar (SB_HORZ, true);//Показываем горизонтальный
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



void CChildView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)//Вертикальный скролл
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	SetScrollRange (SB_VERT, 0, 100);//Разделяем скролл на 100 ячеек
	Y = nPos;
	switch (nSBCode)//Что делаем
	{
	case SB_THUMBPOSITION://Зацепить и потащить ползунок	
		SetScrollPos (SB_VERT, nPos);//В текущую позицию
		break;
	case SB_ENDSCROLL://Закончить работу с ползунком
		Y = GetScrollPos (SB_VERT);//Взять текущую позицию
		break;
	case SB_LINEUP://Стрелочка вверх
		nPos = GetScrollPos (SB_VERT);
		nPos--;
		if (nPos < 0)
		{
			nPos = 0;
		}
		SetScrollPos (SB_VERT, nPos);
		Y = nPos;
		break;
	case SB_LINEDOWN://Стрелочка вниз
		nPos = GetScrollPos (SB_VERT);//Берем позицию
		nPos++;//Увеличиваем
		if (nPos > 100)//Если больше максимума
		{
			nPos = 100;
		}
		SetScrollPos (SB_VERT, nPos);//Задаем позицию
		Y = nPos;
		break;
	}
	Invalidate();//Обновляем экран
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
	
}


void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	SetScrollRange (SB_HORZ, 0, 100);//Разделяем скролл на 100 ячеек
	X = nPos;
	switch (nSBCode)//Что делаем
	{
	case SB_THUMBPOSITION://Зацепить и потащить ползунок
		SetScrollPos (SB_HORZ, nPos);//В текущую позицию
		break;
	case SB_ENDSCROLL://Закончить работу с ползунком
		X = GetScrollPos (SB_HORZ);//Взять текущую позицию
		break;
	case SB_LINERIGHT://Стрелочка вверх
		nPos = GetScrollPos (SB_HORZ);
		nPos++;
		if (nPos > 100)
		{
			nPos = 100;
		}
		SetScrollPos (SB_HORZ, nPos);
		X = nPos;
		break;
	case SB_LINELEFT://Стрелочка вниз
		nPos = GetScrollPos (SB_HORZ);//Берем позицию
		nPos--;//Увеличиваем
		if (nPos < 0)//Если больше максимума
		{
			nPos = 0;
		}
		SetScrollPos (SB_HORZ, nPos);//Задаем позицию
		X = nPos;
		break;
	}
	Invalidate();//Обновляем экран

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);

}
