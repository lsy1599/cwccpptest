
/**
 * 判斷是否全為數值組成的字串
 *
 * @param str
 * @return 
 */
bool isAllDigit(const string& str)
{
    int i ;
    for(i = 0; i != str.length(); i++)
    {
        if(!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}



const wchar_t kWhitespaceWide[] = {
  0x0009,  // <control-0009> to <control-000D>
  0x000A,
  0x000B,
  0x000C,
  0x000D,
  0x0020,  // Space
  0x0085,  // <control-0085>
  0x00A0,  // No-Break Space
  0x1680,  // Ogham Space Mark
  0x180E,  // Mongolian Vowel Separator
  0x2000,  // En Quad to Hair Space
  0x2001,
  0x2002,
  0x2003,
  0x2004,
  0x2005,
  0x2006,
  0x2007,
  0x2008,
  0x2009,
  0x200A,
  0x200C,  // Zero Width Non-Joiner
  0x2028,  // Line Separator
  0x2029,  // Paragraph Separator
  0x202F,  // Narrow No-Break Space
  0x205F,  // Medium Mathematical Space
  0x3000,  // Ideographic Space
  0
};

/**
 * 是否為空白字元
 */
inline bool IsWhitespace(wchar_t c) {
  return wcschr(kWhitespaceWide, c) != NULL;
}