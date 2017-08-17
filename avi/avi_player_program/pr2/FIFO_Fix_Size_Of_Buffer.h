#pragma once
#include "afxwin.h"
#include <list>
#include <mutex>

class FIFO_Fix_Size_Of_Buffer : public CWnd
{
public:
    //default constructor
    FIFO_Fix_Size_Of_Buffer();
    //destructor
    ~FIFO_Fix_Size_Of_Buffer();
    //set all values to ready position
    //sizeOfBuffer - quantity of pixels in one picture
    void InitFIFO(int SizeOFBuffer, int BuffersNumber);
    //reset all members
    void ResetFIFO();
    //return a pointer to the free buffer if it has enough free space
    unsigned char* GetFree();
    //mark curent free frame as ready
    void AddReady();
    //return a pointer to the first buffer with ready to use data (if exist)
    unsigned char* GetReady();
    //mark first ready buffer as free
    void AddFree();
private:
    unsigned char* m_pBuffer;
    std::list<unsigned char*> m_Free;
    std::list<unsigned char*> m_Ready;
    std::mutex m_FifoBusy;
};
