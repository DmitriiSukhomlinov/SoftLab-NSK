// MyWnd.cpp: файл реализации
//

#include "stdafx.h"
#include "MyWnd.h"
#include "FIFO_Circle_Buffer.h"
#include "FIFO_Fix_Size_Of_Buffer.h"



// MyWnd

IMPLEMENT_DYNAMIC(MyWnd, CWnd)

MyWnd::MyWnd()
{
}


MyWnd::~MyWnd()
{
	delete[]m_pDataOutConv;
}

BEGIN_MESSAGE_MAP(MyWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void MyWnd::Init(int width, int height)
{
    ZeroMemory(&m_BMPInfoConv, sizeof(BITMAPINFO));
    m_BMPInfoConv.bmiHeader.biSize = 40;
    m_BMPInfoConv.bmiHeader.biWidth = width;
    m_BMPInfoConv.bmiHeader.biHeight = height;
    m_BMPInfoConv.bmiHeader.biPlanes = 1;
    m_BMPInfoConv.bmiHeader.biBitCount = 24;
    m_BMPInfoConv.bmiHeader.biSizeImage = (((width * 3) + 3) & ~3) * height;
    m_pDataOutConv = new unsigned char[m_BMPInfoConv.bmiHeader.biSizeImage];
}

void MyWnd::DrawImage(unsigned char *DataConv)
{
    CopyMemory(m_pDataOutConv, DataConv, m_BMPInfoConv.bmiHeader.biSizeImage);
    Invalidate(false);
}

void MyWnd::OnPaint()
{
	CPaintDC dc(this); 
    HRESULT re = SetDIBitsToDevice(dc, 0, 0, m_BMPInfoConv.bmiHeader.biWidth, m_BMPInfoConv.bmiHeader.biHeight, 0, 0, 0, m_BMPInfoConv.bmiHeader.biHeight, m_pDataOutConv, &m_BMPInfoConv, DIB_RGB_COLORS);
}

// обработчики сообщений MyWnd