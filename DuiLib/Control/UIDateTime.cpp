#include "stdafx.h"

#include <regex>

namespace DuiLib {

CDateTimeUI::CDateTimeUI(void)
    : m_Style(DTS_SHORTDATEFORMAT)
{
}


CDateTimeUI::~CDateTimeUI(void)
{
}

void CDateTimeUI::Init()
{
    __super::Init();

    RECT rc = GetPos();
    HWND hWnd = CreateWindowEx(0, DATETIMEPICK_CLASS, _T("DateTime"),
        WS_CHILD | m_Style, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
        GetManager()->GetPaintWindow(), NULL, ::GetModuleHandle(NULL), NULL);
    Attach(hWnd);
    TFontInfo *pf = GetManager()->GetFontInfo(GetFont());
    LOGFONT lf = { 0 };
    ::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
    _tcsncpy(lf.lfFaceName, pf->sFontName, LF_FACESIZE);
    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfHeight = -pf->iSize;
    if( pf->bBold ) lf.lfWeight += FW_BOLD;
    if( pf->bUnderline ) lf.lfUnderline = TRUE;
    if( pf->bItalic ) lf.lfItalic = TRUE;
    HFONT hFont = ::CreateFontIndirect(&lf);
    SetWindowFont(m_hWnd, hFont, FALSE);
    
    SetVisible(true);
}

void CDateTimeUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
    if (_tcscmp(pstrName, _T("style")) == 0)
    {
        if (_tcscmp(pstrValue, _T("date")) == 0) m_Style = DTS_SHORTDATEFORMAT;
        if (_tcscmp(pstrValue, _T("time")) == 0) m_Style = DTS_TIMEFORMAT;
    }
    __super::SetAttribute(pstrName, pstrValue);
}

SYSTEMTIME CDateTimeUI::GetSystemTime(void)
{
    SYSTEMTIME st = {0};
    ::SendMessage(m_hWnd, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
    return st;
}

void CDateTimeUI::SetSystemTime(const SYSTEMTIME &st)
{
    ::SendMessage(m_hWnd, DTM_SETSYSTEMTIME, 0, (LPARAM)&st);
}

void CDateTimeUI::SetDateTime(const CDuiString &datetime)
{
    SYSTEMTIME st = {0};
    _stscanf(datetime, _T("%04d-%02d-%02d %02d:%02d:%02d"),
        &st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond);
    ::SendMessage(m_hWnd, DTM_SETSYSTEMTIME, 0, (LPARAM)&st);
}

DuiLib::CDuiString CDateTimeUI::GetDateTime(void)
{
    SYSTEMTIME st = {0};
    ::SendMessage(m_hWnd, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
    CDuiString str;
    str.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
        st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
    return str;
}

void CDateTimeUI::SetDate(const CDuiString &date)
{
    SYSTEMTIME st = {0};
    _stscanf(date, _T("%04d-%02d-%02d"),
        &st.wYear, &st.wMonth, &st.wDay);
    ::SendMessage(m_hWnd, DTM_SETSYSTEMTIME, 0, (LPARAM)&st);
}

DuiLib::CDuiString CDateTimeUI::GetDate(void)
{
    SYSTEMTIME st = {0};
    ::SendMessage(m_hWnd, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
    CDuiString str;
    str.Format(_T("%04d-%02d-%02d"),
        st.wYear, st.wMonth, st.wDay);
    return str;
}

void CDateTimeUI::SetTime(const CDuiString &time)
{
    SYSTEMTIME st = {0};
    ::GetSystemTime(&st);
    _stscanf(time, _T("%02d:%02d:%02d"),
        &st.wHour, &st.wMinute, &st.wSecond);
    ::SendMessage(m_hWnd, DTM_SETSYSTEMTIME, 0, (LPARAM)&st);
}

DuiLib::CDuiString CDateTimeUI::GetTime(void)
{
    SYSTEMTIME st = {0};
    ::SendMessage(m_hWnd, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
    CDuiString str;
    str.Format(_T("%02d:%02d:%02d"),
        st.wHour, st.wMinute, st.wSecond);
    return str;
}

}
