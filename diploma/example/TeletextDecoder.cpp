#include "stdafx.h"
#include "TeletextDecoder.h"
#include <assert.h>

const int cMagazineCnt = 8;
const int cTeletextTextLength = 40;
const int cTeltextLinesCount = 24;
typedef WCHAR tTText[cTeletextTextLength + 1];
typedef tTText tTTPage[cTeltextLinesCount];

class CTTDecoder : public CTeletextDecoder
{
public:
	CTTDecoder() { InitArrays();  Reset(); }
	~CTTDecoder() override {}
	void Reset() override {
		ZeroMemory(m_TTPage, sizeof(m_TTPage));
		ZeroMemory(m_bWasPageHeader, sizeof(m_bWasPageHeader));
		ZeroMemory(m_bTextIsReady, sizeof(m_bTextIsReady));
		for (int i = 0; i < cMagazineCnt; i++) {
			m_nCurPageIndex[i] = -1;
			m_bCyrillic[i] = false;
		}
	};
	void DecodeTeletext(const BYTE *data, DWORD size) override;
	int GetNextPage(int nStartID) override;
	bool HasPage(int nPageID) override;
	bool HasText(int nPageID) override;
	CString GetText(int nPageID, int nLineLimit) override;

private:
	void InitArrays();
	void DecodePacket(const BYTE *data);
	void DecodeHeader(int nMagazine, const BYTE *data);
	void DecodeText(int nMagazine, int nTextLineID, const BYTE *pData, int nSkip, int nFill);
	void UpdatePage(int nPageIndex);

private:
	BYTE m_cCharFromBits[256];
	tTTPage m_TTPage[cTTPageCount];
	bool m_bWasPageHeader[cTTPageCount];
	bool m_bTextIsReady[cTTPageCount];
	CString m_szReadyText[cTTPageCount];
	int m_nCurPageIndex[cMagazineCnt];
	bool m_bCyrillic[cMagazineCnt];
};

inline BYTE MakeOddParity(BYTE data)
{
	BYTE parity = 0x01;
	BYTE result = 0;
	for (int i = 0; i < 7; i++)
	{
		if ((data & (1 << i)) != 0)
		{
			result |= (1 << (7 - i));
			parity ^= 0x01;
		}
	}
	return result | parity;
}

CTeletextDecoder *CTeletextDecoder::CreateDecoder()
{
	//CString str = _T("\nBYTE data8[128] = {\n");
	//for (int i = 0; i < 128; i++) {
	//	CString s;  s.Format(_T(" 0x%0X,"), MakeOddParity(i));
	//	str += s;
	//}
	//str += _T(" };\n");
	//OutputDebugString(str);
	return new CTTDecoder();
}

int CTTDecoder::GetNextPage(int nStartID)
{
	int nPageID;
	if (nStartID < cTTBasePage || nStartID >= cTTBasePage + cTTPageCount)  nPageID = 0;
	else  nPageID = nStartID - cTTBasePage;
	for (; nPageID < cTTPageCount; nPageID++)
		if (m_bWasPageHeader[nPageID])
			return nPageID + cTTBasePage;
	return -1;
}

bool CTTDecoder::HasPage(int nPageID)
{
	if (nPageID < cTTBasePage || nPageID >= cTTBasePage + cTTPageCount)
		return false;
	return m_bWasPageHeader[nPageID - cTTBasePage];
}

bool CTTDecoder::HasText(int nPageID)
{
	if (nPageID < cTTBasePage || nPageID >= cTTBasePage + cTTPageCount)
		return false;
	return m_bTextIsReady[nPageID - cTTBasePage];
}

CString CTTDecoder::GetText(int nPageID, int nLineLimit)
{
	if (nPageID < cTTBasePage || nPageID >= cTTBasePage + cTTPageCount)
		return _T("");
	m_bTextIsReady[nPageID - cTTBasePage] = false;
	CString str = m_szReadyText[nPageID - cTTBasePage];
	if (nLineLimit < 1 || nLineLimit >= cTeltextLinesCount)
		return str;
	int nSkip = cTeltextLinesCount - nLineLimit;
	int nPos = -1;
	while (nSkip-- > 0) {
		nPos = str.Find(_T('\n'), nPos + 1);
		if (nPos < 0) {
			ATLASSERT(FALSE);
			return _T("");
		}
	}
	return str.Mid(nPos + 1);
}

void CTTDecoder::InitArrays()
{
	for (int code8 = 0; code8 < 256; code8++) {
		BYTE code7 = 0;
		int parity = 1;
		for (int i = 0; i < 7; i++) if (code8 & (0x80 >> i)) {
			code7 |= 0x01 << i;
			parity ^= 1;
		}
		m_cCharFromBits[code8] = parity == (code8 & 0x01) ? code7 : 0x7F;
	}
}

void CTTDecoder::DecodeTeletext(const BYTE *data, DWORD size)
{
	if (data[0] != 0x10)
		return;
	DWORD pos = 1;
	while (pos + 46 <= size) {
		BYTE data_unit_id = data[pos + 0];
		BYTE data_unit_length = data[pos + 1];
		if ((0x02 == data_unit_id || 0x03 == data_unit_id) && 44 == data_unit_length)
			DecodePacket(&data[pos + 4]);
		pos += 2 + data_unit_length;
	}
}

int DecodeHammin8(int code)
{
	int p1 = (code & 0x80) == 0 ? 0 : 1;
	int d1 = (code & 0x40) == 0 ? 0 : 1;
	int p2 = (code & 0x20) == 0 ? 0 : 1;
	int d2 = (code & 0x10) == 0 ? 0 : 1;
	int p3 = (code & 0x08) == 0 ? 0 : 1;
	int d3 = (code & 0x04) == 0 ? 0 : 1;
	int p4 = (code & 0x02) == 0 ? 0 : 1;
	int d4 = (code & 0x01) == 0 ? 0 : 1;
	int A = p1 ^ d1 ^ d3 ^ d4;
	int B = p2 ^ d1 ^ d2 ^ d4;
	int C = p3 ^ d1 ^ d2 ^ d3;
	int D = p1 ^ p2 ^ p3 ^ p4 ^ d1 ^ d2 ^ d3 ^ d4;
	int result = d1 | (d2 << 1) | (d3 << 2) | (d4 << 3);
	if (A == 1 && B == 1 && C == 1)  return result; // all right
	else if (D == 1)  return 999; // double error !!!
	else { // single error
		if (A == 0 && B == 0 && C == 1)  return result ^ 0x08;
		else if (A == 0 && B == 1 && C == 0)  return result ^ 0x04;
		else if (A == 1 && B == 0 && C == 0)  return result ^ 0x03;
		else if (A == 0 && B == 0 && C == 0)  return result ^ 0x01;
		else  return 998;
	}
}

void CTTDecoder::DecodePacket(const BYTE *data)
{
	int nMagazine = DecodeHammin8(data[0]);
	int nPacket = DecodeHammin8(data[1]) << 1;
	if (nMagazine & 0x08) {
		nMagazine &= 0x07;
		nPacket++;
	}
	if (nMagazine < 0 || nMagazine > 7) // wrang data
		return;
	if (nPacket == 0) { // header
		DecodeHeader(nMagazine, &data[2]);
	} else if (nPacket < 24) { // text
		DecodeText(nMagazine, nPacket, &data[2], 0, cTeletextTextLength);
	} else { // other data (non-display)
		return;
	}
}

void CTTDecoder::DecodeHeader(int nMagazine, const BYTE *data)
{
	// reset previous page index
	m_nCurPageIndex[nMagazine] = -1;
	// obtain new page index
	int nPage01 = DecodeHammin8(data[0]);
	int nPage10 = DecodeHammin8(data[1]);
	//int nPage = ((nPage10 & 0x0F) << 4) | (nPage01 & 0x0F);
	if (nPage01 > 9 || nPage10 > 9) // wrang page index
		return;
	int nPage = (nMagazine == 0 ? 800 : nMagazine * 100) + nPage10 * 10 + nPage01 - cTTBasePage;
	assert(nPage < cTTPageCount);
	// check erase bits
	//int SC1 = DecodeHammin8(data[2]);
	int SC2 = DecodeHammin8(data[3]);
	//int SC3 = DecodeHammin8(data[4]);
	//int SC4 = DecodeHammin8(data[5]);
	int SC5 = DecodeHammin8(data[6]);
	int SC6 = DecodeHammin8(data[7]);
	if (SC2 > 15 || SC5 > 15 || SC6 > 15) { // wrang data
		//CString str;
		//str.Format(_T("\n!!!!!!!!!! DecodeTeletext: WRONG page #%d !!!!!!!!!!!!!\n"), nPage + cTTBasePage);
		//OutputDebugString(str);
		return;
	}
	bool bErasePage = false;
	bool bUsePage = true;
	if (SC2 & 0x08)  bErasePage = true;
	if (SC5 & 0x02)  bErasePage = true;
	if (SC5 & 0x08) { bErasePage = true;  bUsePage = false; }
	if (bErasePage) {
		tTText *page = m_TTPage[nPage];
		for (int i = 0; i < cTeltextLinesCount; i++)
			ZeroMemory(page[i], sizeof(tTText));
		m_szReadyText[nPage].Empty();
		m_bTextIsReady[nPage] = true;
	}
	if (bUsePage) {
		m_bWasPageHeader[nPage] = true;
		m_nCurPageIndex[nMagazine] = nPage;
		m_bCyrillic[nMagazine] = (SC6 >> 1) == 0x01;
		DecodeText(nMagazine, 0, &data[8], 8, cTeletextTextLength - 8);
	}
	//if (nPage == 100 - cTTBasePage) {
	//	CString str;
	//	str.Format(_T("\n+++++ DecodeTeletext: START page #%d  SC2=%X, SC5=%X, SC6=%X, use=%d, clear=%d\n"), nPage + cTTBasePage, SC2, SC5, SC6, bUsePage ? 1 : 0, bErasePage ? 1 : 0);
	//	OutputDebugString(str);
	//}
}

#include "TeletextCodePage.h"
const BYTE SYMBOL_ESC = 0x1B;

TCHAR Teletext2Unicode(BYTE code7, bool &bCyrillic)
{
	if (code7 == SYMBOL_ESC) {
		bCyrillic = !bCyrillic;
		return _T(' ');
	}
	else if (code7 <= 0x20 || code7 >= 0x7F) // non printable symbol or space
		return _T(' ');
	else if (bCyrillic) {
		if (code7 >= 0x40 && code7 < 0x7F)
			return cTTRus_x40x7E[code7 - 0x40];
		else if (code7 == 0x26)
			return _T('û');
		else
			return code7;
	}
	else { // non-Cyrillic == Latin
		return code7;
	}
}

void CTTDecoder::DecodeText(int nMagazine, int nTextLineID, const BYTE *pData, int nSkip, int nFill)
{
	int nPage = m_nCurPageIndex[nMagazine];
	bool bCyrillic = m_bCyrillic[nMagazine];
	if (nPage < 0)
		return;
	if (nTextLineID < 0  ||  nTextLineID >= cTeltextLinesCount) // wrang data
		return;
	tTText *page = m_TTPage[nPage];
	WCHAR *text = page[nTextLineID];
	for (int i = 0; i < nSkip; i++)
		text[i] = L' ';
	text += nSkip;
	for (int i = 0; i < nFill; i++)
		text[i] = Teletext2Unicode(m_cCharFromBits[pData[i]], bCyrillic);
	//if (nPage == 100 - cTTBasePage) {
	//	CString str;
	//	str.Format(_T("----- DecodeTeletext: Page #%d, Line #%d, Text='%s'\n"), nPage + cTTBasePage, nTextLineID, text);
	//	OutputDebugString(str);
	//}
	UpdatePage(nPage);
}

void CTTDecoder::UpdatePage(int nPageIndex)
{
	CStringW str;
	tTText *page = m_TTPage[nPageIndex];
	for (int i = 0; i < cTeltextLinesCount; i++) {
		CStringW sss(page[i]);
		str += sss + L"\r\n";
	}
	m_szReadyText[nPageIndex] = str;
	m_bTextIsReady[nPageIndex] = true;
}
