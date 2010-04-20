#include "StdAfx.h"
#include ".\xml.h"

namespace Generic
{



	CXml::CXml(void)
	: m_strFilePath(_T(""))
	, m_pDoc(NULL)
	, m_dwVersion(0)
	{
	}

	CXml::~CXml(void)
	{
		Close();
	}


	//-------------------------------------------------------------------------
	// Function Name    :IsFileExist	[static]
	// Parameter(s)     :CString strFilePath
	// Return           :BOOL
	// Memo             :Whether the file exist
	//-------------------------------------------------------------------------
	BOOL CXml::IsFileExist(CString strFilePath)
	{
		BOOL bExist = FALSE;
		HANDLE hFile = NULL;

		hFile = CreateFile( strFilePath
			, GENERIC_READ
			, FILE_SHARE_READ | FILE_SHARE_WRITE
			, NULL
			, OPEN_EXISTING
			, 0
			, 0
			);

		if( hFile != INVALID_HANDLE_VALUE )
		{
			CloseHandle( hFile );
			bExist = TRUE;
		}

		return (bExist);
	}


	CString CXml::GetXmlFile(void) const
	{
		return m_strFilePath;
	}


	//-------------------------------------------------------------------------
	// Function Name    :CreateNode
	// Parameter(s)     :CString strName
	// Return           :CXmlNodePtr
	// Memo             :create node
	//-------------------------------------------------------------------------
	CXmlNodePtr CXml::CreateNode(CString strName)
	{
		ASSERT( m_pDoc != NULL );

		CXmlNodePtr pChild( new CXmlNode() );
		
		try
		{	MSXML2::IXMLDOMNodePtr pChildNode = NULL;
			pChildNode = m_pDoc->createElement( _bstr_t(strName) );
			ASSERT( pChildNode != NULL );
			pChild->m_pNode = pChildNode;
			RELEASE_PTR(pChildNode);
		}
		catch ( _com_error e )
		{
			TRACE( _T("CXml::CreateNode failed:%s\n"), e.ErrorMessage());
			ASSERT( FALSE );
		}
		return pChild;
	}


	BOOL CXml::CreateInstance(void)
	{
		Close();

		HRESULT hr = S_FALSE;

		hr = (hr == S_OK) ? hr : m_pDoc.CreateInstance( __uuidof(MSXML2::DOMDocument60) );
		m_dwVersion = (m_dwVersion == 0 && hr == S_OK) ? 60 : m_dwVersion;
		hr = (hr == S_OK) ? hr : m_pDoc.CreateInstance( __uuidof(MSXML2::DOMDocument50) );
		m_dwVersion = (m_dwVersion == 0 && hr == S_OK) ? 50 : m_dwVersion;
		hr = (hr == S_OK) ? hr : m_pDoc.CreateInstance( __uuidof(MSXML2::DOMDocument40) );
		m_dwVersion = (m_dwVersion == 0 && hr == S_OK) ? 40 : m_dwVersion;
		hr = (hr == S_OK) ? hr : m_pDoc.CreateInstance( __uuidof(MSXML2::DOMDocument30) );
		m_dwVersion = (m_dwVersion == 0 && hr == S_OK) ? 30 : m_dwVersion;
		hr = (hr == S_OK) ? hr : m_pDoc.CreateInstance( __uuidof(MSXML2::DOMDocument26) );
		m_dwVersion = (m_dwVersion == 0 && hr == S_OK) ? 26 : m_dwVersion;
		hr = (hr == S_OK) ? hr : m_pDoc.CreateInstance( __uuidof(MSXML2::DOMDocument) );
		if( hr != S_OK ) 
		{
			// did u CoInitialize ?
			// did u install MSXML?
			ASSERT(FALSE);
			return FALSE;
		}

		return TRUE;
	}

	//-------------------------------------------------------------------------
	// Function Name    :Open
	// Parameter(s)     :LPCTSTR lpszXmlFilePath	
	// Return           :BOOL		false when failed
	// Memo             :open xml file, if not exist then create a new one
	//-------------------------------------------------------------------------
	BOOL CXml::Open( LPCTSTR lpszXmlFilePath )
	{
		HRESULT hr = S_FALSE;

		if( !CreateInstance() )
			return FALSE;

		m_strFilePath = lpszXmlFilePath;
		VARIANT_BOOL vbSuccessful = VARIANT_TRUE;

		try
		{
			m_pDoc->preserveWhiteSpace = VARIANT_FALSE;
			m_pDoc->validateOnParse = VARIANT_FALSE;

			if( IsFileExist(lpszXmlFilePath) )
			{
				vbSuccessful = m_pDoc->load( _variant_t(lpszXmlFilePath) );
			}
			else
			{
				MSXML2::IXMLDOMProcessingInstructionPtr pPI = NULL;
				pPI = m_pDoc->createProcessingInstruction( _bstr_t(_T("xml")), _bstr_t(_T("version=\"1.0\"")) );
				ASSERT( pPI != NULL );

				hr = m_pDoc->appendChild(pPI);
				ASSERT( SUCCEEDED(hr) );

				// create the root element
				MSXML2::IXMLDOMElementPtr pRoot = NULL;
				pRoot = m_pDoc->createElement( _bstr_t(_T("xmlRoot")) );
				m_pDoc->appendChild(pRoot);
				RELEASE_PTR(pRoot);

				vbSuccessful = SUCCEEDED(hr) ? VARIANT_TRUE : VARIANT_FALSE;
			}// if_else

			m_pDoc->setProperty( _bstr_t(_T("SelectionLanguage")), _variant_t(_T("XPath")) );
		}
		catch( _com_error e )
		{
			TRACE( _T("CXml::Open failed:%s\n"), e.ErrorMessage());
			vbSuccessful = FALSE;
			ASSERT( FALSE );
		}
		catch(...)
		{
			vbSuccessful = FALSE;
			ASSERT( FALSE );
		}

		return (vbSuccessful == VARIANT_TRUE);
	}

	//-------------------------------------------------------------------------
	// Function Name    :LoadXml
	// Parameter(s)     :LPCTSTR lpszXmlContent
	// Return           :BOOL
	// Memo             :Load the xml content
	//-------------------------------------------------------------------------
	BOOL CXml::LoadXml(LPCTSTR lpszXmlContent)
	{
		if( !CreateInstance() )
			return FALSE;

		VARIANT_BOOL vbSuccessful = VARIANT_TRUE;

		try
		{
			m_pDoc->preserveWhiteSpace = VARIANT_FALSE;
			m_pDoc->validateOnParse = VARIANT_FALSE;

			vbSuccessful = m_pDoc->loadXML( _bstr_t(lpszXmlContent) );

			m_pDoc->setProperty( _bstr_t(_T("SelectionLanguage")), _variant_t(_T("XPath")) );
		}
		catch( _com_error e )
		{
			TRACE( _T("CXml::Open failed:%s\n"), e.ErrorMessage());
			vbSuccessful = FALSE;
			ASSERT( FALSE );
		}
		catch(...)
		{
			vbSuccessful = FALSE;
			ASSERT( FALSE );
		}

		return (vbSuccessful == VARIANT_TRUE);
	}


	//-------------------------------------------------------------------------
	// Function Name    :Close
	// Parameter(s)     :void
	// Return           :void
	// Memo             :¹Ø±Õ
	//-------------------------------------------------------------------------
	void CXml::Close(void)
	{
		m_strFilePath = _T("");
		m_dwVersion = 0;
		RELEASE_PTR(m_pDoc);
	}



	//-------------------------------------------------------------------------
	// Function Name    :GetLastError
	// Parameter(s)     :void
	// Return           :CString
	// Memo             :get the latest error
	//-------------------------------------------------------------------------
	CString CXml::GetLastError(MSXML2::IXMLDOMDocumentPtr pDoc /* = NULL */)
	{
		if( pDoc == NULL )
		{
			ASSERT( m_pDoc != NULL );
			pDoc = m_pDoc;
		}	

		HRESULT hr = S_OK;
		MSXML2::IXMLDOMParseErrorPtr pIParseError = NULL;

		hr = pDoc->get_parseError(&pIParseError);
		ASSERT( SUCCEEDED(hr) );

		CString strRet;
		if( pIParseError != NULL )
		{
			BSTR bstr = NULL;
			hr = pIParseError->get_reason(&bstr);
			ASSERT( SUCCEEDED(hr) );

			strRet = (LPCTSTR)_bstr_t( bstr, true);

			if( bstr != NULL )
			{
				SysFreeString(bstr);
				bstr = NULL;
			}

			RELEASE_PTR(pIParseError);		
		}

		return strRet;
	}



	//-------------------------------------------------------------------------
	// Function Name    :GetRoot
	// Parameter(s)     :
	// Return           :
	// Memo             :get the root element
	//-------------------------------------------------------------------------
	CXmlNodePtr CXml::GetRoot(void)
	{	
		ASSERT( m_pDoc != NULL );

		CXmlNodePtr pNode( new CXmlNode() );

		try
		{
			MSXML2::IXMLDOMElementPtr pElement = NULL;
			HRESULT hr = m_pDoc->get_documentElement(&pElement);
			ASSERT( SUCCEEDED(hr) );
			ASSERT( pElement != NULL );

			pNode->m_pNode = pElement;
			RELEASE_PTR(pElement);
		}
		catch ( _com_error e )
		{
			TRACE( _T("CXml::GetRoot failed:%s\n"), e.ErrorMessage());
			ASSERT( FALSE );
		}
		
		return pNode;
	}

	//-------------------------------------------------------------------------
	// Function Name    :Save
	// Parameter(s)     :LPCTSTR lpszFilePath	[in] 
	// Return           :BOOL
	// Memo             :Save the xml file
	//-------------------------------------------------------------------------
	BOOL CXml::Save(LPCTSTR lpszFilePath /* = NULL */)
	{
		if( m_pDoc == NULL )
			return FALSE;

		ASSERT( m_pDoc != NULL );

		HRESULT hr = S_OK;
		if( lpszFilePath == NULL )
			hr = m_pDoc->save( _variant_t((LPCTSTR)m_strFilePath) );
		else
			hr = m_pDoc->save( _variant_t( lpszFilePath ) );

		return SUCCEEDED(hr);
	}



	//-------------------------------------------------------------------------
	// Function Name    :SelectSingleNode
	// Parameter(s)     :LPCTSTR strPath 
	// Return           :CXmlNodePtr
	// Memo             :
	//-------------------------------------------------------------------------
	CXmlNodePtr CXml::SelectSingleNode(LPCTSTR lpszPath)
	{
		ASSERT( m_pDoc != NULL );

		CXmlNodePtr pNode ( new CXmlNode() );

		if( !GetRoot()->IsNull() )
			(*pNode) = GetRoot()->SelectSingleNode(lpszPath);
		
		return pNode;
	}



	//-------------------------------------------------------------------------
	// Function Name    :SelectNodes
	// Parameter(s)     :LPCTSTR strPath	
	// Return           :CXmlNodesPtr
	// Memo             :
	//-------------------------------------------------------------------------
	CXmlNodesPtr CXml::SelectNodes(LPCTSTR lpszPath)
	{
		ASSERT( m_pDoc != NULL );

		CXmlNodesPtr pNodes( new CXmlNodes() );

		if( !GetRoot()->IsNull() )
			(*pNodes) = GetRoot()->SelectNodes(lpszPath);

		return pNodes;
	}



	//-------------------------------------------------------------------------
	// Function Name    :EncodeBase64
	// Parameter(s)     :LPBYTE *pBuf	The binary buffer
	//					:ULONG ulSize	size
	// Return           :CString		the result
	// Memo             :encoding the binary buffer into Base64 string
	//-------------------------------------------------------------------------
	CString CXml::Base64Encode(LPBYTE pBuf, ULONG ulSize)
	{
		ASSERT( m_pDoc != NULL );
		ASSERT( pBuf != NULL );
		
		CString strRet = _T("");
		try
		{
			MSXML2::IXMLDOMElementPtr pElement = NULL;
			pElement = m_pDoc->createElement( _bstr_t(_T("Base64")) );
			ASSERT( pElement != NULL );

			HRESULT hr = S_OK;
			hr = pElement->put_dataType( _bstr_t(_T("bin.base64")) );
			ASSERT( SUCCEEDED(hr) );

			SAFEARRAY * pAry = SafeArrayCreateVector( VT_UI1, 0L, ulSize);
			::memcpy( pAry->pvData, pBuf, ulSize);

			VARIANT var;
			VariantInit(&var);
			var.parray = pAry;
			var.vt = VT_ARRAY | VT_UI1;
			pElement->nodeTypedValue = var;

			BSTR bstr = NULL;
			hr = pElement->get_text( &bstr );
			ASSERT( SUCCEEDED(hr) );	
			strRet = (LPCTSTR)_bstr_t( bstr, true);

			if( bstr != NULL )
			{
				SysFreeString(bstr);
				bstr = NULL;
			}

			RELEASE_PTR(pElement);
		}
		catch ( _com_error e )
		{
			TRACE( _T("CXml::Base64Encode failed:%s\n"), e.ErrorMessage());
			ASSERT( FALSE );
		}

		return strRet;
	}



	//-------------------------------------------------------------------------
	// Function Name    :Base64Decode
	// Parameter(s)     :CString strIn		The base64 string
	//					:LPBYTE pBuf		The output buffer
	//					:ULONG &ulSize		the site of buffer
	// Return           :BOOL
	// Memo             :Decode the base64 string into buffer
	//					:NOTE: The pBuf will be alloced in the method and should be deleted after
	//-------------------------------------------------------------------------
	BOOL CXml::Base64Decode(CString strIn, LPBYTE & pBuf, LONG &lSize)
	{
		ASSERT( m_pDoc != NULL );
		
		try
		{
			MSXML2::IXMLDOMElementPtr pElement = NULL;
			pElement = m_pDoc->createElement( _bstr_t(_T("Base64")) );
			ASSERT( pElement != NULL );

			HRESULT hr = S_OK;
			hr = pElement->put_dataType( _bstr_t(_T("bin.base64")) );
			ASSERT( SUCCEEDED(hr) );

			hr = pElement->put_text( _bstr_t(strIn) );
			ASSERT( SUCCEEDED(hr) );

			hr = SafeArrayGetUBound( pElement->nodeTypedValue.parray, 1, &lSize);
			ASSERT( SUCCEEDED(hr) );
			lSize ++;

			pBuf = new BYTE[lSize];
			memset( pBuf, 0, lSize);

			memcpy( pBuf, LPVOID(pElement->nodeTypedValue.parray->pvData), lSize);	

			RELEASE_PTR(pElement);
		}
		catch ( _com_error e )
		{
			TRACE( _T("CXml::Base64Decode failed:%s\n"), e.ErrorMessage());
			ASSERT( FALSE );
			return FALSE;
		}
		
		return TRUE;
	}

	DWORD CXml::GetVersion(void) const
	{
		return m_dwVersion;
	}

	//-------------------------------------------------------------------------
	// Function Name    :Transform
	// Parameter(s)     :
	// Return           :
	// Memo             :This method has not been tested yet
	//-------------------------------------------------------------------------
	BOOL CXml::Transform( CString strXslFile, CString strDestFile)
	{
		ASSERT( m_pDoc != NULL );
		HRESULT hr = S_OK;

		short sResult = FALSE;
		MSXML2::IXMLDOMDocument2Ptr pStyleSheet;
		MSXML2::IXSLTemplatePtr pIXSLTemplate;
		MSXML2::IXSLProcessorPtr pIXSLProcessor;
		IStream * pOutStream	= NULL;
		LPVOID pOutput			= NULL;

		try
		{
			hr = pIXSLTemplate.CreateInstance( __uuidof(MSXML2::XSLTemplate) );
			ASSERT( SUCCEEDED(hr) );

			hr = pStyleSheet.CreateInstance( __uuidof(MSXML2::FreeThreadedDOMDocument) );
			ASSERT( SUCCEEDED(hr) );

			VARIANT_BOOL vbSuccessful = VARIANT_TRUE;
			vbSuccessful = pStyleSheet->load( _variant_t((LPCTSTR)strXslFile) );
			ASSERT( vbSuccessful == VARIANT_TRUE );

			hr = pIXSLTemplate->putref_stylesheet(pStyleSheet);
			if( !SUCCEEDED(hr) )
			{
				AfxMessageBox( _T("Error occurs when transform xsl!") );
				return FALSE;
			}

			pIXSLProcessor = pIXSLTemplate->createProcessor();
			ASSERT( pIXSLProcessor != NULL );

			CreateStreamOnHGlobal( NULL, TRUE, &pOutStream);
			pIXSLProcessor->put_output(_variant_t(pOutStream));

			hr = pIXSLProcessor->put_input( _variant_t((IUnknown*)m_pDoc) );
			ASSERT( SUCCEEDED(hr) );

			vbSuccessful = pIXSLProcessor->transform();
			ASSERT( vbSuccessful == VARIANT_TRUE );


		
			HGLOBAL hg = NULL;
			hr = pOutStream->Write( (void const*)_T("\0"), 1, 0);
			GetHGlobalFromStream( pOutStream, &hg);
			GlobalUnlock(hg);
			
			LARGE_INTEGER start = {0, 0};
			ULARGE_INTEGER cb = {0, 0};
			pOutStream->Seek( start, STREAM_SEEK_CUR, &cb);
	 
			pOutput = GlobalLock(hg);
			CFile file;
			file.Open( strDestFile, CFile::modeCreate | CFile::modeWrite, NULL);
			file.Write( pOutput, (UINT)cb.QuadPart);
			file.Flush();
			file.Close();
			GlobalUnlock(hg);

			RELEASE_PTR(pIXSLProcessor);
			RELEASE_PTR(pStyleSheet);
			RELEASE_PTR(pIXSLTemplate);
			

			return TRUE;
		}
		catch( _com_error e)
		{
			TRACE( _T("CXml::Transform failed:%s\n"), e.ErrorMessage());
			ASSERT( FALSE );
			return FALSE;
		}

	}

}