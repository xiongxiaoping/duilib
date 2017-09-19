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
        // ����ͷ�����ݣ����� + �п�
        typedef std::pair<LPCTSTR, int> element_header;
        // �б�ͷ������
        typedef std::vector<element_header> list_header;
        // ���ж�Ӧ�����ݣ���һ��Ϊuserdata
        typedef std::pair<LPCTSTR, std::vector<LPCTSTR>> element_data;
        // �б������е�����
        typedef std::vector<element_data> list_data;

    public:
        void ShowRowHeader(bool bShow = true);

        // ��������
        void SetData(const list_data &dataList);

        // ���б������д����ݣ�����£����޴����ݣ������
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
