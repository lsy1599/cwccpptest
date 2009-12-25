
#if !defined(AFX_ASSOCIATEARRAY_H__622BC67E_2F16_477F_BD90_6D00D1AAC5D2__INCLUDED_)
#define AFX_ASSOCIATEARRAY_H__622BC67E_2F16_477F_BD90_6D00D1AAC5D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAssociateArray  
{
public:
	unsigned long hash(char* filename);
	bool Get(char* src,char* tgt);
	bool Add(char* src,char* tgt);
	CAssociateArray();
	virtual ~CAssociateArray();

private:
	CMap<unsigned long,unsigned long,char*,char*> aamap;
	CList<char*,char*> garbagelist;
	short CheckSum(char* filename);
	unsigned short Crc16(char* filename);
	unsigned short gkey;
	unsigned short gkey2;
	unsigned long glongkey;
	HANDLE hlock_garbagelist_list;
	HANDLE hlock_aamap;
};

#endif // !defined(AFX_ASSOCIATEARRAY_H__622BC67E_2F16_477F_BD90_6D00D1AAC5D2__INCLUDED_)
