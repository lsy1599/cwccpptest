#include "objbase.h"
#include <httprequest.h>
#include <string>
#include <sstream>
#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <memory.h>
#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include <list>
#include <atlconv.h>

const int MAX_MIME_LINE_LEN	= 76;
std::string XBase64Encode(TCHAR* filename) {
	static const char* s_Base64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	bool m_bAddLineBreak = false;
//, const char* pbInput, int nInputSize/*, unsigned char* pbOutput, int nMaxSize*/
	std::list<unsigned char> tmp;

	HANDLE hFile = CreateFile(filename, 
                     GENERIC_READ,
                     FILE_SHARE_READ, 
                     NULL,
                     OPEN_EXISTING, 
                     FILE_ATTRIBUTE_NORMAL, 
                     NULL);
	DWORD nInputSize = GetFileSize(hFile, NULL);
	DWORD readed;
	char* pbInput = new char[nInputSize];
	ReadFile(hFile, pbInput, nInputSize, &readed, NULL);
	//__dbg_printf(_T("File Length: %d"), size);
	//__dbg_printf(_T("Read: %d"), readed);  
	CloseHandle(hFile);	

	//unsigned char* pbOutStart = pbOutput;
	//unsigned char* pbOutEnd = pbOutput + nMaxSize;
	int nFrom, nLineLen = 0;
	unsigned char chHigh4bits = 0;

	for (nFrom=0; nFrom<nInputSize; nFrom++)
	{
		//if (pbOutput >= pbOutEnd)
		//	break;

		unsigned char ch = pbInput[nFrom];
		switch (nFrom % 3)
		{
		case 0:
			tmp.push_back( s_Base64Table[ch >> 2] );
			//*pbOutput++ = s_Base64Table[ch >> 2];
			chHigh4bits = (ch << 4) & 0x30;
			break;

		case 1:
			tmp.push_back( s_Base64Table[chHigh4bits | (ch >> 4)] );
			//*pbOutput++ = s_Base64Table[chHigh4bits | (ch >> 4)];
			chHigh4bits = (ch << 2) & 0x3c;
			break;

		default:
			tmp.push_back(s_Base64Table[chHigh4bits | (ch >> 6)]);
			//*pbOutput++ = s_Base64Table[chHigh4bits | (ch >> 6)];
			//if (pbOutput < pbOutEnd)
			//{
				tmp.push_back(s_Base64Table[ch & 0x3f]);
				//*pbOutput++ = s_Base64Table[ch & 0x3f];
				nLineLen++;
			//}
		}

		nLineLen++;
		//if (m_bAddLineBreak && nLineLen >= MAX_MIME_LINE_LEN && pbOutput+2 <= pbOutEnd)
		//{
		//	*pbOutput++ = '\r';
		//	*pbOutput++ = '\n';
		//	nLineLen = 0;
		//}
	}

	if (nFrom % 3 != 0 )	// 76 = 19 * 4, so the padding wouldn't exceed 76
	{
		tmp.push_back(s_Base64Table[chHigh4bits]);
		//*pbOutput++ = s_Base64Table[chHigh4bits];
		int nPad = 4 - (nFrom % 3) - 1;
		//if (pbOutput+nPad <= pbOutEnd)
		//{
			//::memset(pbOutput, '=', nPad);
			//pbOutput += nPad;
			for(int i =0; i <nPad; ++i){
				tmp.push_back('=');
			}
		//}		
	}
	//if (m_bAddLineBreak && nLineLen != 0 && pbOutput+2 <= pbOutEnd)	// add CRLF
	//{
	//	*pbOutput++ = '\r';
	//	*pbOutput++ = '\n';
	//}
	//return (int)(pbOutput - pbOutStart);

	return std::string(tmp.begin(), tmp.end());
}

// IID for IWinHttpRequest.
const IID IID_IWinHttpRequest =
{
  0x06f29373,
  0x5c5a,
  0x4b54,
  {0xb0, 0x25, 0x6e, 0xf1, 0xbf, 0x8a, 0xbf, 0x0e}
};
const char* MULTIPART_BOUNDARY = "---------------------------0123456789012";

struct BSTRPtr{
	BSTR _ptr;
	BSTRPtr(TCHAR* p){
		_ptr = SysAllocString(p);
	}

	BSTRPtr(){
		_ptr = 0;
	}

	~BSTRPtr(){
		if (_ptr){
			SysFreeString(_ptr);
		}
	}

	BSTR* operator& () {
		return &_ptr;
	}

	BSTR get() const { return _ptr; }	
};

struct HttpRequest{
	/**
	 * 建構子
	 *
	 */
	HttpRequest(): bPost(L"POST"), bGet(L"GET"){
		CoInitialize( NULL );
		VariantInit(&varFalse);
		V_VT(&varFalse)   = VT_BOOL;
		V_BOOL(&varFalse) = VARIANT_FALSE;

		VariantInit(&varTrue);
		V_VT(&varTrue)   = VT_BOOL;
		V_BOOL(&varTrue) = VARIANT_TRUE;

		HRESULT hr = CLSIDFromProgID(L"WinHttp.WinHttpRequest.5.1", &clsid);
		if (SUCCEEDED(hr)) {
		}else{
			throw "Not Found WinHttp Component v5.1";
		}
	}

	/**
	 * 解構子
	 *
	 */
	~HttpRequest(){
		CoUninitialize();
	}

	/**
	 *
	 *
	 */
	std::wstring SyncHttpRequest(BSTR method, BSTR url, BSTR param = 0){
		HRESULT    hr;

		VARIANT         varEmpty;    
		VariantInit(&varEmpty);
		V_VT(&varEmpty) = VT_ERROR;		

		VARIANT         varParam;  
		varParam.vt = VT_BSTR;
		varParam.bstrVal = param;


		IWinHttpRequest*  pIWinHttpRequest = CreateRequest(method, url, varFalse);
		
		// Set request header.
		SetContentType(pIWinHttpRequest, BSTRPtr(L"application/x-www-form-urlencoded").get());	
		
		// Send Request.
		if (param == 0){
			hr = pIWinHttpRequest->Send(varEmpty);		
		}else{
			hr = pIWinHttpRequest->Send(varParam);		
		}
		

		BSTRPtr rep;
		if (SUCCEEDED(hr)) {	
			// Get Response text.		
			hr = pIWinHttpRequest->get_ResponseText( &rep );
		}
		
		// Print response to console.		
		std::wstring result(rep.get() );

		// Release memory.
		if (pIWinHttpRequest){
			pIWinHttpRequest->Release();
		}

		return result;
	}

	/**
	 *
	 *
	 */
	std::wstring AsyncHttpRequest(){
		return std::wstring();
	}

	/**
	 * 上傳檔案
	 *
	 * @param	url
	 * @param	file
	 * @return	伺服器處理結果
	 */ 
	std::wstring UploadFile(BSTR url, BSTR file){
		const wchar_t* CrLf		= L"\r\n";
		const wchar_t* Boundary = L"---------------------------7d7c2a20936";
		const wchar_t* Split	= L"-----------------------------7d7c2a20936";

		IWinHttpRequest*  pIWinHttpRequest = CreateRequest(bPost.get(), url, varFalse);

		std::wstringstream contentType;	
		contentType << L"multipart/form-data, boundary=" 
					<< Boundary;

		SetContentType(
			pIWinHttpRequest, 
			BSTRPtr( const_cast<TCHAR*>(contentType.str().c_str()) ).get()			
		);

		pIWinHttpRequest->SetRequestHeader(
			BSTRPtr(L"Accept-Language").get(),  
			BSTRPtr(L"zh-tw,en;q=0.5").get()
		);

		pIWinHttpRequest->SetRequestHeader(
			BSTRPtr(L"Accept-Encoding").get(),  
			BSTRPtr(L"gzip, deflate").get()
		);

		pIWinHttpRequest->SetRequestHeader(
			BSTRPtr(L"Accept").get(),  
			BSTRPtr(L"image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd.ms-excel, application/msword, application/vnd.ms-powerpoint, application/pdf, application/x-comet, */*").get()
		);

		pIWinHttpRequest->SetRequestHeader(
			BSTRPtr(L"CACHE-CONTROL").get(),  
			BSTRPtr(L"no-cache").get()
		);

		std::wstringstream content;	
		
		content << Split << CrLf
				<< L"Content-Disposition: form-data; name=\"token\"" << CrLf << CrLf
				<< L"xxxxxxxxx" << CrLf
				<< Split << CrLf
				<< L"Content-Disposition: form-data; name=\"file\"; filename=\"c:\\my.zip\"" << CrLf
				<< L"Content-Type: application/x-zip-compressed" << CrLf << CrLf
				<< CW2A( XBase64Encode(TEXT("c:\\my.zip")).c_str() )
				<< L"Content Data" << CrLf
				<< Split;		
	
		BSTRPtr c( const_cast<TCHAR*>(content.str().c_str()) );

		// Send Request.
		VARIANT         varParam;  
		varParam.vt = VT_BSTR;
		varParam.bstrVal = c.get();
		HRESULT hr = pIWinHttpRequest->Send(varParam);		
				

		BSTRPtr rep;
		if (SUCCEEDED(hr)) {	
			// Get Response text.		
			hr = pIWinHttpRequest->get_ResponseText( &rep );
		}
		
		// Print response to console.		
		std::wstring result(rep.get() );

		// Release memory.
		if (pIWinHttpRequest){
			pIWinHttpRequest->Release();
		}

		return std::wstring();
	}
private:
	/**
	 * 設定 Content-Type
	 *
	 * @param	pIWinHttpRequest
	 * @param	contentType
	 */
	void SetContentType(IWinHttpRequest* pIWinHttpRequest, BSTR contentType){
		HRESULT hr = pIWinHttpRequest->SetRequestHeader(
			BSTRPtr(L"Content-Type").get() ,  
			contentType
		);

		if (SUCCEEDED(hr)) {			
		}else{
			throw "Create WinHttp Fail";
		}
	}

	/**
	 * 建立 Request
	 *
	 * @param	method
	 * @param	url
	 * @param	async
	 */
	IWinHttpRequest* CreateRequest(BSTR method, BSTR url, VARIANT async){		
		IWinHttpRequest*  pIWinHttpRequest = NULL;
		HRESULT    hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_IWinHttpRequest, (void **)&pIWinHttpRequest);

		if (SUCCEEDED(hr)) {			
		}else{
			throw "Create WinHttp Fail";
		}


		// Open WinHttpRequest.	
		hr = pIWinHttpRequest->Open(
			method, 
			url, 
			async
		);

		if (SUCCEEDED(hr)) {			
		}else{
			throw "Open WinHttp Fail";
		}

		hr = pIWinHttpRequest->SetRequestHeader(
			BSTRPtr(L"User-Agent").get() ,  
			BSTRPtr(L"Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; .NET CLR 1.1.4322; .NET CLR 2.0.50727)").get()
		);
		return pIWinHttpRequest;
	}

private:
	VARIANT         varFalse;
	VARIANT			varTrue;
	CLSID           clsid;
	BSTRPtr			bPost;
	BSTRPtr			bGet;
};