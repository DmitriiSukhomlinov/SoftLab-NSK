// pr2Dlg.h : файл заголовка
//

#pragma once
#include <thread>
#include "afxcmn.h"
#include "afxwin.h"
#include "MyWnd.h"
#include "FIFO_Fix_Size_Of_Buffer.h"
#include "FIFO_Circle_Buffer.h"

// диалоговое окно Cpr2Dlg
class Cpr2Dlg : public CDialogEx
{
// Создание
public:
	Cpr2Dlg(CWnd* pParent = NULL);	
	~Cpr2Dlg();
// Данные диалогового окна
	enum { IDD = IDD_PR2_DIALOG };

    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnDestroy();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV
// Реализация
protected:
	HICON m_hIcon;
	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private://комментарии к функциям - ограничение на использование, какие переменные использует
    typedef enum m_ReadFrameStatus
    {
        Correct,
        No_Free_Memory_In_FIFO,
        Critical_Error_Can_Not_Set_A_Pointer,
        Critical_Error_Can_Not_Read,
        Critical_Error_CoCreateInstance_For_Reading,
        Critical_Error_CoCreateInstance_For_Decode,
        Critical_Error_MainAVIHeader,
        Critical_Error_BITMAPINFO_Size,
        Critical_Error_BITMAPINFO_For_Input,
        Critical_Error_AviStreamHeder,
        Critical_Error_Can_Not_Find_A_Codec,
        Critical_Error_Can_Not_Start_Decompression,
        Critical_Error_File_For_Write,
        Critical_Error_Can_Not_Start_PlayBack,
        Critical_Error_Continue_After_Slide
    }m_ReadFrameStatus;
    
    //Get the AVI file from the 'path', start threads and show first frame
    afx_msg void ClickOpen();
    //Activates the timer, remembers the current time in 'm_nStartTickCount' member and null 'm_nFramesAfterPushPlay' member
    afx_msg void ClickPlay();
    //Kills current timer
    afx_msg void ClickPause();
    //Update the slider and, if it was moved, reset threads and FIFOs
    //Return error MessageBox if the error occurs when drawing a frame
    afx_msg void DrawSlider(NMHDR *pNMHDR, LRESULT *pResult);
    //Is called if the timer was set
    //Stop playback if the slider reaches the end (call ClickPause and kill threads)
    //Call TryNextFrame function
	afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg LRESULT OnWMUSER_1(WPARAM, LPARAM);
    afx_msg LRESULT OnWMUSER_2(WPARAM, LPARAM);
    afx_msg LRESULT OnWMUSER_3(WPARAM, LPARAM);

    //Open selected AVI file if it is possible or return error MessageBox if not
    //pathToFile - a path to the file directory
    bool OpenAVI(CString pathToFile);
    //Initialize the codec for AVI
    bool InitCodec();
    //To free memory
    void Release();
    //Get the frame from FIFO fix size of buffer and show if it possible, if not return false
	bool TryNextFrame();
    //Run read and decode threads
	void ThreadsRun();
    //Change m_bSuicide flag, join both threads and wait for them die
	void ThreadsDeath();
    //Main function of Read thread. Kick TryNextFrame function and handle the result
    void LoopRead();
    //Get the information about the next frame. Kicks itself if its need an information about previous frame (recursion). Push the frame info to the FIFO circle buffer
    //numOfReadFrame - number of current reading frame
    //recursionCheck - a flag which shows recursive this call or not
    m_ReadFrameStatus TryFrameRead(int& numOfReadFrame, bool recursionCheck);
    ///Main function of Decode thread. Get the information from the FIFO circle buffer, decode and kick DecToScale function 
    void LoopDecode();
    //Get last decode frame, scale and push to the FIFO fix size of buffer
	bool DecToScale();
    //Try to show the first frame when AVI was open. Have a cycle for 1000 iterations, each tries to kick TryNextFrame function. 
    bool TryFirstFrame();
    //Reset m_nStartTickCount and m_nFramesAfterPushPlay members when slider has moved
    void ResetDataForSlide();
    //stretch (squeeze) a picture to the size of the output window
    //DataConv - stretched (squeezed) data
    //DataOut - before stretch (squeeze)
    void FrameScale(unsigned char *DataConv, unsigned char *DataOut);

    std::thread m_FrameReader;
	std::thread m_FrameDecoder;
	FIFO_Circle_Buffer m_FifoReadToDec;
    FIFO_Fix_Size_Of_Buffer m_FifoDecToDraw;
	CComPtr <class GETAVIINFOLib::IGetAVIInfo> m_pAVI;
    CComPtr <class ICONVERTIMAGELib::IStretchImage> m_pConverter;
	AVIStreamHeader m_StreamHeader;
	BITMAPINFO* m_pBmpInfoIn;
	BITMAPINFO m_BmpInfoOut;
    HIC m_HIC;
	CString m_strPath;
	bool m_bPlayingNow;
    bool m_bErrorMessageWasShown;
	volatile bool m_bSuicide;
	int m_nLastReadFrame;//number of a frame, which was read last
	int m_nTotalFrames;//quantity of frames in current .avi
	double m_nMiliSecPerFrame;//time, which one frame is displayed (in milliseconds)
	long m_nStartTickCount;//variable, which remember time, when reproduction was began
	double m_nFramesAfterPushPlay;//quantity of frames, which was drawn since reproduction was began
    int m_nFrameNum;//number of the last drawn frame
    //next block of variables is responsible for frame window size
    int m_nScaleWidth;
    int m_nScaleHeight;
    int m_nScaleStride;

	unsigned char* m_pDecodedImage;
	HANDLE m_MyAVI;
    CSliderCtrl m_Progr;
    CButton m_EnablePause;
    CButton m_EnablePlay;
    MyWnd m_Picture;
};
