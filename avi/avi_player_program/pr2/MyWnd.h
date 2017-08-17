#pragma once
#include "FIFO_Fix_Size_Of_Buffer.h"
#include "FIFO_Circle_Buffer.h"
// MyWnd

class MyWnd : public CWnd
{
	DECLARE_DYNAMIC(MyWnd)

public:
    //default constructor
	MyWnd();
    //destructor
	virtual ~MyWnd();
    //init an info about output picture
    //width and height - width and height of the output picture
    void Init(int width, int height);
    //copy data to the local buffer and call invalidate
    //DataConv - data to the output picture
    void DrawImage(unsigned char *DataConv);

protected:
    afx_msg void OnPaint();

private:
	unsigned char* m_pDataOutConv;
	BITMAPINFO m_BMPInfoConv;

	DECLARE_MESSAGE_MAP()
};


