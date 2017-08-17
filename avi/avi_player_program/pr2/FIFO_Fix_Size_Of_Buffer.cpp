#include "stdafx.h"
#include "FIFO_Fix_Size_Of_Buffer.h"


FIFO_Fix_Size_Of_Buffer::FIFO_Fix_Size_Of_Buffer()
{
    int size = m_Ready.size();
    for (int i = 0; i < size; i++)
    {
        m_Free.push_front(m_Ready.front());
        m_Ready.pop_front();
    }
}


FIFO_Fix_Size_Of_Buffer::~FIFO_Fix_Size_Of_Buffer()
{
    while (!m_Free.empty())
    {
        delete m_Free.back();
        m_Free.pop_back();
    }
    while (!m_Ready.empty())
    {
        delete m_Ready.back();
        m_Ready.pop_back();
    }
}

void  FIFO_Fix_Size_Of_Buffer::InitFIFO(int SizeOfBuffer, int BuffersNumber)
{
    for (int i = 0; i < BuffersNumber; i++)
    {
        m_Free.push_back(new unsigned char[SizeOfBuffer]);
    }
}

void FIFO_Fix_Size_Of_Buffer::ResetFIFO()
{
    int size = m_Ready.size();
    for (int i = 0; i < size; i++)
    {
        m_Free.push_front(m_Ready.front());
        m_Ready.pop_front();
    }
}

unsigned char* FIFO_Fix_Size_Of_Buffer::GetFree()
{
    unsigned char* ptr = NULL;
    m_FifoBusy.lock();
    if (!m_Free.empty())
    {
        ptr = m_Free.back();
    }
    m_FifoBusy.unlock();
    return ptr;
}

void FIFO_Fix_Size_Of_Buffer::AddReady()
{
    m_FifoBusy.lock();
    if (!m_Free.empty())
    {
        m_Ready.push_back(m_Free.back());
        m_Free.pop_back();
    }
    m_FifoBusy.unlock();
}

unsigned char* FIFO_Fix_Size_Of_Buffer::GetReady()
{
    unsigned char* ptr = NULL;
    m_FifoBusy.lock();
    if (!m_Ready.empty()) ptr = m_Ready.front();
    m_FifoBusy.unlock();
    return ptr;
}

void FIFO_Fix_Size_Of_Buffer::AddFree()
{
    m_FifoBusy.lock();
    if (!m_Ready.empty())
    {
        m_Free.push_front(m_Ready.front());
        m_Ready.pop_front();
    }
    m_FifoBusy.unlock();
}