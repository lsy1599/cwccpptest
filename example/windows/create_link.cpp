/**
 * Description: �Q�� ShellLink �إ߱��|
 *
 * Author: Chui-Wen Chiu <sisimi.pchome@gmail.com>
 */

#include <windows.h>
#include <objbase.h>
#include <isguids.h>
#include <shobjidl.h>
#include <shlguid.h>


#define   IURL_SETURL_FL_USE_DEFAULT_PROTOCOL   0x0002
typedef struct urlinvokecommandinfoW
{
   DWORD   dwcbSize;
   DWORD   dwFlags; 
   HWND    hwndParent;
   LPCWSTR pcszVerb;  
}
URLINVOKECOMMANDINFOW;
typedef URLINVOKECOMMANDINFOW *PURLINVOKECOMMANDINFOW;
DECLARE_INTERFACE_(IUniformResourceLocatorW, IUnknown)
{
   STDMETHOD(QueryInterface)(THIS_
                             REFIID riid,
                             PVOID *ppvObject) PURE;
   STDMETHOD_(ULONG, AddRef)(THIS) PURE;
   STDMETHOD_(ULONG, Release)(THIS) PURE;
   STDMETHOD(SetURL)(THIS_
                     LPCWSTR pcszURL,
                     DWORD dwInFlags) PURE;
   STDMETHOD(GetURL)(THIS_
                     LPWSTR *ppszURL) PURE;
   STDMETHOD(InvokeCommand)(THIS_
                            PURLINVOKECOMMANDINFOW purlici) PURE;
};
#define IUniformResourceLocator         IUniformResourceLocatorW
typedef IUniformResourceLocator *PIUniformResourceLocator;

/**
 * �إ߱��|�s��
 *
 * @param	���|�W��
 * @param	�O�_�� URL 
 * @param	���|�����ؿ�
 * @return	TRUE=���\, FALSE=����
 */
BOOL CreateLink(LPCTSTR lptstrLinkName,  BOOL bURL, LPCTSTR lptstrLinkTarget) {
	BOOL bRetValue = FALSE;
	HRESULT hrTemp;
	::CoInitialize(NULL); 
	::IUnknown *punk = NULL;
	if (bURL) {
		::PIUniformResourceLocator purl = NULL;
		hrTemp = ::CoCreateInstance(::CLSID_InternetShortcut, NULL, CLSCTX_INPROC_SERVER, ::IID_IUniformResourceLocator, (void **) (&purl));
		if (SUCCEEDED(hrTemp)) {
			purl->SetURL(lptstrLinkTarget, IURL_SETURL_FL_USE_DEFAULT_PROTOCOL);
			punk = (IUnknown*) purl;
		}
	} else {
		IShellLink* psl = NULL;
		hrTemp = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **) (&psl));
		if (SUCCEEDED(hrTemp)) {
			psl->SetPath(lptstrLinkTarget);
			punk = (IUnknown*) psl;
		}
	} 

	if (punk != NULL) {
		::IPersistFile *ppf = NULL;
		hrTemp = punk->QueryInterface(IID_IPersistFile,	(void **) (&ppf));
		if (SUCCEEDED(hrTemp)) {
			hrTemp = ppf->Save(lptstrLinkName, TRUE);
			if (SUCCEEDED(hrTemp)) {
				bRetValue = TRUE;
			}
			ppf->Release();
		}
		punk->Release();
	}

	::CoUninitialize();
	return bRetValue;
}


int _tmain(int argc, _TCHAR* argv[])
{
	::CreateLink(TEXT("TEST"), TRUE, TEXT("http://chuiwenchiu.spaces.live.com"));
	
	return 0;
}

