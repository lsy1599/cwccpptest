//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include <stdio.h>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma resource "*.dfm"

#define HRCALL(a, errmsg) \
do { \
    hr = (a); \
    if (FAILED(hr)) { \
        dprintf( "%s:%d  HRCALL Failed: %s\n  0x%.8x = %s\n", \
                __FILE__, __LINE__, errmsg, hr, #a ); \
        goto clean; \
    } \
} while (0)

// Helper function that put output in stdout and debug window
// in Visual Studio:
void dprintf( char * format, ...)
{
    static char buf[1024];
    va_list args;
    va_start( args, format );
    vsprintf( buf, format, args );
    va_end( args);
    OutputDebugStringA( buf);
    printf("%s", buf);
}


// Helper function to create a DOM instance:
::IXMLDOMDocument * DomFromCOM()
{
   HRESULT hr;
   ::IXMLDOMDocument *pxmldoc = NULL;

   HRCALL( CoCreateInstance(CLSID_msDOMDocument30,
                  NULL,
                  CLSCTX_INPROC_SERVER,
                  ::IID_IXMLDOMDocument,
                  (void**)&pxmldoc),
                  "Create a new DOMDocument");

    HRCALL( pxmldoc->put_async(VARIANT_FALSE),
            "should never fail");
    HRCALL( pxmldoc->put_validateOnParse(VARIANT_FALSE),
            "should never fail");
    HRCALL( pxmldoc->put_resolveExternals(VARIANT_FALSE),
            "should never fail");

    return pxmldoc;
clean:
    if (pxmldoc)
    {
        pxmldoc->Release();
    }
    return NULL;
}

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
   ::IXMLDOMDocument *pXMLDom=NULL;
   ::IXMLDOMParseError *pXMLErr=NULL;
    BSTR bstr = NULL;
    VARIANT_BOOL status;
    VARIANT var;
    HRESULT hr;

   CoInitialize(NULL);
   pXMLDom = DomFromCOM();
    if (!pXMLDom) {
      ShowMessage("error");
       goto clean;
    }

    VariantInit(&var);
    V_BSTR(&var) = SysAllocString(L"c:\\search.xml");
    V_VT(&var) = VT_BSTR;
    HRCALL(pXMLDom->load(var, &status), "");

    if (status!=VARIANT_TRUE) {
        HRCALL(pXMLDom->get_parseError(&pXMLErr),"");
        HRCALL(pXMLErr->get_reason(&bstr),"");
        dprintf("Failed to load DOM from stocks.xml. %S\n",
                    bstr);
        goto clean;
    }
    HRCALL(pXMLDom->get_xml(&bstr), "");
    ShowMessage("XML DOM loaded from stocks.xml:\n%S\n");
//    dprintf("XML DOM loaded from stocks.xml:\n%S\n",bstr);

clean:
    if (bstr) SysFreeString(bstr);
    if (&var) VariantClear(&var);
    if (pXMLErr) pXMLErr->Release();
    if (pXMLDom) pXMLDom->Release();

CoUninitialize();

}
//---------------------------------------------------------------------------

