#define ARRCOUNT(a)		( sizeof(a) / sizeof( (a)[0] ) )
#define AnsiToUniCode(pstr,pwstr,cch)    \
            MultiByteToWideChar(CP_ACP,0,(pstr),(cch),(pwstr),(cch))
#define UniCodeToAnsi(pstr,pwstr,cch)    \
            WideCharToMultiByte(CP_ACP,0,(pwstr),(cch),(pstr),(cch),NULL,NULL)