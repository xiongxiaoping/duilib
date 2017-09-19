#include "stdafx.h"

namespace DuiLib {

CWin32WndUI::CWin32WndUI(void)
    : m_hWnd(NULL)
{
}


CWin32WndUI::~CWin32WndUI(void)
{
}

void CWin32WndUI::Init()
{
    __super::Init();
    SetVisible(true);
}

void CWin32WndUI::SetPos(RECT rc, bool bNeedInvalidate /*= true*/)
{
    __super::SetPos(rc, bNeedInvalidate);
    if (m_hWnd)
    {
        ::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
    }
}

void CWin32WndUI::SetInternVisible(bool bVisible /*= true*/)
{
    __super::SetInternVisible(bVisible);
    if (m_hWnd)
    {
        ::ShowWindow(m_hWnd, bVisible ? SW_SHOW : SW_HIDE);
    }
}

void CWin32WndUI::SetVisible(bool bVisible /* = true */)
{
    __super::SetVisible(bVisible);
    if (m_hWnd)
    {
        ShowWindow(m_hWnd, bVisible ? SW_SHOW : SW_HIDE);
    }
}

bool CWin32WndUI::Attach(HWND hWnd)
{
    if (!hWnd || !::IsWindow(hWnd))
    {
        return false;
    }
    m_hWnd = hWnd;
    return true;
}

HWND CWin32WndUI::Detach()
{
    auto hWnd = m_hWnd;
    m_hWnd = NULL;
    return hWnd;
}

HWND CWin32WndUI::GetWnd(void)
{
    return m_hWnd;
}

void CWin32WndUI::Delete()
{
    if (m_hWnd)
    {
        HWND hWnd = Detach();
        DestroyWindow(hWnd);
    }
    __super::Delete();
}

}
