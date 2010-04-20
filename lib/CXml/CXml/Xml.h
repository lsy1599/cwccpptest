#pragma once
#include "XmlNode.h"


//-------------------------------------------------------------------------
// Classes Name	    :CXml CXmlNode CXmlNodes
// Author			:Jerry.Wang QQ32775973 jerry.wang@clochase.com MSN:sky-sea-earth@21cn.com
// CreateTime       :2005-10-23
// Version          :v2.0 2007-07-16
//					:v2.1	Improve: Add LoadXml method
//					:		Improve: Add GetVersion method
//					:		Improve: Add const for GetXXX methods
//					:		Improve: define ASSERT as ATLASSERT for ATL 
//					:		Improve: define TRACE as ATLTRACE for ATL 
//-------------------------------------------------------------------------


namespace Generic
{

	class CXml
	{
	public:
		CXml(void);
		~CXml(void);

	protected:
		MSXML2::IXMLDOMDocument2Ptr m_pDoc; 
		CString						m_strFilePath;
		DWORD						m_dwVersion;

		BOOL CreateInstance(void);

	public:
		CString GetXmlFile(void) const;

		BOOL Base64Decode( CString strIn, LPBYTE & pBuf, LONG & lSize);
		CString Base64Encode( LPBYTE pBuf, ULONG ulSize);

		// Open xml file
		BOOL Open(LPCTSTR lpszXmlFilePath);

		// Load Xml string
		BOOL LoadXml(LPCTSTR lpszXmlContent);

		// save xml file
		BOOL Save(LPCTSTR lpszFilePath = NULL);

		// close xml file
		void Close(void);

		// get the latest error message
		CString GetLastError(MSXML2::IXMLDOMDocumentPtr pDoc = NULL);

		// get the root element of 
		CXmlNodePtr GetRoot(void);		

		// get single node by XPath
		CXmlNodePtr SelectSingleNode(LPCTSTR lpszPath);

		// get nodes by XPath
		CXmlNodesPtr SelectNodes(LPCTSTR lpszPath);

		// whether file exist
		static BOOL IsFileExist(CString strFilePath);

		// create node
		CXmlNodePtr CreateNode(CString strName);

		// get the current version of MSXML
		DWORD GetVersion(void) const;

		BOOL Transform( CString strXslFile, CString strDestFile);
	};
}