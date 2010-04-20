#include <windows.h>
#include "CXML.h"

CXML::CXML(){
   CoInitialize(NULL);

   bstr = NULL;
   pXMLErr = NULL;
   pXMLDom  = NULL;
   VariantInit(&var);

   CoCreateInstance(CLSID_msDOMDocument30, NULL, CLSCTX_INPROC_SERVER, ::IID_IXMLDOMDocument, (void**)&pXMLDom);
   pXMLDom->put_async(VARIANT_FALSE);
   pXMLDom->put_validateOnParse(VARIANT_FALSE);
   pXMLDom->put_resolveExternals(VARIANT_FALSE);
}

CXML::~CXML(){
   if (bstr) SysFreeString(bstr);
   if (&var) VariantClear(&var);
   if (pXMLErr) pXMLErr->Release();
   if (pXMLDom) pXMLDom->Release();

   CoUninitialize();
}

bool CXML::loadXML(PWCHAR xml_filename){
   _filename = xml_filename;
   VARIANT_BOOL status;
   V_BSTR(&var) = SysAllocString(xml_filename);
   V_VT(&var) = VT_BSTR;
   pXMLDom->load(var, &status);

   if (status!=VARIANT_TRUE) {
      return false;
//     pXMLDom->get_parseError(&pXMLErr);
//     pXMLErr->get_reason(&bstr);
//     throw bstr;
  }
  return true;
}
bool CXML::saveXML(){
   V_BSTR(&var) = SysAllocString(_filename);
   V_VT(&var) = VT_BSTR;

   if (FAILED( pXMLDom->save(var) )){
      return false;
   }

   return true;
}

bool CXML::saveXML(PWCHAR xml_filename){
   _filename = xml_filename;
   return saveXML();
}
//BSTR
wstring CXML::getContent(){
   pXMLDom->get_xml(&bstr);
   return wstring(bstr);
}

wstring CXML::getFirstNodeText(PWCHAR nodeName){
     HRESULT ret;
     ::IXMLDOMNodeList* pNodeList = NULL;
     if FAILED( pXMLDom->getElementsByTagName(nodeName, &pNodeList)){
         throw "getElementsByTagName";
     }
     ::IXMLDOMNode* node = NULL;
     long len = 0;
     if (FAILED(pNodeList->get_length(&len))){
         throw "get_length";
     }
     if (len <= 0){
       return L"";
     }


     if ( FAILED( pNodeList->get_item(0, &node) ) ){
         throw "get_item";
     }

     if ( FAILED( node->get_text(&bstr) )){
         throw "get_text";
     }

     node->Release();
     pNodeList->Release();

     return bstr;
}

bool CXML::setFirstNodeText(PWCHAR nodeName, CPWCHAR text){
//bool CXML::setFirstNodeText(CPWCHAR nodeName, BSTR text){
     ::IXMLDOMNodeList* pNodeList = NULL;
     if ( FAILED( pXMLDom->getElementsByTagName(nodeName, &pNodeList) )){
         throw "getElementsByTagName";
     }
     ::IXMLDOMNode* node = NULL;

     long len = 0;
     if (FAILED(pNodeList->get_length(&len)) ){
         throw "get_length";
     }
     if (len <= 0){
       return false;
     }
     if (FAILED(pNodeList->get_item(0, &node))){
         throw "get_item";
     }

     if ( FAILED(node->put_text( const_cast<PWCHAR>(text) ))){
         throw "put_text";
     }

     node->Release();
     pNodeList->Release();

     return true;
}

// ミ穝じ
::IXMLDOMElement* CXML::createElement(PWCHAR nodeName, CPWCHAR text){
   ::IXMLDOMElement *pNode=NULL;
   if ( FAILED( pXMLDom->createElement( const_cast<PWCHAR>( nodeName ), &pNode) )){
      throw "createElement";
   }

   if ( FAILED(pNode->put_text( const_cast<PWCHAR>(text) ) )){
      throw "put_text";
   }
   return pNode;
}

void CXML::appendChildToParent(::IXMLDOMNode *pChild, ::IXMLDOMNode *pParent)
{
    HRESULT hr;
    ::IXMLDOMNode *pNode=NULL;
    HRCALL(pParent->appendChild(pChild, &pNode), "");
clean:
    if (pNode) pNode->Release();
    pNode=NULL;

}

// Helper function to append a whitespace text node to a
// specified element:
void CXML::addWhiteSpaceToNode(
                    CPWCHAR bstrWs,
                    ::IXMLDOMNode *pNode)
{
    HRESULT hr;
    ::IXMLDOMText *pws=NULL;
    ::IXMLDOMNode *pBuf=NULL;
    HRCALL(pXMLDom->createTextNode( const_cast<PWCHAR>(bstrWs), &pws), " ");
    HRCALL(pNode->appendChild(pws,&pBuf)," ");

clean:
    if (pws) pws->Release();
    pws=NULL;
    if (pBuf) pBuf->Release();
    pBuf=NULL;
}

void CXML::appendTextNode(
					CPWCHAR nodeName,
                    CPWCHAR text,
                    ::IXMLDOMNode *pParent)
{
	HRESULT hr;
	::IXMLDOMElement *pe = NULL;
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
    appendChildToParent(pe, pParent);

clean:
    pe->Release();
    pe = NULL;
	if (bstr) SysFreeString(bstr);
	if (bstr) SysFreeString(bstr);
}

/*
 * 眔﹚ node 计秖
 *
 * 把计
 *   nodeName: PWCHAR, 竊翴嘿
 *
 * 肚
 *   long   竊翴计
 */
long CXML::getCountNode(PWCHAR nodeName){
     HRESULT ret;
     ::IXMLDOMNodeList* pNodeList = NULL;
     if FAILED( pXMLDom->getElementsByTagName(nodeName, &pNodeList)){
         throw "getElementsByTagName";
     }

     long len = 0;
     if (FAILED(pNodeList->get_length(&len))){
         throw "get_length";
     }

   return len;
}
