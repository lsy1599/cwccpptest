
/**
 * �P�_�O�_�����ƭȲզ����r��
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