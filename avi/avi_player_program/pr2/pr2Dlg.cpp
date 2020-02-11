
// pr2Dlg.cpp : файл реализации

#include "stdafx.h"
#include "pr2.h"
#include "pr2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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

// диалоговое окно Cpr2Dlg

Cpr2Dlg::Cpr2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cpr2Dlg::IDD, pParent)
	, m_nFrameNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAVI = NULL;
    m_pConverter = NULL;
    m_pDecodedImage = NULL;
	m_pBmpInfoIn = NULL;
}

void Cpr2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SLIDER1, m_nFrameNum);
	DDX_Control(pDX, IDC_SLIDER1, m_Progr);
	DDX_Control(pDX, IDC_BUTTON2, m_EnablePlay);
	DDX_Control(pDX, IDC_BUTTON3, m_EnablePause);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
}

BEGIN_MESSAGE_MAP(Cpr2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &Cpr2Dlg::ClickOpen)
    ON_BN_CLICKED(IDC_BUTTON3, &Cpr2Dlg::ClickPause)
    ON_BN_CLICKED(IDC_BUTTON2, &Cpr2Dlg::ClickPlay)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &Cpr2Dlg::DrawSlider)
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
    ON_MESSAGE(WM_USER + 1, OnWMUSER_1)
    ON_MESSAGE(WM_USER + 2, OnWMUSER_2)
    ON_MESSAGE(WM_USER + 3, OnWMUSER_3)
END_MESSAGE_MAP()

// обработчики сообщений Cpr2Dlg

BOOL Cpr2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);
	// TODO: добавьте дополнительную инициализацию
    m_bPlayingNow = false;
    m_bErrorMessageWasShown = false;
	//Buttons disable
	m_EnablePlay.EnableWindow(false);
	m_EnablePause.EnableWindow(false);
	//size of a frame and quantity af added frames
	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_PICTURE);
	pWnd->GetWindowRect(&rect);
    m_nScaleWidth = rect.right - rect.left;
    m_nScaleHeight = rect.bottom - rect.top;
    m_nScaleStride = ((m_nScaleWidth * 3) + 3) & ~3;
    m_Picture.Init(m_nScaleWidth, m_nScaleHeight);
    //init fix size of buffer FIFO
    m_FifoDecToDraw.InitFIFO(m_nScaleStride * m_nScaleHeight, 5);


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

Cpr2Dlg::~Cpr2Dlg()
{
	Release();
}

void Cpr2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

HCURSOR Cpr2Dlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

BOOL Cpr2Dlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void Cpr2Dlg::OnDestroy()
{
    CDialogEx::OnDestroy();
    ThreadsDeath();
}

void Cpr2Dlg::Release()
{
    m_pAVI = NULL;
    m_pConverter = NULL;
    if (m_pDecodedImage != NULL)
	{
        delete[]m_pDecodedImage;
	}
	if (m_pBmpInfoIn!=NULL)
	{
		delete []m_pBmpInfoIn;
	}
}

bool Cpr2Dlg::OpenAVI (CString pathToFile)
{
    //release all pointers to NULL (this function call might be not first)
	Release();

	HRESULT hres = m_pAVI.CoCreateInstance(GETAVIINFOLib::CLSID_GetAVIInfo);
	if (hres != S_OK)
	{
        PostMessage(WM_USER + 2, Critical_Error_CoCreateInstance_For_Reading, 0);
		return false;
	}

    hres = m_pConverter.CoCreateInstance(ICONVERTIMAGELib::CLSID_StretchImage);
    if (hres != S_OK)
    {
        PostMessage(WM_USER + 2, Critical_Error_CoCreateInstance_For_Decode, 0);
        AfxMessageBox(L"Error: can't create CoCreateInstance object for decode");
        return false;
    }

    CComBSTR MyBstr(pathToFile);//convert the format from char to BSTR
	hres = m_pAVI->Load(MyBstr);//read AVI file
	//we don't need MainAVIHeader, we need just .dwTotalFrames
	MainAVIHeader aviHeader;
	long tmp;
	hres = m_pAVI->GetMainHeader((unsigned char*) &aviHeader, sizeof(aviHeader), &tmp);//read MainAVIHeader
	if (hres != S_OK)
	{
        PostMessage(WM_USER + 2, Critical_Error_MainAVIHeader, 0);
		return false;
	}
	m_nTotalFrames = aviHeader.dwTotalFrames;
	//BITMAPINFO size
	long sizeBMPINFO;
	hres = m_pAVI->GetVideoFormatInfo(0, 0, 0, &sizeBMPINFO);
	if (hres != S_OK)
	{
        PostMessage(WM_USER + 2, Critical_Error_BITMAPINFO_Size, 0);
		return false;
	}
	//BITMAPINFO for input data
	m_pBmpInfoIn = (BITMAPINFO*) new unsigned char[sizeBMPINFO];
	hres = m_pAVI->GetVideoFormatInfo(0, (unsigned char*) m_pBmpInfoIn, sizeBMPINFO, &sizeBMPINFO);
	if (hres != S_OK)
	{
        PostMessage(WM_USER + 2, Critical_Error_BITMAPINFO_For_Input, 0);
		return false;
	}
	//BITMAPINFO for output data
	ZeroMemory (&m_BmpInfoOut, sizeof (m_BmpInfoOut));
	m_BmpInfoOut.bmiHeader.biSize = m_pBmpInfoIn->bmiHeader.biSize;
	m_BmpInfoOut.bmiHeader.biWidth = m_pBmpInfoIn->bmiHeader.biWidth;
	m_BmpInfoOut.bmiHeader.biHeight = m_pBmpInfoIn->bmiHeader.biHeight;
	m_BmpInfoOut.bmiHeader.biPlanes = m_pBmpInfoIn->bmiHeader.biPlanes;
	m_BmpInfoOut.bmiHeader.biBitCount = m_pBmpInfoIn->bmiHeader.biBitCount;
	//AVIStreamHeader
	hres = m_pAVI->GetVideoStreamInfo(0, (unsigned char*) &m_StreamHeader, sizeof(m_StreamHeader), &tmp, NULL, NULL);
	if (hres != S_OK)
	{
        PostMessage(WM_USER + 2, Critical_Error_AviStreamHeder, 0);
		return false;
	}
	m_nMiliSecPerFrame = 1000 * m_StreamHeader.dwScale / m_StreamHeader.dwRate;//milliseconds per frame

    //search for maximum size of frame, which might be read
	unsigned long maxSizeOfFrame = 0;
	for (int i = 0; i < m_nTotalFrames; i++)
	{
		long hiOf;
		unsigned long lowOf;
		unsigned long size;
		m_pAVI->GetVideoFrameInfo(0, i, &hiOf, &lowOf, &size);
		if (size > maxSizeOfFrame)
		{
			maxSizeOfFrame = size;
		}
	}
    m_pDecodedImage = new unsigned char[m_pBmpInfoIn->bmiHeader.biWidth*m_pBmpInfoIn->bmiHeader.biHeight * 3];
    //init circle buffer FIFO
    m_FifoReadToDec.InitFIFO(maxSizeOfFrame * 3);
	return true;
}

bool Cpr2Dlg::InitCodec()//Codec definition
{
    m_HIC = ICOpen(ICTYPE_VIDEO, m_StreamHeader.fccHandler, ICMODE_DECOMPRESS);//open file for decompression
    if (m_HIC == 0)//if it didn't work...
	{
        m_HIC = ICLocate(ICTYPE_VIDEO, m_StreamHeader.fccHandler, &m_pBmpInfoIn->bmiHeader, &m_BmpInfoOut.bmiHeader, ICMODE_DECOMPRESS);//...try to find a codec automatically
        if (m_HIC == 0)//if it didn't work too...
		{
            PostMessage(WM_USER + 2, Critical_Error_Can_Not_Find_A_Codec, 0);//...return error message
			return false;
		}
	}
	ICINFO codecInfo;//wanna know a codec type
    ICGetInfo(m_HIC, &codecInfo, sizeof(ICINFO));
    if (ICDecompressBegin(m_HIC, m_pBmpInfoIn, &m_BmpInfoOut) == ICERR_BADFORMAT)//start decompression
	{
        PostMessage(WM_USER + 2, Critical_Error_Can_Not_Start_Decompression, 0);
		return false;
	}
	return true;
}

void Cpr2Dlg::ThreadsRun()
{
	m_bSuicide = false;
    m_FrameReader = std::thread(&Cpr2Dlg::LoopRead, this);
    m_FrameDecoder = std::thread(&Cpr2Dlg::LoopDecode, this);
}

void Cpr2Dlg::ThreadsDeath()
{
	m_bSuicide = true;
    if (m_FrameReader.joinable()) m_FrameReader.join();
    if (m_FrameDecoder.joinable()) m_FrameDecoder.join();
}

void Cpr2Dlg::LoopRead()
{
    int nNumOfReadFrame = m_nFrameNum;
    while (!m_bSuicide)
    {
        if ((nNumOfReadFrame < 0) || (nNumOfReadFrame >= m_nTotalFrames))
            return;

        Cpr2Dlg::m_ReadFrameStatus currentStatus = TryFrameRead(nNumOfReadFrame, false);
        switch (currentStatus)
        {
        case Correct:
            nNumOfReadFrame++;
            break;
        case No_Free_Memory_In_FIFO:
            Sleep(10);
            break;
        case Critical_Error_Can_Not_Set_A_Pointer:
            PostMessage(WM_USER + 1, Critical_Error_Can_Not_Set_A_Pointer, 0);
            return;
        case Critical_Error_Can_Not_Read:
            PostMessage(WM_USER + 1, Critical_Error_Can_Not_Read, 0);
            AfxMessageBox(L"Error: can't set a pointer to the frame");
            return;
        }
    }
}

Cpr2Dlg::m_ReadFrameStatus Cpr2Dlg::TryFrameRead(int& numOfReadFrame, bool recursionCheck)
{
    long hiOf;
    unsigned long lowOf;
    unsigned long sizeOfFrame;
    unsigned long key;
    m_pAVI->GetVideoFrameInf(0, numOfReadFrame, &hiOf, &lowOf, &sizeOfFrame, &key);
    if (((key == 0) || (sizeOfFrame == 0)) && (numOfReadFrame != m_nLastReadFrame + 1))
    {
        int numOfFrameToRecursion = numOfReadFrame - 1;
        m_ReadFrameStatus currentStatus = TryFrameRead(numOfFrameToRecursion, true);
        if (currentStatus == No_Free_Memory_In_FIFO)
            return No_Free_Memory_In_FIFO;
    }
    unsigned char* pDataIn = m_FifoReadToDec.GetFree(sizeOfFrame);
    if (pDataIn == NULL)
        return No_Free_Memory_In_FIFO;
    if (!SetFilePointer(m_MyAVI, lowOf, &hiOf, FILE_BEGIN))
        return Critical_Error_Can_Not_Set_A_Pointer;
    unsigned long bytesRead;
    if (!ReadFile(m_MyAVI, pDataIn, sizeOfFrame, &bytesRead, NULL))
    {
        return Critical_Error_Can_Not_Read;
    }
    m_FifoReadToDec.AddReady(sizeOfFrame, key, recursionCheck);
    m_nLastReadFrame = numOfReadFrame;
    return Correct;
}

void Cpr2Dlg::LoopDecode()
{
    while (!m_bSuicide)
    {
        unsigned char* pDataOut;
        int nSize;
        int nKey;
        bool bDoNotDraw;
        if (!m_FifoReadToDec.GetReady(pDataOut, nSize, nKey, bDoNotDraw))
        {
            Sleep(10);
            continue;
        }
        m_pBmpInfoIn->bmiHeader.biSizeImage = nSize;
        //if decode failed this mistake is not critical
        DWORD res = ICDecompress(m_HIC, nKey == 0 ? ICDECOMPRESS_NOTKEYFRAME : 0, &m_pBmpInfoIn->bmiHeader, pDataOut, &m_BmpInfoOut.bmiHeader, m_pDecodedImage);
        m_FifoReadToDec.AddFree();
        if (res != ICERR_OK)
            continue;
        if (bDoNotDraw)
            continue;
        //scaling of a frame, which was decoded just now
        while (!DecToScale())
        {
            if (m_bSuicide)
                return;
            Sleep(10);
        }
    }
}

bool Cpr2Dlg::DecToScale()
{
    unsigned char* decToScale = m_FifoDecToDraw.GetFree();
    if (decToScale == NULL)
        return false;
    FrameScale(decToScale, m_pDecodedImage);
    m_FifoDecToDraw.AddReady();
    return true;
}

void Cpr2Dlg::FrameScale(unsigned char *DataConv, unsigned char *DataOut)
{
    m_pConverter->StretchImage(DataConv,
                               DataOut,
                               m_nScaleWidth,
                               m_nScaleHeight,
                               m_BmpInfoOut.bmiHeader.biWidth,
                               m_BmpInfoOut.bmiHeader.biHeight,
                               m_nScaleStride,
                               m_BmpInfoOut.bmiHeader.biWidth * 3,
                               7);
}

void Cpr2Dlg::ClickOpen()
{
    //open file
	CFileDialog fileDialog(TRUE);
    if (fileDialog.DoModal() == IDOK)//invoke the modal dialog box
	{
		m_strPath = fileDialog.GetPathName();//path to the file
		if(!OpenAVI(m_strPath))
            return;
	}
	else
        return;
	if (!InitCodec())
        return;
    //create file
    m_MyAVI = CreateFile(m_strPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (m_MyAVI == INVALID_HANDLE_VALUE)
	{
        PostMessage(WM_USER + 2, Critical_Error_File_For_Write, 0);
		return;
	}
	//set initial data for new file
	CSliderCtrl* sliderCtrl = (CSliderCtrl*) this->GetDlgItem(IDC_SLIDER1);//create slider
    sliderCtrl->SetRangeMin(0);
    sliderCtrl->SetRangeMax(m_nTotalFrames - 1);
    m_nFrameNum = 0;
	m_Progr.SetPos(m_nFrameNum);
	ThreadsRun();
    if (!TryFirstFrame())
    {
        if (!m_bSuicide)
        {
            PostMessage(WM_USER + 3, Critical_Error_Can_Not_Start_PlayBack, 0);
        }
        return;
    }
    m_EnablePlay.EnableWindow(true);
    m_EnablePause.EnableWindow(true);
}


void Cpr2Dlg::ClickPlay()
{
    if (!m_bPlayingNow)
	{
		SetTimer(1, 10, NULL);
        m_bPlayingNow = true;
		m_nStartTickCount = GetTickCount();
		m_nFramesAfterPushPlay = 0;
	}
}

void Cpr2Dlg::ClickPause()
{
    if (m_bPlayingNow)
	{
		KillTimer (1);
        m_bPlayingNow = false;
		m_nFramesAfterPushPlay = -1;
	}
}

void Cpr2Dlg::DrawSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
		if (m_nFrameNum != m_Progr.GetPos())//if move a slider
		{
			SetCursor(LoadCursor(NULL, IDC_WAIT));
			m_nFrameNum = m_Progr.GetPos();
			ThreadsDeath();
            m_FifoReadToDec.ResetFifo();
            m_FifoDecToDraw.ResetFIFO();
            ResetDataForSlide();
            ThreadsRun();
            if ((!TryFirstFrame()) && (!m_bSuicide))
            {
                PostMessage(WM_USER + 3, Critical_Error_Continue_After_Slide, 0);
            }
			SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
	*pResult = 0;
}

void Cpr2Dlg::ResetDataForSlide()
{
    m_nStartTickCount = GetTickCount();
    m_nFramesAfterPushPlay = 0;
}

void Cpr2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 1)
	{
		if (m_nFrameNum == m_nTotalFrames)
		{
            ClickPause();
            ThreadsDeath();
			return;
		}
		TryNextFrame();
	}
	CDialogEx::OnTimer(nIDEvent);
}

bool Cpr2Dlg::TryNextFrame()
{
    //return, if it is not time to draw a frame
    if ((GetTickCount() - m_nStartTickCount) < m_nMiliSecPerFrame*m_nFramesAfterPushPlay)
        return false;
    //return, if the is now ready frames in FIFO
    unsigned char* ptr = m_FifoDecToDraw.GetReady();
    if (ptr == NULL)
        return false;

    m_Picture.DrawImage(ptr);
    m_FifoDecToDraw.AddFree();
    m_Progr.SetPos(m_nFrameNum);
    //show a number of a frame, which was drawn
    WCHAR cNumInChar[10];
    wsprintf(cNumInChar, L"%d", m_nFrameNum);
    SetDlgItemText(IDC_NUM, cNumInChar);
    //update counts
    m_nFramesAfterPushPlay++;
    m_nFrameNum++;
	return true;
}

bool Cpr2Dlg::TryFirstFrame()
{
    for (int i = 0; i < 500; i++)
    {
        if (TryNextFrame())
        {
            return true;
        }
        Sleep(2);
    }
    return false;
}

LRESULT Cpr2Dlg::OnWMUSER_1(WPARAM message, LPARAM)
{
    ClickPause();
    m_bSuicide = true;
    if (m_FrameDecoder.joinable())
        m_FrameDecoder.join();
    CString errorMessage;
    switch (message)
    {
    case Critical_Error_Can_Not_Set_A_Pointer:
        errorMessage = "Error: can't set a pointer to the frame";
        break;
    case Critical_Error_Can_Not_Read:
        errorMessage = "Error: can't set a pointer to the frame";
        break;
    }
    if (!m_bErrorMessageWasShown)
    {
        m_bErrorMessageWasShown = true;
        AfxMessageBox(errorMessage);
    }
    return LRESULT();
}

LRESULT Cpr2Dlg::OnWMUSER_2(WPARAM message, LPARAM)
{
    CString errorMessage;
    switch (message)
    {
    case Critical_Error_CoCreateInstance_For_Reading:
        errorMessage = "Error: can't create CoCreateInstance object for data reading";
        break;
    case Critical_Error_CoCreateInstance_For_Decode:
        errorMessage = "Error: can't create CoCreateInstance object for decode";
        break;
    case Critical_Error_MainAVIHeader:
        errorMessage = "Error: can't read MainAVIHeader";
        break;
    case Critical_Error_BITMAPINFO_Size:
        errorMessage = "Error: can't read BITMAPINFO size";
        break;
    case Critical_Error_BITMAPINFO_For_Input:
        errorMessage = "Error: can't read BITMAPINFO for input";
        break;
    case Critical_Error_AviStreamHeder:
        errorMessage = "Error: can't read AVIStreamHeader";
        break;
    case Critical_Error_Can_Not_Find_A_Codec:
        errorMessage = "Error: can't find a codec";
        break;
    case Critical_Error_Can_Not_Start_Decompression:
        errorMessage = "Error: can't start decompression";
        break;
    case Critical_Error_File_For_Write:
        errorMessage = "Error: can't create file for write";
        break;
    }
    if (!m_bErrorMessageWasShown)
    {
        m_bErrorMessageWasShown = true;
        AfxMessageBox(errorMessage);
    }
    return LRESULT();
}

LRESULT Cpr2Dlg::OnWMUSER_3(WPARAM message, LPARAM)
{
    ThreadsDeath();
    CString errorMessage;
    switch (message)
    {
    case Critical_Error_Can_Not_Start_PlayBack:
        errorMessage = "Error: can't start playback";
        ThreadsDeath();
        break;
    case Critical_Error_Continue_After_Slide:
        errorMessage = "Error: can't continue playback after slider move";
        break;
    }
    if (!m_bErrorMessageWasShown)
    {
        m_bErrorMessageWasShown = true;
        AfxMessageBox(errorMessage);
    }
    return LRESULT();
}

