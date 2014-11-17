#ifndef ResourceManager_h__
#define ResourceManager_h__
/*/////////////////////////////////////////////////////////////
//
// �ļ�����	:	ResourceManager.h
// ������		: 	daviyang35@gmail.com
// ����ʱ��	:	2014-11-11 17:47:53
// ˵��			:	ȫ����Դ�������������֣����ԣ�����
/////////////////////////////////////////////////////////////*/
#pragma once
class CUIEngine;
class TemplateObject;
class TiXmlElement;
class CWindowUI;

class DIRECTUI_API CResourceManager
{
public:
	static CResourceManager *GetInstance();
	static void ReleaseInstance();

public:
	virtual void SetLanguage(LPCTSTR lpszLanguage);
	virtual void InitResouceDir(LPCTSTR lpszPath,bool bIsDefault = false);

	virtual void FreeResource(LPCTSTR lpszComponentName);

	LPCTSTR GetLanguage();
	LPCTSTR GetResouceDir(LPCTSTR lpszModuleName = NULL);

	TemplateObject* GetWindowTemplate(LPCTSTR lpszWindowTemplateName);
	TemplateObject* GetViewTemplate(LPCTSTR lpszViewTemplateName);

	CControlUI *CreateControlFromTemplate(TemplateObject *pTemplate,CWindowUI* pManager,CControlUI* pParent=NULL);

	void AddFont(FontObject *pFont);
	ImageObject* GetImage(LPCTSTR lpszImagePath,bool bCached = true );
	FontObject*	GetFont(LPCTSTR lpszFontName);

private:
	bool GetAbsolutePath(CDuiString& strFullPath,LPCTSTR lpszComponent,LPCTSTR lpszRelativePath);

	void parseLayouts(TiXmlElement * pLayouts, LPCTSTR lpszComponentName);
	void parseFonts(TiXmlElement * pLayouts, LPCTSTR lpszComponentName);
	void parseLanguages(TiXmlElement * pLayouts, LPCTSTR lpszComponentName);

	TemplateObject* parseXmlFile(LPCTSTR lpszFilePath);
	TemplateObject* XmlToTemplate(TiXmlElement *pElement,TemplateObject* pParent);

private:
	// ��Resource.xml�Ļ���
	StringMap m_mapComponent;		// �����Դ·��
	TemplateMap m_mapLayouts;		// ���֣����������ڣ���ͼ
	TemplateMap m_mapLanguages;	// �����
	// TODO �ݲ�֧�� TemplateMap m_mapTemplates;	// �ɸ�����ʽ

private:
	LANGID m_DefaultLangID;
	CDuiString m_strDefaultResourcePath;
	CDuiString m_strDefaultLanguage;
	CDuiString m_strDefaultFont;
	// �Ѽ�����Դ�Ļ���
	//CStdStringPtrMap m_mapImagePool;
	//CStdStringPtrMap m_mapFontPool;
	ImagePoolMap m_mapImagePool;	// �Ѽ��ص�ͼƬ��Դ����
	FontPoolVector m_vecFontPool;		// �Ѽ��ص�������ʽ����
	StringMap		m_mapI18NPool;		// ������ַ�������

private:
	CResourceManager(void);
	~CResourceManager(void);
	static CResourceManager *m_pInstace;
	static CUIEngine* m_pEngine;
};

#endif // ResourceManager_h__