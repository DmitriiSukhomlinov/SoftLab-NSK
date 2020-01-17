#pragma once

const int cTTBasePage = 100;
const int cTTPageCount = 800;

class CTeletextDecoder
{
public:
	CTeletextDecoder() {}
	virtual ~CTeletextDecoder() {}
	virtual void Reset() = 0;
	virtual void DecodeTeletext(const BYTE *data, DWORD size) = 0;
	virtual int GetNextPage(int nStartID) = 0;
	virtual bool HasPage(int nPageID) = 0;
	virtual bool HasText(int nPageID) = 0;
	virtual CString GetText(int nPageID, int nLineLimit) = 0;
	static CTeletextDecoder *CreateDecoder();
};
