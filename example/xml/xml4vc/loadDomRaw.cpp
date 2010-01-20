#include <iostream.h>
#include <stdio.h>
#include <windows.h>
#include <objbase.h>
#include <msxml2.h>

// Macro that calls a COM method returning HRESULT value:

typedef const wchar_t*	CPWCHAR;

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

// Helper function to create a DOM instance. 
IXMLDOMDocument * DomFromCOM()
{
    HRESULT hr;
    IXMLDOMDocument *pxmldoc = NULL;

    HRCALL( CoCreateInstance(__uuidof(DOMDocument30),
                     NULL,
                     CLSCTX_INPROC_SERVER,
                     __uuidof(IXMLDOMDocument),
                     (void**)&pxmldoc),
                     "Create a new DOMDocument");

    HRCALL( pxmldoc->put_async(VARIANT_FALSE),
            "should never fail");
    HRCALL( pxmldoc->put_validateOnParse(VARIANT_FALSE),
            "should never fail");
    HRCALL( pxmldoc->put_resolveExternals(VARIANT_FALSE),
            "should never fail");
    HRCALL( pxmldoc->put_preserveWhiteSpace(VARIANT_TRUE),
            "should never fail");

    return pxmldoc;
clean:
    if (pxmldoc)
    {
        pxmldoc->Release();
    }
    return NULL;
}

VARIANT VariantString(BSTR str)
{
    VARIANT var;
    VariantInit(&var);
    V_BSTR(&var) = SysAllocString(str);
    V_VT(&var) = VT_BSTR;
    return var;
}

// Helper function to display xml parse error:
void ReportParseError(IXMLDOMDocument *pDom, char *desc) {
    IXMLDOMParseError *pXMLErr=NULL;
    BSTR bstrReason = NULL;
    HRESULT hr;
    HRCALL(pDom->get_parseError(&pXMLErr),
            "dom->get_parseError: ");
    HRCALL(pXMLErr->get_reason(&bstrReason),
            "parseError->get_reason: ");

    dprintf("%s %S\n",desc, bstrReason);
clean:
    if (pXMLErr) pXMLErr->Release();
    if (bstrReason) SysFreeString(bstrReason);
}

// Helper function to append a whitespace text node to a 
// specified element:
void AddWhiteSpaceToNode(IXMLDOMDocument* pDom,
                    BSTR bstrWs,
                    IXMLDOMNode *pNode)
{
    HRESULT hr;
    IXMLDOMText *pws=NULL;
    IXMLDOMNode *pBuf=NULL;
    HRCALL(pDom->createTextNode(bstrWs,&pws), " ");
    HRCALL(pNode->appendChild(pws,&pBuf)," ");
clean:
    if (pws) pws->Release();
    pws=NULL;
    if (pBuf) pBuf->Release();
    pBuf=NULL;
}

// Helper function to append a child to a parent node:
void AppendChildToParent(IXMLDOMNode *pChild, IXMLDOMNode *pParent)
{
    HRESULT hr;
    IXMLDOMNode *pNode=NULL;
    HRCALL(pParent->appendChild(pChild, &pNode), "");
clean:
    if (pNode) pNode->Release();
    pNode=NULL;

}
                 
void AppendTextNode(IXMLDOMDocument* pXMLDom,
					const wchar_t* nodeName,
                    const wchar_t* text,
                    IXMLDOMNode *pParent)
{
	HRESULT hr;
	IXMLDOMElement *pe = NULL;
	BSTR bstr;
    bstr = SysAllocString( nodeName );
    HRCALL(pXMLDom->createElement(bstr, &pe), "");
    SysFreeString(bstr);
    bstr=NULL;

    bstr = SysAllocString(text);
    HRCALL(pe->put_text(bstr), "");
    SysFreeString(bstr);
    bstr=NULL;

    // Append <node1> to <root>.
    AppendChildToParent(pe, pParent);

clean:
    pe->Release();
    pe = NULL;
	if (bstr) SysFreeString(bstr);
	if (bstr) SysFreeString(bstr);
}

CPWCHAR XML_TAG_STATUS_INFO			= L"info";
CPWCHAR XML_TAG_STATUS_ID			= L"id";
CPWCHAR XML_TAG_STATUS_BEGINDATE	= L"beginDate";
CPWCHAR XML_TAG_STATUS_ENDDATE		= L"endDate";
CPWCHAR XML_TAG_STATUS_STATUS		= L"status";
CPWCHAR XML_TAG_STATUS_RESULT		= L"result";

void appendStatus(IXMLDOMDocument* pXMLDom,
		IXMLDOMNode *pParent,
		CPWCHAR id,
		CPWCHAR beginDate,
		CPWCHAR endDate,
		CPWCHAR status,
		CPWCHAR result
	)
{
	HRESULT hr;
	BSTR bstr;	
    IXMLDOMElement *pe = NULL;
	IXMLDOMDocumentFragment *pdf = NULL;
	
	bstr = SysAllocString(XML_TAG_STATUS_INFO);
	HRCALL(pXMLDom->createElement(bstr,&pe),"");
	SysFreeString(bstr);
	bstr=NULL;

	HRCALL(pXMLDom->createDocumentFragment(&pdf), "");
	AddWhiteSpaceToNode(pXMLDom, L"\n\t\t\t", pdf);
	AppendTextNode(pXMLDom, XML_TAG_STATUS_ID, id, pdf);
	AddWhiteSpaceToNode(pXMLDom, L"\n\t\t\t", pdf);

	AppendTextNode(pXMLDom, XML_TAG_STATUS_BEGINDATE, beginDate, pdf);
	AddWhiteSpaceToNode(pXMLDom, L"\n\t\t\t", pdf);

	AppendTextNode(pXMLDom, XML_TAG_STATUS_ENDDATE, endDate, pdf);
	AddWhiteSpaceToNode(pXMLDom, L"\n\t\t\t", pdf);

	AppendTextNode(pXMLDom, XML_TAG_STATUS_STATUS, status, pdf);
	AddWhiteSpaceToNode(pXMLDom, L"\n\t\t\t", pdf);

	AppendTextNode(pXMLDom, XML_TAG_STATUS_RESULT, result, pdf);
	AddWhiteSpaceToNode(pXMLDom, L"\n\t\t", pdf);	

	AddWhiteSpaceToNode(pXMLDom, L"\n\t\t", pe);
	AppendChildToParent(pdf, pe);

	AddWhiteSpaceToNode(pXMLDom, L"\n\t\t", pParent);
	AppendChildToParent(pe, pParent);	

clean:
    pe->Release();
    pe = NULL;

	pdf->Release();
	pdf = NULL;
	if ( bstr ) SysFreeString(bstr);		
}

int main()
{
    IXMLDOMDocument *pXMLDom=NULL;
    IXMLDOMProcessingInstruction *pi=NULL;
    IXMLDOMComment *pc=NULL;
    IXMLDOMElement *pe=NULL;
    IXMLDOMElement *pRoot=NULL;
    IXMLDOMAttribute *pa=NULL;
    IXMLDOMAttribute *pa1=NULL;
    IXMLDOMCDATASection *pcd=NULL;
    IXMLDOMElement *peSub=NULL;
    IXMLDOMDocumentFragment *pdf=NULL;
	IXMLDOMElement* pNode = NULL;
	

    BSTR bstr = NULL;
    BSTR bstr1 = NULL;
    BSTR bstr_wsn = SysAllocString(L"\n");
    BSTR bstr_wsnt= SysAllocString(L"\n\t");
    BSTR bstr_wsntt=SysAllocString(L"\n\t\t");

    VARIANT var;
    HRESULT hr;

    CoInitialize(NULL);
    VariantInit(&var);
  
    pXMLDom = DomFromCOM();
    if (!pXMLDom) goto clean;

    // Create a processing instruction element.
    bstr = SysAllocString(L"xml");
    bstr1 = SysAllocString(L"version='1.0'");
    HRCALL(pXMLDom->createProcessingInstruction(
                bstr,bstr1, &pi),
                "createProcessingInstruction:");
    AppendChildToParent(pi, pXMLDom);
    pi->Release();
    pi=NULL;
    SysFreeString(bstr);
    bstr=NULL;
    SysFreeString(bstr1);
    bstr1=NULL;

    // Create a comment element.
    bstr = SysAllocString(L"sample xml file created using XML DOM object.");
    HRCALL(pXMLDom->createComment(bstr, &pc), "");
    AppendChildToParent(pc, pXMLDom);
    SysFreeString(bstr);
    bstr=NULL;
    pc->Release();
    pc=NULL;

    // Create the root element.
    bstr = SysAllocString(L"root");
    HRCALL(pXMLDom->createElement(bstr, &pRoot), "");
    SysFreeString(bstr);
    bstr = NULL;

    // Create a "created" attribute for the <root> element, and
    // assign the "using dom" character data as the attribute value.
    bstr = SysAllocString(L"created");
    var = VariantString(L"using dom");
    HRCALL(pXMLDom->createAttribute(bstr,&pa), "");
    HRCALL(pa->put_value(var), "");
    HRCALL(pRoot->setAttributeNode(pa, &pa1), "");
    AppendChildToParent(pRoot, pXMLDom);
    SysFreeString(bstr);
    bstr=NULL;
    if (pa1) {
        pa1->Release();
        pa1=NULL;
    }
    pa->Release();
    pa=NULL;
    VariantClear(&var);

    // Next, we will create and add three nodes to the <root> element.

    // Add NEWLINE+TAB for identation before <node1>.
    AddWhiteSpaceToNode(pXMLDom, bstr_wsnt, pRoot);

    // Create a <node1> to hold text content.
/*
    bstr = SysAllocString(L"node1");
    HRCALL(pXMLDom->createElement(bstr,&pe),"");
    SysFreeString(bstr);
    bstr=NULL;

    bstr=SysAllocString(L"some character data");
    HRCALL(pe->put_text(bstr), "");
    SysFreeString(bstr);
    bstr=NULL;


    // Append <node1> to <root>.
    AppendChildToParent(pe, pRoot);
    pe->Release();
    pe=NULL;
*/

	pRoot->Release();
	pRoot = NULL;
	pXMLDom->get_documentElement(&pRoot);
	if (pRoot == NULL){
		cout << "error";
		exit(-1);
	}
	cout << "get";
    HRCALL(pXMLDom->get_xml(&bstr), "dom->get_xml");
    dprintf("Dynamically created DOM:\n%S\n", bstr);
	//cout << "here" << endl;
	//if (S_OK != pXMLDom->get_documentElement(&pNode)){
//		cout << "error" << endl;
	//}else{
//	appendStatus(pXMLDom, pNode, L"10001", L"2006/1/7 9:3:12", L"2006/1/7 10:54:28", L"yes", L"5");


//	}
//	pNode->Release();
//	pNode = NULL;

	AppendTextNode(pXMLDom, L"node1", L"some character data", pRoot);
    AddWhiteSpaceToNode(pXMLDom, bstr_wsnt, pRoot);
// -----
//appendStatus(pXMLDom, pRoot, L"10001", L"2006/1/7 9:3:12", L"2006/1/7 10:54:28", L"yes", L"5");
//appendStatus(pXMLDom, pRoot, L"10001", L"2006/1/7 9:3:12", L"2006/1/7 10:54:28", L"no", L"6");
// Create a document fragment to hold three sub-elements.

// ----
    // Add NEWLINE+TAB for identation before <node2>.
    AddWhiteSpaceToNode(pXMLDom, bstr_wsnt, pRoot);

    // Create a <node2> to hold a CDATA section.
    bstr = SysAllocString(L"node2");
    HRCALL(pXMLDom->createElement(bstr,&pe),"create <node2> ");
    SysFreeString(bstr);
    bstr=NULL;

    bstr = SysAllocString(L"<some mark-up text>");
    HRCALL(pXMLDom->createCDATASection(bstr,&pcd),"");
    SysFreeString(bstr);
    bstr=NULL;
    if (!pcd) goto clean;

    AppendChildToParent(pcd, pe);
    pcd->Release();
    pcd=NULL;

    // Append <node2> to <root>.
    AppendChildToParent(pe, pRoot);
    pe->Release();
    pe=NULL;

    // Add NEWLINE+TAB for identation before <node3>.
    AddWhiteSpaceToNode(pXMLDom, bstr_wsnt, pRoot);

    // Create <node3> to hold a doc fragment with three sub-elements.
    bstr = SysAllocString(L"node3");
    HRCALL(pXMLDom->createElement(bstr,&pe),"");
    SysFreeString(bstr);
    bstr=NULL;

    // Create a document fragment to hold three sub-elements.
    HRCALL(pXMLDom->createDocumentFragment(&pdf), "");

    // Add NEWLINE+TAB+TAB for identation before <subnode1>.
    AddWhiteSpaceToNode(pXMLDom, bstr_wsntt, pdf);

    // Create <subnode1>.
    bstr = SysAllocString(L"subnode1");
    HRCALL(pXMLDom->createElement(bstr,&peSub), "");
    SysFreeString(bstr);
    bstr=NULL;

    // Add <subnode1> to pdf.
    AppendChildToParent(peSub, pdf);
    peSub->Release();
    peSub=NULL;

    // Add NEWLINE+TAB+TAB for identation before <subnode2>.
    AddWhiteSpaceToNode(pXMLDom, bstr_wsntt, pdf);

    // Create and append <subnode2>.
    bstr = SysAllocString(L"subnode2");
    HRCALL(pXMLDom->createElement(bstr,&peSub), "");
    SysFreeString(bstr);
    bstr=NULL;

    // Add <subnode1> to pdf.
    AppendChildToParent(peSub, pdf);
    peSub->Release();
    peSub=NULL;

    // Add NEWLINE+TAB+TAB for identation before <subnode3>.
    AddWhiteSpaceToNode(pXMLDom, bstr_wsntt, pdf);

    // Create and append <subnode3>.
    bstr = SysAllocString(L"subnode3");
    HRCALL(pXMLDom->createElement(bstr,&peSub), "");
    SysFreeString(bstr);
    bstr=NULL;
    if (!peSub) goto clean;

    // Add <subnode1> to pdf.
    AppendChildToParent(peSub, pdf);
    peSub->Release();
    peSub=NULL;

    // Add NEWLINE+TAB after </subnode> in pdf.
    AddWhiteSpaceToNode(pXMLDom, bstr_wsnt, pdf);
    // Append pdf to <node3> (pe).
    AppendChildToParent(pdf, pe);

    // Append <node3> to <root>.
    AppendChildToParent(pe, pRoot);

    // Add NEWLINE for identation before </root>.
    AddWhiteSpaceToNode(pXMLDom, bstr_wsn, pRoot);

    HRCALL(pXMLDom->get_xml(&bstr), "dom->get_xml");
    dprintf("Dynamically created DOM:\n%S\n", bstr);

    VariantClear(&var);
//    var = VariantString(L"dynamDom.xml");
//    HRCALL(pXMLDom->save(var), "");
//    dprintf("DOM saved to dynamDom.xml\n");


clean:
    if (bstr) SysFreeString(bstr);
    if (bstr1) SysFreeString(bstr1);
    if (&var) VariantClear(&var);

    if (pXMLDom) pXMLDom->Release();
    if (pRoot) pRoot->Release();
    if (pe) pe->Release();
    if (peSub) peSub->Release();
    if (pi) pi->Release();
    if (pa) pa->Release();
    if (pa1) pa1->Release();
    if (pc) pc->Release();
    if (pcd) pcd->Release();
    if (pdf) pdf->Release();

    CoUninitialize();
    return 0;
}
