// WriteDIB		- Writes a DIB to file
// Returns		- TRUE on success
// szFile		- Name of file to write to
// hDIB			- Handle of the DIB
BOOL WriteDIB( LPTSTR szFile, HANDLE hDIB)
{
	BITMAPFILEHEADER	hdr;
	LPBITMAPINFOHEADER	lpbi;

	if (!hDIB)
		return FALSE;

	CFile file;
	if( !file.Open( szFile, CFile::modeWrite|CFile::modeCreate) )
		return FALSE;

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	int nColors = 1 << lpbi->biBitCount;

	// Fill in the fields of the file header 
	hdr.bfType		= ((WORD) ('M' << 8) | 'B');	// is always "BM"
	hdr.bfSize		= GlobalSize (hDIB) + sizeof( hdr );
	hdr.bfReserved1 	= 0;
	hdr.bfReserved2 	= 0;
	hdr.bfOffBits		= (DWORD) (sizeof( hdr ) + lpbi->biSize +
						nColors * sizeof(RGBQUAD));

	// Write the file header 
	file.Write( &hdr, sizeof(hdr) );

	// Write the DIB header and the bits 
	file.Write( lpbi, GlobalSize(hDIB) );

	return TRUE;
}


void  SaveBitmap(char *szFilename,HBITMAP hBitmap)

{

      HDC        hdc=NULL;

      FILE*      fp=NULL;

      LPVOID     pBuf=NULL;

      BITMAPINFO bmpInfo;

      BITMAPFILEHEADER  bmpFileHeader; 

      do{ 

            hdc=GetDC(NULL);

            ZeroMemory(&bmpInfo,sizeof(BITMAPINFO));

            bmpInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);

            GetDIBits(hdc,hBitmap,0,0,NULL,&bmpInfo,DIB_RGB_COLORS); 

            if(bmpInfo.bmiHeader.biSizeImage<=0)

            bmpInfo.bmiHeader.biSizeImage=bmpInfo.bmiHeader.biWidth*abs(bmpInfo.bmiHeader.biHeight)*(bmpInfo.bmiHeader.biBitCount+7)/8;

            if((pBuf = malloc(bmpInfo.bmiHeader.biSizeImage))==NULL)

            {

                  MessageBox( NULL, "Unable to Allocate Bitmap Memory", "Error", MB_OK|MB_ICONERROR);

                  break;

            }           

            bmpInfo.bmiHeader.biCompression=BI_RGB;

            GetDIBits(hdc,hBitmap,0,bmpInfo.bmiHeader.biHeight,pBuf, &bmpInfo, DIB_RGB_COLORS);       

            if((fp = fopen(szFilename,"wb"))==NULL)

            {

                  MessageBox( NULL, "Unable to Create Bitmap File", "Error", MB_OK|MB_ICONERROR);

                  break;

            } 

            bmpFileHeader.bfReserved1=0;

            bmpFileHeader.bfReserved2=0;

            bmpFileHeader.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+bmpInfo.bmiHeader.biSizeImage;

            bmpFileHeader.bfType='MB';

            bmpFileHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER); 

            fwrite(&bmpFileHeader,sizeof(BITMAPFILEHEADER),1,fp);

            fwrite(&bmpInfo.bmiHeader,sizeof(BITMAPINFOHEADER),1,fp);

            fwrite(pBuf,bmpInfo.bmiHeader.biSizeImage,1,fp); 

      }while(false); 

            if(hdc)     ReleaseDC(NULL,hdc); 

            if(pBuf)    free(pBuf); 

            if(fp)      fclose(fp);

}