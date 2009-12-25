// AssociateArray.cpp: implementation of the CAssociateArray class.
// (C) THE INAZUMA PIKACHU , 2000
// THE HIGH PERFORMANCE HASHED ASSOCIATIVE ARRAY OR MAP
// MULTI THREADING OPERATION : OK
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AssociateArray.h"

CAssociateArray::CAssociateArray()
{
	hlock_garbagelist_list = CreateEvent(NULL,false,false,"lockgarbage");
	hlock_aamap = CreateEvent(NULL,false,false,"lockaamap");
	SetEvent(hlock_garbagelist_list);
	SetEvent(hlock_aamap);
}

CAssociateArray::~CAssociateArray()
{
	WaitForSingleObject(hlock_garbagelist_list,INFINITE);
	ResetEvent(hlock_garbagelist_list);
	POSITION pos1 = NULL;
	char* delpoint;
	for(pos1 = garbagelist.GetHeadPosition(); pos1 != NULL; )    
	{
		try
		{
			delpoint = garbagelist.GetNext( pos1 );
			if(delpoint != NULL)
				delete delpoint;
		}
		catch(...)
		{
		}
	}
	SetEvent(hlock_garbagelist_list);
	SetEvent(hlock_aamap);
	delete hlock_garbagelist_list;
	delete hlock_aamap;
}

unsigned short CAssociateArray::Crc16(char *filename)
{
	int nChars = strlen(filename);
	const unsigned int POLY = 0x8468;
	int i,j;
	int data;
	unsigned short crc = 0xffff;
	if (nChars == 0) return ((unsigned short)~crc);
	for ( i = 0 ; i < nChars; i++ ) {  
		data=(unsigned int)0xff & *filename++;
		for (j=0; j < 8; j++ ) {
			if ((crc & 0x0001) ^ (data & 0x0001)){
				crc = (unsigned short)((crc >> 1) ^ POLY);
			} else {
				crc >>= 1;
			}
			data >>= 1;
		}
	}
	crc = (unsigned short)~crc;
	data = crc;
	crc = (unsigned short)((crc << 8) | (data >> 8 & 0xff));
	return crc;
}

short CAssociateArray::CheckSum(char *filename)
{
	int len = strlen(filename);
	if (len == 0)
		return 1;
	short avg = 0;
	for(int j = 0 ; j < len ; j++)
		avg =(short)(avg + ((short)*(filename+j)));
	return avg;
}

bool CAssociateArray::Add(char *src, char *tgt)
{
	char * dsa = NULL;
	gkey = Crc16(src);
	gkey2 = CheckSum(src);
	unsigned long longkey = (gkey << 16) + gkey2;
	WaitForSingleObject(hlock_aamap,INFINITE);
	ResetEvent(hlock_aamap);
	if(!aamap.Lookup(longkey,dsa))
	{
		char * tgttmp = new char[strlen(tgt)+1];
		strcpy(tgttmp,tgt);
		aamap.SetAt(longkey,tgttmp);
		SetEvent(hlock_aamap);
		WaitForSingleObject(hlock_garbagelist_list,INFINITE);
		ResetEvent(hlock_garbagelist_list);
		garbagelist.AddTail(tgttmp);
		SetEvent(hlock_garbagelist_list);
		return true;
	}
	else
	{
		SetEvent(hlock_aamap);
		char tmp[256] = "";
		wsprintf(tmp,"%s,%s",src,tgt);
		MessageBox(NULL,tmp,"WARNING DUPE KEY",MB_OK);
		return false;
	}
}

bool CAssociateArray::Get(char *src, char *tgt)
{
	char* tmp = NULL;
	gkey = Crc16(src);
	gkey2 = CheckSum(src);
	glongkey = (gkey << 16) + gkey2;
	WaitForSingleObject(hlock_aamap,INFINITE);
	ResetEvent(hlock_aamap);
	if(aamap.Lookup(glongkey,tmp))
	{
		strcpy(tgt,tmp);
		SetEvent(hlock_aamap);
		return true;
	}
	else
	{
		SetEvent(hlock_aamap);
		strcpy(tgt,"");
		return false;
	}
}

unsigned long CAssociateArray::hash(char *filename)
{
	int nChars = strlen(filename);
	const unsigned int POLY = 0x8468;
	int i,j,data;
	short avg = 0;
	unsigned short crc = 0xffff;
	if (nChars == 0) return ((unsigned short)~crc);
	for ( i = 0 ; i < nChars; i++ ) 
	{  
		data=(unsigned int)0xff & *filename++;
		for (j=0; j < 8; j++ ) 
		{
			if ((crc & 0x0001) ^ (data & 0x0001))
				crc = (unsigned short)((crc >> 1) ^ POLY);
			else
				crc >>= 1;
			data >>= 1;
		}
	}
	crc = (unsigned short)~crc;
	data = crc;
	crc = (unsigned short)((crc << 8) | (data >> 8 & 0xff));
	for(j = 0 ; j < nChars ; j++)
		avg =(short)(avg + ((short)*(filename+j)));
	unsigned long longkey = (avg << 16) + crc;
	return longkey;
}
