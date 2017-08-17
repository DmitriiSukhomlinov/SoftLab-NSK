#include "stdafx.h"
#include "FIFO_Circle_Buffer.h"


FIFO_Circle_Buffer::FIFO_Circle_Buffer()
{
    m_pBuffer = NULL;
}

FIFO_Circle_Buffer::~FIFO_Circle_Buffer()
{
    delete[]m_pBuffer;
    while(!m_Free.empty())
    {
        delete m_Free.front();
        m_Free.pop_front();
    }
    while (!m_Ready.empty())
    {
        delete m_Ready.front();
        m_Ready.pop_front();
    }
}

void FIFO_Circle_Buffer::InitFIFO(int SizeOfBuffer)
{
    m_Ready.resize(0);
    m_Free.resize(0);
    for (int i = 0; i < 10; i++)
    {
        m_Free.push_back(new FifoElement());
    }
    m_nSizeOfBuffer = SizeOfBuffer;
    m_pBuffer = new unsigned char[m_nSizeOfBuffer];
    m_nFreeOffset = 0;
    m_nReadyOffset = 0;
    m_nFreeSize = m_nSizeOfBuffer;
    m_nReadySize = 0;
}

void FIFO_Circle_Buffer::ResetFifo()
{
    int size = m_Ready.size();
    for (int i = 0; i < size; i++)
    {
        m_Free.push_front(m_Ready.front());
        m_Ready.pop_front();
    }
    m_nFreeOffset = 0;
    m_nReadyOffset = 0;
    m_nFreeSize = m_nSizeOfBuffer;
    m_nReadySize = 0;
}

unsigned char* FIFO_Circle_Buffer::GetFree(int sizeOfFrame)//1
{
    unsigned char* ptr = NULL;
    if (m_nFreeSize < sizeOfFrame) {
        return NULL;
    }

    m_FifoBusy.lock();
    if (m_nReadyOffset >= m_nFreeOffset) {
        if (m_nReadySize == 0) {
            m_nFreeOffset = 0;
            m_nReadyOffset = 0;
        }
        ptr = &m_pBuffer[m_nFreeOffset];
    }
    else if (m_nSizeOfBuffer - m_nFreeOffset >= sizeOfFrame) {
        ptr = &m_pBuffer[m_nFreeOffset];
    }
    else if (m_nReadyOffset >= sizeOfFrame) {
        m_nFreeSize -= m_nSizeOfBuffer - m_nFreeOffset;
        m_nFreeOffset = 0;
        ptr = &m_pBuffer[m_nFreeOffset];
    }
    m_FifoBusy.unlock();
    return ptr;
}

void FIFO_Circle_Buffer::AddReady(int sizeOfFrame, int key, bool doNotDraw)//2
{
	m_FifoBusy.lock();
    FifoElement* fifo = m_Free.back();
    fifo->m_pDataLocate = &m_pBuffer[m_nFreeOffset];
    fifo->m_nSize = sizeOfFrame;
    fifo->m_nKey = key;
    fifo->m_bDoNotDraw = doNotDraw;
    m_nReadySize += sizeOfFrame;
    assert(m_nReadySize <= m_nSizeOfBuffer);
    m_nFreeSize -= sizeOfFrame;
    assert(m_nFreeSize >= 0);
    m_nFreeOffset += sizeOfFrame;
    if (m_nFreeOffset >= m_nSizeOfBuffer) {
        m_nFreeOffset -= m_nSizeOfBuffer;
    }
    assert((m_nFreeOffset <= m_nSizeOfBuffer) && (m_nFreeOffset >= 0));
    m_Free.pop_back();
    m_Ready.push_back(fifo);
	m_FifoBusy.unlock();
}

bool FIFO_Circle_Buffer::GetReady(unsigned char*& ptr, int& sizeOfFrame, int& key, bool& recursionCheck)//3
{
    if (m_nReadySize == 0) {
        return false;
    }

    m_FifoBusy.lock();
    FifoElement* fifo = m_Ready.front();
    ptr = fifo->m_pDataLocate;
    sizeOfFrame = fifo->m_nSize;
    key = fifo->m_nKey;
    recursionCheck = fifo->m_bDoNotDraw;
    m_FifoBusy.unlock();
    return true;
}

void FIFO_Circle_Buffer::AddFree()//4
{
    m_FifoBusy.lock();
    FifoElement* fifo = m_Ready.front();
    m_Ready.pop_front();
    int size = fifo->m_nSize;
    int skip = 0;
    if (fifo->m_pDataLocate != &m_pBuffer[m_nReadyOffset]) {
        skip = fifo->m_pDataLocate - &m_pBuffer[m_nReadyOffset];
        if (skip < 0) {
            skip += m_nSizeOfBuffer;
        }
    }
    m_nFreeSize += (size + skip);
    assert(m_nFreeSize <= m_nSizeOfBuffer);
    m_nReadySize -= size;
    assert(m_nReadySize >= 0);
    m_nReadyOffset += (size + skip);
    if (m_nReadyOffset >= m_nSizeOfBuffer) {
        m_nReadyOffset -= m_nSizeOfBuffer;
    }
    assert((m_nReadyOffset >= 0) && (m_nReadyOffset <= m_nSizeOfBuffer));
    m_Free.push_back(fifo);
    m_FifoBusy.unlock();
}
