/*
 * XML 讀寫類別
 *
 * 方法：
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
 * XML Wraper 類別
 *
 * 方法：
 *    loadXML              載入 XML
 *    saveXML              儲存 XML
 *    getContent           取得 XML 完整內容
 *    getFirstNodeText     取得第一個文字節點的值
 *    setFirstNodeText     設定第一個文字節點的值
 *    getCountNode         取得指定節點的數量
 *    appendChildToParent  附加一個節點到父節點之下
 *    addWhiteSpaceToNode  附加一個空白節點
 *    appendTextNode       附加一個文字節點
 *    createElement        建立一個元素
 *
 *    getDoc               取得 IXMLDOMDocument 介面
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
