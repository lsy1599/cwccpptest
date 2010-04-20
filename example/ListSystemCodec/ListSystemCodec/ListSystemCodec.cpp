// ListSystemCodec.cpp : 定義主控台應用程式的進入點。
//

#include <atlbase.h>
#include <atlstr.h>
#include <wmsdk.h>
#include <iostream>
#include <string>
using namespace std;

std::string ChooseFormatTag(WORD tag){
    switch(tag){
    case 0x0161:
        return "Windows Media Audio.";
    case 0x0162:
        return "Windows Media Audio 9 Professional";
    case 0x0163:
        return "Windows Media Audio 9 Lossless";
    case 0x0001:
        return "PCM audio";
    case 0xFFFE:
        return "Indicates that the format is specified in the WAVEFORMATEXTENSIBLE.SubFormat member";
    default:
        return "unknown";
    }
}

/// ref: http://msdn.microsoft.com/en-us/library/aa391545%28VS.85%29.aspx
void ListFormat(WM_MEDIA_TYPE * pType){
    if (pType->formattype == WMFORMAT_VideoInfo){    
        cout << "\t\tformat type: VIDEO\n";
        WMVIDEOINFOHEADER* p = (WMVIDEOINFOHEADER*) pType->pbFormat;
        
    }else if (pType->formattype == WMFORMAT_WaveFormatEx){
        cout << "\t\tformat type: WAVE\n";
        WAVEFORMATEX *pWfx = (WAVEFORMATEX *) pType->pbFormat;        
        cout << "\t\t\tFormat Tag: " << ChooseFormatTag(pWfx->wFormatTag) << "(" << hex << pWfx->wFormatTag << ")" << endl;
        cout << "\t\t\tChannel: " << pWfx->nChannels << endl;
        cout << "\t\t\tSample Per Sec: " << pWfx->nSamplesPerSec << endl; // 一般 8k, 11025k, 441k(PCM)
        cout << "\t\t\tAvgBytesPerSec: " << pWfx->nAvgBytesPerSec << endl; 
        cout << "\t\t\tnBlockAlign: " << pWfx->nBlockAlign << endl;
        cout << "\t\t\tcbSize: " << pWfx->cbSize << endl;
        
    //pType->formattype != WMFORMAT_WaveFormatEx            
    
    //pWfx->nAvgBytesPerSec
    //pWfx->nSamplesPerSec
    //pWfx->nChannels
    //pWfx->wFormatTag
    //pWfx->nBlockAlign        
    }else if (pType->formattype == WMFORMAT_MPEG2Video){
        cout << "\t\tformat type: MPEG2 VIDEO\n";
        
    }else if (pType->formattype ==  WMFORMAT_WebStream){
        cout << "\t\tformat type: Web Stream\n";
        
    }else if (pType->formattype == WMFORMAT_Script){
        cout << "\t\tformat type: Script\n";
        
    }
    

}
//
//void ListVideoCodec(CComQIPtr<IWMCodecInfo>& pIWMInfo){
//    DWORD cCodecs;    
//    HRESULT hr = pIWMInfo->GetCodecInfoCount( WMMEDIATYPE_Video,
//                                          &cCodecs );       
//    if (FAILED(hr)){
//        cout << "GetCodecInfoCount fail\n";
//    }                                            
//    cout << "Video Codec: " << cCodecs << endl;
//    for(DWORD i=0; i<cCodecs; ++i){
//        DWORD cFormats;
//        hr = pIWMInfo->GetCodecFormatCount( WMMEDIATYPE_Audio,
//                                            i,
//                                            &cFormats );        
//        cout << "\t Format: " << cFormats << endl;    
//        CComQIPtr<IWMCodecInfo> pCodecInfo = pIWMInfo;
//        WM_MEDIA_TYPE *pMT = NULL;
//        for(DWORD j = 0; j < cFormats; j++ ) {
//            CComPtr<IWMStreamConfig> pStreamConfig;
//            hr = pCodecInfo->GetCodecFormat( WMMEDIATYPE_Video,
//                                                 i,
//                                                 j,
//                                                 &pStreamConfig );
//                                                 
//            CComQIPtr<IWMVideoMediaProps> pProps;
//            DWORD cbMT;
//            hr = pProps->GetMediaType( NULL, &cbMT );
//            
//            if (pMT != NULL){
//                delete[] pMT;
//                pMT = NULL;
//            }
//            pMT = (WM_MEDIA_TYPE *) new BYTE[ cbMT ];
//            hr = pProps->GetMediaType( pMT, &cbMT );
//            ListFormat(pMT);
//        }
//    }
//}
//
//void ListAudioCodec(CComQIPtr<IWMCodecInfo>& pIWMInfo){
//    DWORD cCodecs;
//    // WMMEDIATYPE_Video or WMMEDIATYPE_Audio
//    HRESULT hr = pIWMInfo->GetCodecInfoCount( WMMEDIATYPE_Audio,
//                                          &cCodecs );    
//    if (FAILED(hr)){
//        cout << "GetCodecInfoCount fail\n";
//    }                                            
//    cout << "Audio Codec: " << cCodecs << endl;
//    
//    for(int i =0;i < cCodecs; ++i ) {
//        DWORD cFormats;
//        hr = pIWMInfo->GetCodecFormatCount( WMMEDIATYPE_Audio,
//                                            i,
//                                            &cFormats );        
//        cout << "\t Format: " << cFormats << endl;
//        
//        
//        
//        WM_MEDIA_TYPE   *pType = NULL;
//        for(int j = 0; j < cFormats; ++j ){
//            CComPtr<IWMStreamConfig> pIWMStreamConfig;            
//            hr = pIWMInfo->GetCodecFormat( WMMEDIATYPE_Audio,
//                                           i,
//                                           j,
//                                           &pIWMStreamConfig );                
//                                        
//            CComPtr<IWMMediaProps>   pIMP;
//            hr = pIWMStreamConfig->QueryInterface( IID_IWMMediaProps,
//                                        ( void ** )&pIMP );       
//                                        
//            DWORD cbType = 0;                            
//            hr = pIMP->GetMediaType( NULL, &cbType );   
//            if (pType != NULL){
//                delete[] pType;
//                pType= NULL;
//            } 
//            
//            pType = (WM_MEDIA_TYPE *) new BYTE[ cbType ];                                                                        
//            if( !pType ){
//                hr = E_OUTOFMEMORY;
//                break;
//            }            
//            hr = pIMP->GetMediaType( pType, &cbType );
//            
//            ListFormat(pType);
//        }                                            
//    }                        
//}


template<REFGUID IID_CODEC>
void ListCodec(CComQIPtr<IWMCodecInfo>& pIWMInfo){
    DWORD cCodecs;
    // WMMEDIATYPE_Video or WMMEDIATYPE_Audio
    HRESULT hr = pIWMInfo->GetCodecInfoCount( IID_CODEC, &cCodecs );    
    if (FAILED(hr)){
        cout << "GetCodecInfoCount fail\n";
    }                                            
    cout << cCodecs << endl;
    
    for(int i =0;i < cCodecs; ++i ) {
        DWORD cFormats;
        hr = pIWMInfo->GetCodecFormatCount( IID_CODEC,
                                            i,
                                            &cFormats );        
        cout << "\t Format: " << cFormats << endl;
        
        
        
        WM_MEDIA_TYPE   *pType = NULL;
        for(int j = 0; j < cFormats; ++j ){
            CComPtr<IWMStreamConfig> pIWMStreamConfig;            
            hr = pIWMInfo->GetCodecFormat( IID_CODEC,
                                           i,
                                           j,
                                           &pIWMStreamConfig );                
                                        
            CComPtr<IWMMediaProps>   pIMP;
            hr = pIWMStreamConfig->QueryInterface( IID_IWMMediaProps,
                                        ( void ** )&pIMP );       
                                        
            DWORD cbType = 0;                            
            hr = pIMP->GetMediaType( NULL, &cbType );   
            if (pType != NULL){
                delete[] pType;
                pType= NULL;
            } 
            
            pType = (WM_MEDIA_TYPE *) new BYTE[ cbType ];                                                                        
            if( !pType ){
                hr = E_OUTOFMEMORY;
                break;
            }            
            hr = pIMP->GetMediaType( pType, &cbType );
            
            ListFormat(pType);
        }                                            
    }                        
}

int _tmain(int argc, _TCHAR* argv[]){
//CComQIPtr<IWMProfileManager>

    //CComPtr<IWMProfileManager> pIWMProfileManage;
    IWMProfileManager *pIWMProfileManage = NULL;
    HRESULT hr = WMCreateProfileManager( &pIWMProfileManage );
    if (FAILED(hr)){
        cout << "Create Profile Manager fail\n";
    }       
    IWMCodecInfo *pCodecInfo = NULL;
hr = pIWMProfileManage->QueryInterface( IID_IWMCodecInfo,
                                       (void **) &pCodecInfo );

        DWORD cCodecs;
        hr = pCodecInfo->GetCodecInfoCount( WMMEDIATYPE_Video, &cCodecs );
            
    //CComQIPtr<IWMCodecInfo> pIWMInfo = pIWMProfileManage;
    //cout << "Audio Codec: ";
    //ListCodec<WMMEDIATYPE_Audio>( pIWMInfo );
    //cout << "Video Codec: ";
    //ListCodec<WMMEDIATYPE_Video>( pIWMInfo );
    
    //ListVideoCodec(pIWMInfo);    
    //ListAudioCodec(pIWMInfo);                         
    
	return 0;
}

