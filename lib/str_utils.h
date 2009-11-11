
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