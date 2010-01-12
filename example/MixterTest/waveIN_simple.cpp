#include "waveIN_simple.h"

const char* LineToString(DWORD fdwLine){
    switch(fdwLine){
    case MIXERLINE_LINEF_ACTIVE :
        return "MIXERLINE_LINEF_ACTIVE ";
    case MIXERLINE_LINEF_DISCONNECTED :
        return "MIXERLINE_LINEF_DISCONNECTED ";
    case MIXERLINE_LINEF_SOURCE :
        return "MIXERLINE_LINEF_SOURCE ";
    default:
        return "Unknown";
    }
}

void dumpMixerLine(MIXERLINE& mxLine){
    using namespace std;

    cout<< "#--Begin\n"
        << "Destination: " << mxLine.dwDestination << endl
        << "Source: " << mxLine.dwSource<< endl
        << "Line Id: " << mxLine.dwLineID << endl
        << "Component Type: " << mxLine.dwComponentType << endl
        << "Name: " << mxLine.szName << endl
        //<< "Line: " << LineToString(mxLine.fdwLine) << endl
        //<< "User Data: " << mxLine.dwUser << endl
        << "Channels: " << mxLine.cChannels << endl
        << "Connections: " << mxLine.cConnections << endl
        << "Controls: " << mxLine.cControls << endl
        << "Product Name: " << mxLine.Target.szPname << endl
        << "#--End\n\n";

}
//---------------------------- IMPLEMENTATION ----------------------------------------------------

vector<CWaveINSimple*> CWaveINSimple::m_arrWaveINDevices;
QMutex CWaveINSimple::m_qGlobalMutex;
volatile bool CWaveINSimple::m_isDeviceListLoaded = false;

//------------------------------------------------------------------------------
#pragma region CMixerLine
//------------------------------------------------------------------------------
/**
 * 建構子
 * 
 * @param	MixerHandle		混音裝置代碼
 * @param	pMxLine			
 */
CMixerLine::CMixerLine(HMIXER MixerHandle, MIXERLINE *pMxLine) {
	this->m_MixerHandle = MixerHandle;
	memcpy(&this->m_MxLine, pMxLine, sizeof(MIXERLINE));
}
//------------------------------------------------------------------------------
/**
 * 選取
 *
 * @see mixerGetLineInfo()
 * @see mixerGetLineControls()
 * @see mixerGetControlDetails()
 * @see mixerSetControlDetails()
 * @see MIXERLINE
 * @see MIXERLINECONTROLS
 */
void CMixerLine::Select() {
	DWORD i;
	MIXERLINE mxl;
	BOOL bOneItemOnly = FALSE;

	// Get the line info for the WaveIN destination line
	mxl.cbStruct = sizeof(MIXERLINE);
	mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_WAVEIN;
	mixerGetLineInfo((HMIXEROBJ) this->m_MixerHandle, &mxl, MIXER_GETLINEINFOF_COMPONENTTYPE);

	// Find a LIST control, if any, for the WaveIN line
	LPMIXERCONTROL pmxctrl = (LPMIXERCONTROL) malloc(mxl.cControls * sizeof(MIXERCONTROL));
	if (pmxctrl != NULL) {
		MIXERLINECONTROLS mxlctrl = {sizeof(mxlctrl), mxl.dwLineID, 0, mxl.cControls,
			sizeof(MIXERCONTROL), pmxctrl};
		mixerGetLineControls((HMIXEROBJ) this->m_MixerHandle, &mxlctrl, MIXER_GETLINECONTROLSF_ALL);

		// Now walk through each control to find a type of LIST control. This
		// can be either Mux, Single-select, Mixer or Multiple-select.
		for(i=0; i < mxl.cControls; i++) {
			if (MIXERCONTROL_CT_CLASS_LIST == (pmxctrl[i].dwControlType & MIXERCONTROL_CT_CLASS_MASK)) {
				break;
			}
		}

		if (i < mxl.cControls) {
			// Found a LIST control
			// Check if the LIST control is a Mux or Single-select type
			switch (pmxctrl[i].dwControlType) {
				case MIXERCONTROL_CONTROLTYPE_MUX:
				case MIXERCONTROL_CONTROLTYPE_SINGLESELECT:
					bOneItemOnly = TRUE;
			}

			DWORD cChannels = mxl.cChannels, cMultipleItems = 0;
			if (MIXERCONTROL_CONTROLF_UNIFORM & pmxctrl[i].fdwControl) cChannels = 1;
			if (MIXERCONTROL_CONTROLF_MULTIPLE & pmxctrl[i].fdwControl) {
				cMultipleItems = pmxctrl[i].cMultipleItems;
			}

			// Get the text description of each item
			LPMIXERCONTROLDETAILS_LISTTEXT plisttext = (LPMIXERCONTROLDETAILS_LISTTEXT)
				malloc(cChannels * cMultipleItems * sizeof(MIXERCONTROLDETAILS_LISTTEXT));

			if (plisttext != NULL) {
				MIXERCONTROLDETAILS mxcd = {sizeof(mxcd), pmxctrl[i].dwControlID,
				cChannels, (HWND)cMultipleItems, sizeof(MIXERCONTROLDETAILS_LISTTEXT), (LPVOID) plisttext};
				mixerGetControlDetails((HMIXEROBJ) this->m_MixerHandle, &mxcd, MIXER_GETCONTROLDETAILSF_LISTTEXT);

				// Now get the value for each item
				LPMIXERCONTROLDETAILS_BOOLEAN plistbool = (LPMIXERCONTROLDETAILS_BOOLEAN)
					malloc(cChannels * cMultipleItems * sizeof(MIXERCONTROLDETAILS_BOOLEAN));

				if (plistbool != NULL) {

					mxcd.cbDetails = sizeof( MIXERCONTROLDETAILS_BOOLEAN);
					mxcd.paDetails = plistbool;
					mixerGetControlDetails((HMIXEROBJ) this->m_MixerHandle, &mxcd, MIXER_GETCONTROLDETAILSF_VALUE);

					// Select the class' line item
					for (DWORD j=0; j<cMultipleItems; j = j + cChannels) {
						if (0 == lstrcmp(plisttext[j].szName, this->GetName())) {
							// Select it for both left and right channels
							plistbool[j].fValue = plistbool[j+ cChannels - 1].fValue = 1;
						}
						else if (bOneItemOnly) {
							// Mux or Single-select allows only one item to be selected
							// so clear other items as necessary
							plistbool[j].fValue = plistbool[j+ cChannels - 1].fValue = 0;
						}
					}
					// Now actually set the new values in
					mixerSetControlDetails((HMIXEROBJ) this->m_MixerHandle, &mxcd, MIXER_SETCONTROLDETAILSF_VALUE);

					free(plistbool);
				}

				free(plisttext);
			}
		}

		free(pmxctrl);
	}
}
//------------------------------------------------------------------------------
/**
 * 音量設定
 * 
 * @param	nVolumeLevel	音量，合理值 0-100
 * @see     mixerSetControlDetails()
 * @see     MIXERLINECONTROLS
 * @see     MIXERCONTROL
 */
void CMixerLine::SetVolume(UINT nVolumeLevel) {
	MIXERCONTROL MxCtrl;
	MIXERLINECONTROLS MxLCtrl;
	MIXERCONTROLDETAILS_UNSIGNED uValue[2];
	MIXERCONTROLDETAILS MxControlDetails;
	UINT nVolume;

	if (nVolumeLevel > 100){
		nVolume = 100;
	}else{
		nVolume = nVolumeLevel;
	}

	// Find volume control, if any, of the line
	MxLCtrl.cbStruct = sizeof(MIXERLINECONTROLS);
	MxLCtrl.dwLineID = this->m_MxLine.dwLineID;
	MxLCtrl.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
	MxLCtrl.cControls = 1;
	MxLCtrl.cbmxctrl = sizeof(MIXERCONTROL);
	MxLCtrl.pamxctrl = &MxCtrl;

	if (!mixerGetLineControls((HMIXEROBJ) this->m_MixerHandle, &MxLCtrl, MIXER_GETLINECONTROLSF_ONEBYTYPE)) {
		// Found, so proceed
		MxControlDetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
		MxControlDetails.dwControlID = MxCtrl.dwControlID;
		MxControlDetails.cChannels = this->m_MxLine.cChannels;

		if (MxControlDetails.cChannels > 2) MxControlDetails.cChannels = 2;
		if (MIXERCONTROL_CONTROLF_UNIFORM &  MxCtrl.fdwControl) MxControlDetails.cChannels = 1;

		MxControlDetails.cMultipleItems = 0;
		MxControlDetails.hwndOwner = (HWND) 0;
		MxControlDetails.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
		MxControlDetails.paDetails = uValue;

		nVolume = MxCtrl.Bounds.dwMinimum + (UINT) (((MxCtrl.Bounds.dwMaximum - MxCtrl.Bounds.dwMinimum) * nVolume)/100);
		// Set volume (for both channels)
		uValue[0].dwValue = uValue[1].dwValue = nVolume;
		mixerSetControlDetails((HMIXEROBJ) this->m_MixerHandle, &MxControlDetails, MIXER_SETCONTROLDETAILSF_VALUE);
	}
}
//------------------------------------------------------------------------------
/**
 * 去除靜音
 *
 * @see     MIXERCONTROL
 * @see     MIXERCONTROLDETAILS
 * @see     mixerGetLineControls()
 * @see     mixerSetControlDetails()
 */
void CMixerLine::UnMute() {
	MIXERCONTROL MxCtrl;
	MIXERLINECONTROLS MxLCtrl;
	MIXERCONTROLDETAILS_BOOLEAN bValue[2];
	MIXERCONTROLDETAILS MxControlDetails;

	// Find mute control, if any, of the line
	MxLCtrl.cbStruct = sizeof(MIXERLINECONTROLS);
	MxLCtrl.dwLineID = this->m_MxLine.dwLineID;
	MxLCtrl.dwControlType = MIXERCONTROL_CONTROLTYPE_MUTE;
	MxLCtrl.cControls = 1;
	MxLCtrl.cbmxctrl = sizeof(MIXERCONTROL);
	MxLCtrl.pamxctrl = &MxCtrl;

	//mlc.cControls   = mCControls;
	MMRESULT ret;
//	if (m_Type == Record){
		ret = mixerGetLineControls((HMIXEROBJ) this->m_MixerHandle, &MxLCtrl, MIXER_GETLINECONTROLSF_ONEBYTYPE);
		
	//}else{
	//	ret = mixerGetLineControls((HMIXEROBJ) this->m_MixerHandle, &MxLCtrl, MIXER_GETLINECONTROLSF_ONEBYTYPE/*MIXER_GETLINECONTROLSF_ALL*/);
	//}


	if (!ret) {
		// Found, so proceed
		MxControlDetails.cbStruct = sizeof(MIXERCONTROLDETAILS);
		MxControlDetails.dwControlID = MxCtrl.dwControlID;
		MxControlDetails.cChannels = this->m_MxLine.cChannels;

		if (MxControlDetails.cChannels > 2) MxControlDetails.cChannels = 2;
		if (MIXERCONTROL_CONTROLF_UNIFORM &  MxCtrl.fdwControl) MxControlDetails.cChannels = 1;

		MxControlDetails.cMultipleItems = 0;
		MxControlDetails.hwndOwner = (HWND) 0;
		MxControlDetails.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
		MxControlDetails.paDetails = bValue;
		mixerGetControlDetails((HMIXEROBJ) this->m_MixerHandle, &MxControlDetails, MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE);
		// Unmute the line (for both channels)
		bValue[0].fValue = bValue[1].fValue = 0;
		mixerSetControlDetails((HMIXEROBJ) this->m_MixerHandle, &MxControlDetails, MIXER_SETCONTROLDETAILSF_VALUE);
	}
}
///////////////////////////////////////////////////////////////////////////
#pragma endregion


#pragma region CMixer
//------------------------------------------------------------------------------
/**
 * 取得指定名稱的混音裝置 Line
 * 
 * @see 
 * @return	混音裝置 Line
 */
CMixerLine& CMixer::GetLine() {
	vector<CMixerLine*>::iterator itPos = this->m_arrMixerLines.begin();
	CMixerLine* pMixerLine = NULL;


	this->m_qLocalMutex.Lock();

	for (; itPos < this->m_arrMixerLines.end(); itPos++) {
		if (smc.isEqual( ((CMixerLine*) *itPos)->GetName() ) ) {
			pMixerLine = *itPos;
			break;
		}
	}
	this->m_qLocalMutex.Unlock();
	

	if (pMixerLine == NULL) {
		throw "Mixer's line not found.";
	}
	return *pMixerLine;
}
//------------------------------------------------------------------------------
/**
 * 取得指定名稱的混音裝置 Line
 * 
 * @see
 * @param	pLineName	混音裝置 Line 名稱
 * @return	混音裝置 Line
 */
CMixerLine& CMixer::GetLine(const TCHAR *pLineName) {
	vector<CMixerLine*>::iterator itPos = this->m_arrMixerLines.begin();
	CMixerLine* pMixerLine = NULL;

	if (pLineName != NULL) {
		this->m_qLocalMutex.Lock();
		for (; itPos < this->m_arrMixerLines.end(); itPos++) {
			// 比較 Line 名稱
			if (::lstrcmp(((CMixerLine*) *itPos)->GetName(), pLineName) == 0) {
				pMixerLine = *itPos;
				break;
			}
		}
		this->m_qLocalMutex.Unlock();
	}

	if (pMixerLine == NULL) {
		throw "Mixer's line not found.";
	}
	return *pMixerLine;
}
//------------------------------------------------------------------------------
/**
 *
 *
 * @return -1=沒有任何 Control
 */
DWORD CMixer::GetLinesByComponent(DWORD fdwInfo){
    MIXERLINE mxLine;
	mxLine.cbStruct = sizeof(MIXERLINE);
	mxLine.dwComponentType = fdwInfo;

	MMRESULT err = mixerGetLineInfo((HMIXEROBJ) this->m_MixerHandle, &mxLine, MIXER_GETLINEINFOF_COMPONENTTYPE);
	if (err) {
		return -1;
	}

    return mxLine.cConnections;
}
//------------------------------------------------------------------------------
//template<typename EnumLinesCallback>
void CMixer::EnumLines(DWORD fdwInfo, EnumLinesCallback func){
	DWORD dwMixLines, i;
	CMixerLine *pMixerLine;
	MIXERLINE mxLine;
	MMRESULT err;

    // 取得錄音控制
	mxLine.cbStruct = sizeof(MIXERLINE);
	mxLine.dwComponentType = fdwInfo;

	err = mixerGetLineInfo((HMIXEROBJ) this->m_MixerHandle, &mxLine, MIXER_GETLINEINFOF_COMPONENTTYPE);
	if (err) {
		// Device doesn't have a WAVE recording control
		return;
	}
    dumpMixerLine(mxLine );
	dwMixLines = mxLine.cConnections;
	for (i = 0; i < dwMixLines; i++) {
		mxLine.cbStruct = sizeof(MIXERLINE);
		mxLine.dwSource = i;

		err = mixerGetLineInfo((HMIXEROBJ) this->m_MixerHandle, &mxLine, MIXER_GETLINEINFOF_SOURCE);
		if (!err ) {
            (this->*func)(mxLine);
		}
	}
}
//------------------------------------------------------------------------------
/**
 * 錄音 Lines 初始化
 *
 * @see     CMixerLine
 * @see     MIXERLINE
 * @see     mixerGetLineInfo()
 */
void CMixer::InitRecordLines(MIXERLINE& mxLine){
/**
 * MIXER_GETLINEINFOF_COMPONENTTYPE 以 MAXLINE.dwComponentType 取得 Mixter Line
 *
 * MIXER_GETLINEINFOF_DESTINATION   以 MAXLINE.dwDestination  取得 Mixter Line
 *
 * MIXER_GETLINEINFOF_LINEID        以 MAXLINE.dwLineID  取得 Mixter Line
 *
 * MIXER_GETLINEINFOF_SOURCE        以 MAXLINE.dwDestination 和 MAXLINE.dwSource 取得 Mixter Line
 */
/*
	DWORD dwMixLines, i;
	CMixerLine *pMixerLine;
	MIXERLINE mxLine;
	MMRESULT err;

    // 取得錄音控制
	mxLine.cbStruct = sizeof(MIXERLINE);
	mxLine.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_WAVEIN;

	err = mixerGetLineInfo((HMIXEROBJ) this->m_MixerHandle, &mxLine, MIXER_GETLINEINFOF_COMPONENTTYPE);
	if (err) {
		// Device doesn't have a WAVE recording control
		return;
	}

	dwMixLines = mxLine.cConnections;
	for (i = 0; i < dwMixLines; i++) {
		mxLine.cbStruct = sizeof(MIXERLINE);
		mxLine.dwSource = i;

		err = mixerGetLineInfo((HMIXEROBJ) this->m_MixerHandle, &mxLine, MIXER_GETLINEINFOF_SOURCE);
		if (!err) {
*/
            dumpMixerLine(mxLine );
			if (mxLine.dwComponentType != MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER) {
				CMixerLine *pMixerLine = new CMixerLine(this->m_MixerHandle, &mxLine);
				pMixerLine->SetType(Record);
				this->m_arrMixerLines.push_back(pMixerLine);
			}
/*
		}
	}
*/
}
//------------------------------------------------------------------------------
/**
 * 取得播放 Lines
 *
 */
void CMixer::InitPlaybackLines(MIXERLINE& mxLine){
/*
	DWORD dwMixLines, i;
	CMixerLine *pMixerLine;
	MIXERLINE mxLine;
	MMRESULT err;

	mxLine.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
	err = mixerGetLineInfo((HMIXEROBJ) this->m_MixerHandle, &mxLine, MIXER_GETLINEINFOF_COMPONENTTYPE);
    if (err){
        return;
    }
	dwMixLines = mxLine.cConnections;
	for (i = 0; i < dwMixLines; i++) {
		mxLine.cbStruct = sizeof(MIXERLINE);
		mxLine.dwSource = i;

		err = mixerGetLineInfo((HMIXEROBJ) this->m_MixerHandle, &mxLine, MIXER_GETLINEINFOF_SOURCE);
		if (!err) {
*/
			CMixerLine *pMixerLine = new CMixerLine(this->m_MixerHandle, &mxLine);
			pMixerLine->SetType(Playback);
			m_arrPlaybackMixerLines.push_back(pMixerLine);

			if (pMixerLine->isWave() || pMixerLine->isMicrophone() ){
				pMixerLine->UnMute();
			}
/*
		}
	}
*/
}
//------------------------------------------------------------------------------
/**
 * 混音裝置 Line 初始化，將所有的 Line 資訊放入陣列中
 *
 * @see InitPlaybackLines()
 * @see InitRecordLines()
 */
void CMixer::InitLines() {
    EnumLines(MIXERLINE_COMPONENTTYPE_DST_WAVEIN, &CMixer::InitRecordLines);
    EnumLines(MIXERLINE_COMPONENTTYPE_DST_SPEAKERS, &CMixer::InitPlaybackLines);
//    InitRecordLines(MIXERLINE_COMPONENTTYPE_DST_SPEAKERS);
    //InitPlaybackLines();
}
//------------------------------------------------------------------------------
struct OpenMixerFail: public std::exception{};

/**
 * 開啟混音裝置
 * 
 * @see	mixerOpen()
 */
void CMixer::Open() {
	MMRESULT err;

	this->m_qLocalMutex.Lock();

	if (this->m_MixerHandle == NULL) {
		err = mixerOpen(&this->m_MixerHandle, this->m_nWaveDeviceID, 0, 0, MIXER_OBJECTF_WAVEIN);
		if (err) {
			this->m_MixerHandle = NULL;
			this->m_qLocalMutex.Unlock();
			throw OpenMixerFail();//"Can't open Mixer Device.";
		}
		this->InitLines();
	}

	this->m_qLocalMutex.Unlock();
}
//------------------------------------------------------------------------------
/**
 * 關閉混音器裝置
 * 
 * @see	mixerClose()
 */
void CMixer::Close() {
	this->m_qLocalMutex.Lock();

	if (this->m_MixerHandle != NULL) {
		// 移除所有的 Line
		vector<CMixerLine*>::iterator itPos = this->m_arrMixerLines.begin();
		for (; itPos < this->m_arrMixerLines.end(); itPos++) {
			delete *itPos;
		}
		this->m_arrMixerLines.clear();

		itPos = this->m_arrPlaybackMixerLines.begin();
		for (; itPos < this->m_arrPlaybackMixerLines.end(); itPos++) {
			delete *itPos;
		}

		this->m_arrPlaybackMixerLines.clear();

		// 關閉混音裝置
		mixerClose(this->m_MixerHandle);
		this->m_MixerHandle = NULL;
	}

	this->m_qLocalMutex.Unlock();
}
//------------------------------------------------------------------------------
/**
 * 解構子
 * 
 */
CMixer::~CMixer() {
	this->Close();
}
//------------------------------------------------------------------------------
/**
 * 建構子
 * 
 * @param	nWaveDeviceID	Wave 設備編號
 */
CMixer::CMixer(UINT nWaveDeviceID): m_qLocalMutex(), m_playback_wave_idx(-1), m_playback_microphone_idx(-1){
	this->m_nWaveDeviceID = nWaveDeviceID;
	this->m_MixerHandle = NULL;
}
#pragma endregion

#pragma region CWaveINSimple
//------------------------------------------------------------------------------
/**
 * 開啟混音裝置
 *
 * @return	混音裝置
 */
CMixer& CWaveINSimple::OpenMixer() {
	this->m_Mixer.Open();
	return this->m_Mixer;
}
//------------------------------------------------------------------------------
/**
 * 取得指定名稱的混音裝置
 *
 * @return
 */
CWaveINSimple& CWaveINSimple::GetDevice() {
	CWaveINSimple* wINSimple = NULL;	

	GetDevices();

	
	m_qGlobalMutex.Lock();
	if (m_arrWaveINDevices.size() > 0){
		wINSimple = m_arrWaveINDevices[0];
	}
	m_qGlobalMutex.Unlock();
	

	if (wINSimple == NULL) {
		throw "Device not found.";
	}

	return *wINSimple;
}
//------------------------------------------------------------------------------
/**
 * 取得指定名稱的混音裝置
 *
 * @param	pDeviceName	混音裝置名稱
 * @return
 */
CWaveINSimple& CWaveINSimple::GetDevice(const TCHAR *pDeviceName) {
	CWaveINSimple* wINSimple = NULL;
	UINT i;

	GetDevices();

	if (pDeviceName != NULL) {
		m_qGlobalMutex.Lock();
		for (i = 0; i < m_arrWaveINDevices.size(); i++) {
			// 設備名稱比較
			if ((::lstrcmp(m_arrWaveINDevices[i]->GetName(), pDeviceName)) == 0) {
				wINSimple = m_arrWaveINDevices[i];
				break;
			}
		}
		m_qGlobalMutex.Unlock();
	}

	if (wINSimple == NULL) {
		throw "Device not found.";
	}

	return *wINSimple;
}
//------------------------------------------------------------------------------
/**
 * 解構子
 * 
 */
CWaveINSimple::~CWaveINSimple() {
	this->m_qLocalMutex.Lock();
	this->_Stop();
	if (this->m_WaveHeader[0].lpData != NULL) VirtualFree(this->m_WaveHeader[0].lpData, 0, MEM_RELEASE);
	this->m_qLocalMutex.Unlock();
}
//------------------------------------------------------------------------------
/**
 *  
 * 
 * @param	iLevel
 */
void CWaveINSimple::Close(int iLevel) {
	switch(iLevel) {
	case 1:
		waveInUnprepareHeader(this->m_WaveInHandle, &this->m_WaveHeader[1], sizeof(WAVEHDR));
	case 2:
		waveInUnprepareHeader(this->m_WaveInHandle, &this->m_WaveHeader[0], sizeof(WAVEHDR));
	case 3:
		// Close the WaveIN device.
		while ((waveInClose(this->m_WaveInHandle)) != MMSYSERR_NOERROR) ::Sleep(1);
	case 4:
		this->m_WaveInHandle = NULL;
		this->m_Receiver = NULL;
	}
}
//------------------------------------------------------------------------------
/**
 * 停止
 * 
 * 加入多執行緒的支援
 */
void CWaveINSimple::Stop() {
	this->m_qLocalMutex.Lock();
	this->_Stop();
	this->m_qLocalMutex.Unlock();
}
//------------------------------------------------------------------------------
/**
 * 停止
 * 
 */
void CWaveINSimple::_Stop() {
	if (this->m_WaveInHandle != NULL) {
		// Say to Thread that stop recording is requested.
		this->m_SIG = EXIT_SIG;

		// Stop recording and tell the driver to unqueue/return all of
		// our WAVEHDRs (via MM_WIM_DONE). The driver will return any
		// partially filled buffer that was currently recording.
		waveInReset(this->m_WaveInHandle);

		// Wait for the recording Thread to receive the MM_WIM_DONE for
		// each queued WAVEHDRs.
		while (this->m_BuffersDone < 2) ::Sleep(1);
		this->Close(1);

		this->m_WaveHeader[1].dwFlags = this->m_WaveHeader[0].dwFlags = 0;
	}
}
//------------------------------------------------------------------------------
/**
 * 開始進行音訊擷取
 *
 * 加入多執行緒的支援
 *
 * @see		_Start()
 * @param	pReceiver
 */
void CWaveINSimple::Start(IReceiver *pReceiver) {
	const char *message = NULL;

	this->m_qLocalMutex.Lock();

	try {
		this->_Start(pReceiver);
	}
	catch (const char *msg) {
		message = msg;
	}

	this->m_qLocalMutex.Unlock();
	if (message != NULL) throw message;
}
//------------------------------------------------------------------------------
/**
 * 開始進行音訊擷取
 * 
 * @see		CreateThread()
 * @see		CloseHandle()
 * @see		waveInOpen()
 * @see		waveInPrepareHeader()
 * @see		waveInAddBuffer()
 * @see		waveInStart()
 * @param	pReceiver
 */
void CWaveINSimple::_Start(IReceiver *pReceiver) {
	HANDLE	waveInThread;
	LPTHREAD_START_ROUTINE pStartRoutine = &CWaveINSimple::waveInProc;
	DWORD	dwThreadID;
	MMRESULT	err;

	if (this->m_WaveInHandle == NULL) {
		this->m_Receiver = pReceiver;
		this->m_SIG = WAIT_SIG;

		// Create the Thread that will receive incoming "blocks" of digital audio data
		// (sent from the driver). The main procedure of this thread is
		// CWaveINSimple::waveInProc(). We need to get the threadID and pass that
		// to waveInOpen().
		waveInThread = CreateThread(NULL, 0, pStartRoutine, (PVOID) this, 0, &dwThreadID);
		if (!waveInThread) {
			this->m_Receiver = NULL;
			throw "Can't create WAVE recording thread.";
		}
		CloseHandle(waveInThread);

		// Open the WaveIN Device, specifying Thread's ID as a callback.
		err = waveInOpen(&this->m_WaveInHandle, this->m_nWaveDeviceID, &this->m_waveFormat, dwThreadID, 0, CALLBACK_THREAD);
		if (err) {
			// Open failed, say to Thread to stop.
			this->m_SIG = EXIT_SIG;
			this->Close(4);
			throw "Can't open WaveIN Device.";
		}
		this->m_SIG = CONTINUE_SIG;

		// Allocate, prepare, and queue two buffers that the driver can
		// use to record blocks of audio data. Alloc buffers only one
		// time and use them until object is deleted.
		// Double-buffering is used.
		if (this->m_WaveHeader[0].lpData == NULL) {
			this->m_WaveHeader[0].lpData = (char *)VirtualAlloc(0, this->m_WaveHeader[0].dwBufferLength * 2, MEM_COMMIT, PAGE_READWRITE);
			if (this->m_WaveHeader[0].lpData == NULL) {
				this->Close(3);
				throw "Can't allocate memory for WAVE buffer.";
			}
		}
		this->m_WaveHeader[1].lpData = this->m_WaveHeader[0].lpData + this->m_WaveHeader[0].dwBufferLength;

		err = waveInPrepareHeader(this->m_WaveInHandle, &this->m_WaveHeader[0], sizeof(WAVEHDR));
		if (err) {
			this->Close(3);
			throw "Error preparing WAVEHDR 1.";
		}

		err = waveInPrepareHeader(this->m_WaveInHandle, &this->m_WaveHeader[1], sizeof(WAVEHDR));
		if (err) {
			this->Close(2);
			throw "Error preparing WAVEHDR 2.";
		}

		err = waveInAddBuffer(this->m_WaveInHandle, &this->m_WaveHeader[0], sizeof(WAVEHDR));
		if (err) {
			this->Close(1);
			throw "Error queueing WAVEHDR 1.";
		}

		err = waveInAddBuffer(this->m_WaveInHandle, &this->m_WaveHeader[1], sizeof(WAVEHDR));
		if (err) {
			this->m_BuffersDone = 1;
			this->Stop();
			throw "Error queueing WAVEHDR 2.";
		}

		// Start recording. Thread will now be receiving audio data.
		err = waveInStart(this->m_WaveInHandle);
		if (err) {
			this->Stop();
			throw "Error starting record.";
		}
	}
}
//------------------------------------------------------------------------------
/**
 * 建構子
 *
 * @see	WAVEINCAPS
 * @param	nWaveDeviceID	WaveIn 設備編號
 * @param	pWIC			設備資訊
 */
CWaveINSimple::CWaveINSimple(UINT nWaveDeviceID, WAVEINCAPS *pWIC): m_Mixer(nWaveDeviceID), m_qLocalMutex() {
	this->m_nWaveDeviceID	= nWaveDeviceID;
	memcpy(&this->m_wic, pWIC, sizeof(WAVEINCAPS));
	this->m_WaveInHandle	= NULL;
	this->m_Receiver		= NULL;

	//Initialize the WAVEFORMATEX for 16-bit, 44KHz, stereo.
	ZeroMemory(&this->m_waveFormat, sizeof(WAVEFORMATEX));
	this->m_waveFormat.wFormatTag		= WAVE_FORMAT_PCM;
	this->m_waveFormat.nChannels		= 2;
	this->m_waveFormat.nSamplesPerSec	= 44100;
	this->m_waveFormat.wBitsPerSample	= 16;
	this->m_waveFormat.nBlockAlign		= this->m_waveFormat.nChannels * (this->m_waveFormat.wBitsPerSample/8);
	this->m_waveFormat.nAvgBytesPerSec	= this->m_waveFormat.nSamplesPerSec * this->m_waveFormat.nBlockAlign;
	this->m_waveFormat.cbSize = 0;

	//Initialize the sound buffers, but don't allocate memory yet.
	ZeroMemory(this->m_WaveHeader, sizeof(WAVEHDR) * 2);
	this->m_WaveHeader[1].dwBufferLength = this->m_WaveHeader[0].dwBufferLength = this->m_waveFormat.nAvgBytesPerSec << 1;
}
//------------------------------------------------------------------------------
/**
 * 執行緒處理片段
 * 
 * @see		GetMessage()
 * @see		MM_WIM_DATA
 * @see		MM_WIM_OPEN
 * @see		MM_WIM_CLOSE
 * @param	arg
 * @return
 */
DWORD WINAPI CWaveINSimple::waveInProc(LPVOID arg) {
	MSG		msg;
	CWaveINSimple *_this = (CWaveINSimple *) arg;

	if (_this == NULL) return(0);

	while (_this->m_SIG == WAIT_SIG) ::Sleep(1);
	if (_this->m_SIG == EXIT_SIG) {
		// Call to waveInOpen failed.
		return(0);
	}

	while (GetMessage(&msg, 0, 0, 0) == 1) 	{
		switch (msg.message) {
			// A buffer has been filled by the driver
			case MM_WIM_DATA:
				// msg.lParam contains a pointer to the WAVEHDR structure
				// for the filled buffer.
				if ((((WAVEHDR *)msg.lParam)->dwBytesRecorded) && (_this->m_Receiver)) {

					// Send buffer to the m_Receiver (instance of the IReceiver)
					// for further processing
					_this->m_Receiver->ReceiveBuffer(((WAVEHDR *)msg.lParam)->lpData,
						((WAVEHDR *)msg.lParam)->dwBytesRecorded);
				}

				// Still recording?
				if (_this->m_SIG != EXIT_SIG) {
					// Yes. Then requeue this buffer so the driver can
					// use it for another block of audio data.
					waveInAddBuffer(_this->m_WaveInHandle, (WAVEHDR *)msg.lParam, sizeof(WAVEHDR));
				}
				else {
					// No, so another WAVEHDR has been returned after
					// recording has stopped. When we get all of them back,
					// m_BuffersDone will be equal to how many WAVEHDRs
					// we queued.
					++_this->m_BuffersDone;
				}
				break;

			// Main thread is opening the WAVE device.
			case MM_WIM_OPEN:
				_this->m_BuffersDone = 0;
				break;

			// Main thread is closing the WAVE device.
			case MM_WIM_CLOSE:
				return(0);
//				break;
		}
	}
	return(0);
}
//------------------------------------------------------------------------------
/**
 * 取得所有的 WaveIn 裝置
 *
 * @see	waveInGetDevCaps()
 * @see waveInGetNumDevs()
 * @see WAVEINCAPS 
 * @return	Wave In 裝置陣列	
 */
const vector<CWaveINSimple*>& CWaveINSimple::GetDevices() {
	UINT nInDev, i;
	WAVEINCAPS wic;
	CWaveINSimple *pWaveIn;

	m_qGlobalMutex.Lock();

	if (!m_isDeviceListLoaded) {
		nInDev = waveInGetNumDevs();

		for (i = 0; i < nInDev; i++) {
			if (!waveInGetDevCaps(i, &wic, sizeof(WAVEINCAPS))) {

				// We are only interested in devices supporting
				// 44.1 kHz, stereo, 16-bit, stereo input
				if (wic.dwFormats & WAVE_FORMAT_4S16) {
					pWaveIn = new CWaveINSimple(i, &wic);
					m_arrWaveINDevices.push_back(pWaveIn);
				}
			}
		}

		m_isDeviceListLoaded = true;
	}

	m_qGlobalMutex.Unlock();

	return m_arrWaveINDevices;
}
//------------------------------------------------------------------------------
/**
 *
 * 
 */
void CWaveINSimple::CleanUp() {
	m_qGlobalMutex.Lock();

	vector<CWaveINSimple*>::iterator itPos = m_arrWaveINDevices.begin();
	for (; itPos < m_arrWaveINDevices.end(); itPos++) {
		delete *itPos;
	}

	m_arrWaveINDevices.clear();
	m_isDeviceListLoaded = false;

	m_qGlobalMutex.Unlock();
}
#pragma endregion 