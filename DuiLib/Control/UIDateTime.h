#pragma once

namespace DuiLib {

class DUILIB_API CDateTimeUI :
    public CWin32WndUI
{
public:
    CDateTimeUI(void);
    ~CDateTimeUI(void);

    virtual void Init() override;

    virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue) override;

    void SetSystemTime(const SYSTEMTIME &st);
    SYSTEMTIME GetSystemTime(void);
    void SetDateTime(const CDuiString &datetime);
    CDuiString GetDateTime(void);
    void SetDate(const CDuiString &date);
    CDuiString GetDate(void);
    void SetTime(const CDuiString &time);
    CDuiString GetTime(void);

private:
    DWORD m_Style;
};

}
