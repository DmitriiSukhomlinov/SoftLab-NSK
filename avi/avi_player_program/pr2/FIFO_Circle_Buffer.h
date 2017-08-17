#pragma once
#include "afxwin.h"
#include <list>
#include <mutex>

class FIFO_Circle_Buffer
{
public:
    //this class has an information about each frame added to FIFO Circle Buffer
    class FifoElement
    {
    public:
        //a pointer to the frame's data
        unsigned char* m_pDataLocate;
        //size of frame
        int m_nSize;
        //key or not key frame
        int m_nKey;
        //need to draw or not
        bool m_bDoNotDraw;

        //default constructor
        FifoElement() : m_pDataLocate(NULL), m_nSize(0), m_nKey(0), m_bDoNotDraw(false){}
    };
    //default constructor
    FIFO_Circle_Buffer();
    //destructor
    ~FIFO_Circle_Buffer();
    //set all values to ready position
    //sizeOfBuffer - 3 max sizes of reading frame
    void InitFIFO(int sizeOfBuffer);
    //reset all members
    void ResetFifo();
    //return a pointer to the buffer if it has enough free space
    //sizeOfFrame - quantity of memory, which necessary in the buffer
	unsigned char* GetFree(int sizeOfFrame);
    //add curent frame to FIFO
    //sizeOfBuffer - quantity of memory, necessary in the buffer
    //key - a flag shows key or not key frame
    //recursionCheck - a flag shows need to draw or not
	void AddReady(int sizeOfFrame, int key, bool recursionCheck);
    //return a flag shows availability of frames in FIFO
    //ptr - a pointer to the place in the buffer, where data starts
    //sizeOfBuffer - quantity of memory, occupied in the buffer
    //key - a flag shows key or not key frame
    //recursionCheck - a flag shows need to draw or not
    bool GetReady(unsigned char*& ptr, int& sizeOfFrame, int& key, bool& recursionCheck);
    //mark current farme as an active, move it from ready to free
	void AddFree();
private:
    int m_nSizeOfBuffer;
    unsigned char* m_pBuffer;
    std::list<FifoElement*> m_Free;
    std::list<FifoElement*> m_Ready;
	std::mutex m_FifoBusy;
    int m_nFreeOffset;
    int m_nReadyOffset;
    int m_nFreeSize;
    int m_nReadySize;
};

