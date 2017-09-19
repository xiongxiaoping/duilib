#pragma once

namespace DuiLib {

class DUILIB_API CWin32WndUI : public CLabelUI
{
public:
    CWin32WndUI(void);
    virtual ~CWin32WndUI(void) = 0;

public:
    virtual void Init() override;
    virtual void Delete() override;
    virtual void SetPos(RECT rc, bool bNeedInvalidate = true) override;
    virtual void SetInternVisible(bool bVisible = true) override;
    virtual void SetVisible(bool bVisible /* = true */) override;

    bool Attach(HWND hWnd);
    HWND Detach();
    HWND GetWnd(void);


protected:
    HWND m_hWnd;
};

}
