/*
 * XML Ū�g���O
 *
 * ��k�G
 * loadXML
 * saveXML
 *
 * getContent()
 * getFirstNodeText()
 */

#include <windows.h>
#include <msxml3.h>
#include <string>

#ifndef CXMLH
#define CXMLH
using std::wstring;

#define HRCALL(a, errmsg) \
do { \
    hr = (a); \
    if (FAILED(hr)) { \
        goto clean; \
    } \
} while (0)

typedef wchar_t   WCHAR;
typedef WCHAR*    PWCHAR;
typedef const wchar_t* CPWCHAR;

/*
 * XML Wraper ���O
 *
 * ��k�G
 *    loadXML              ���J XML
 *    saveXML              �x�s XML
 *    getContent           ���o XML ���㤺�e
 *    getFirstNodeText     ���o�Ĥ@�Ӥ�r�`�I����
 *    setFirstNodeText     �]�w�Ĥ@�Ӥ�r�`�I����
 *    getCountNode         ���o���w�`�I���ƶq
 *    appendChildToParent  ���[�@�Ӹ`�I����`�I���U
 *    addWhiteSpaceToNode  ���[�@�Ӫťո`�I
 *    appendTextNode       ���[�@�Ӥ�r�`�I
 *    createElement        �إߤ@�Ӥ���
 *
 *    getDoc               ���o IXMLDOMDocument ����
 */
class CXML{
public:
   CXML();
   ~CXML();

   bool loadXML(PWCHAR xml_filename);

   bool saveXML(PWCHAR xml_filename);
   bool saveXML();

   wstring getContent();
   wstring getFirstNodeText(PWCHAR nodeName);
   bool setFirstNodeText(PWCHAR nodeName, CPWCHAR text);
   long getCountNode(PWCHAR nodeName);

   ::IXMLDOMDocument* getDoc(){
      return pXMLDom;
   }

   void appendChildToParent(::IXMLDOMNode *pChild, ::IXMLDOMNode *pParent);
   void addWhiteSpaceToNode(CPWCHAR bstrWs, ::IXMLDOMNode *pNode);
   void appendTextNode(CPWCHAR nodeName, CPWCHAR text, ::IXMLDOMNode *pParent);


   ::IXMLDOMElement* createElement(PWCHAR nodeName, CPWCHAR text);
protected:
   ::IXMLDOMDocument *pXMLDom;
   ::IXMLDOMParseError *pXMLErr;

   BSTR bstr;
   VARIANT var;
   PWCHAR _filename;

//   VARIANT VariantString(BSTR str);
};
#endif
