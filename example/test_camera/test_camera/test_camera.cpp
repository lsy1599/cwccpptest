#include "stdafx.h"
#include <rpcsal.h>
#include <dshow.h>
#include <iostream>

#pragma comment(lib, "strmiids.lib")

using namespace std;

int main(){
    ::CoInitialize(NULL);
        {
        CComPtr<IGraphBuilder> pGraphBuilder;
        pGraphBuilder.CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER);

        CComPtr<ICaptureGraphBuilder2> m_pCapture; 
        m_pCapture.CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC);

        // Filter �M Capture �i��s�� 
        m_pCapture->SetFiltergraph(pGraphBuilder); 

        // �C�|�]�� 
        CComPtr<ICreateDevEnum> pCde; 
        pCde.CoCreateInstance (CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC);

        CComPtr<IEnumMoniker> pEm;
        pCde->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);

        CComPtr<IMoniker> pM; 
        ULONG cFetched; 
        CComPtr<IBaseFilter> pBf; 
        HRESULT ret = pEm->Next(1, &pM, &cFetched);
        pM.Detach();
        ret = pEm->Next(1, &pM, &cFetched);
        pM.Detach();
        ret = pEm->Next(1, &pM, &cFetched);
        pM.Detach();
        if(pEm->Next(1, &pM, &cFetched)==S_OK) {
            
            //�]���p�� 
            pM->BindToObject(0,0,IID_IBaseFilter, (void**)&pBf); 
            pM.Release(); 
        } else { 
            // �S�� Webcam �]��
            return 0; 
        } 

        //�N�]�ƲK�[��graph 
        pGraphBuilder->AddFilter(pBf, L"Video Capture"); 

        // �s���@�ӷ����f 
        m_pCapture->RenderStream(
            &PIN_CATEGORY_PREVIEW,
            &MEDIATYPE_Video,
            pBf,
            NULL,
            NULL
       ); 

        CComQIPtr<IMediaControl> m_pMC = pGraphBuilder; 

        // �Ұ�
        m_pMC->Run();
        int count = 0;
        while(1){
            ::Sleep(1000);
            ++count;
            if (count > 300){
            break;
            }
            }
            m_pMC->Stop();
            
        }
        
        ::CoUninitialize(); 
        return 0;
    }