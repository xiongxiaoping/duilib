#ifndef __UIGRID_H__
#define __UIGRID_H__
#pragma once

#include <map>
#include <vector>
namespace DuiLib {

    class DUILIB_API CGridUI
        : public CListUI
    {
    public:
        CGridUI(void);
        ~CGridUI(void);

    public:
        // 单个头部数据，列名 + 列宽
        typedef std::pair<LPCTSTR, int> element_header;
        // 列表头部数据
        typedef std::vector<element_header> list_header;
        // 单行对应的数据，第一个为userdata
        typedef std::pair<LPCTSTR, std::vector<LPCTSTR>> element_data;
        // 列表中所有的数据
        typedef std::vector<element_data> list_data;

    public:
        void ShowRowHeader(bool bShow = true);

        // 设置数据
        void SetData(const list_data &dataList);

        // 若列表中已有此数据，则更新，若无此数据，则插入
        void ReplaceIntoData(const element_data &data);

        virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

        virtual LPCTSTR GetClass() const;

        virtual LPVOID GetInterface(LPCTSTR pstrName);

    private:
        list_header m_HeaderList;
        list_data m_DataList;
    };
} // namespace DuiLib

#endif // __UIGRID_H__
