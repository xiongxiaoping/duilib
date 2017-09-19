#include "StdAfx.h"
#include "UIGrid.h"

#include <algorithm>

#include <string>

#ifdef _UNICODE
#define tstring std::string
#define to_tstring std::to_string
#else
#define tstring std::wstring
#define to_tstring std::to_wstring
#endif

namespace DuiLib {

CGridUI::CGridUI(void)
{
}


CGridUI::~CGridUI(void)
{
}

void CGridUI::ShowRowHeader(bool bShow /*= true*/)
{
    CListHeaderItemUI *pRowHeader = static_cast<CListHeaderItemUI*>(GetHeader()->GetItemAt(0));
    pRowHeader->SetVisible(bShow);
}

void CGridUI::SetData(const list_data &dataList)
{
    // 移除已删除的数据
    for (int i=0; i<GetCount(); ++i)
    {
        auto pElement = GetItemAt(i);
        if (std::find_if(dataList.begin(), dataList.end(),[pElement](const element_data &data){
            return pElement->GetUserData() == data.first;
        }) == dataList.end())
        {
            Remove(pElement);
        }
    }

    // 遍历数据，若列表已有，仅更新，若列表尚无，则添加
    for (const auto &data : dataList)
    {
        ReplaceIntoData(data);
    }
}

void CGridUI::ReplaceIntoData(const element_data &data)
{
    CListTextElementUI *pElement = nullptr;
    int row = 0;
    for (int i=0; i<GetCount(); ++i)
    {
        if (GetItemAt(i)->GetUserData() == data.first)
        {
            pElement = static_cast<CListTextElementUI*>(GetItemAt(i));
            row = i;
            break;
        }
    }
    if (nullptr == pElement)
    {
        pElement = new CListTextElementUI;
        row = GetCount();
        pElement->SetUserData(data.first);
        Add(pElement);
    }
    
    int col = 0;
    CDuiString str;
    str.Format(_T("%d"), col + 1);
    pElement->SetText(col++, str);
    for (const auto &text : data.second)
    {
        pElement->SetText(col++, text);
    }

    while (++row < GetCount())
    {
        CListTextElementUI *pElement = static_cast<CListTextElementUI*>(GetItemAt(row));
        str.Format(_T("%d"), col + 1);
        pElement->SetText(0, str);
    }
}

void CGridUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
    throw std::logic_error("The method or operation is not implemented.");
}

LPCTSTR CGridUI::GetClass() const
{
    return DUI_CTR_GRID;
}

LPVOID CGridUI::GetInterface(LPCTSTR pstrName)
{
    if( _tcscmp(pstrName, DUI_CTR_GRID) == 0 ) return static_cast<CGridUI*>(this);
    return CListUI::GetInterface(pstrName);
}

}
