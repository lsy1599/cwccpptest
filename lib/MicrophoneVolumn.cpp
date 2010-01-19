#include "MicrophoneVolumn.h"
#include <tchar.h>
#include <limits.h>
#include <iostream>
#pragma comment(lib, "Winmm.lib");
CMicrophoneVolumn::CMicrophoneVolumn(DWORD dwInstance)
{
	m_nNumMixers = ::mixerGetNumDevs();
	m_dwIndex = ULONG_MAX;
	if (m_nNumMixers != 0)
	{
		if (::mixerOpen(&m_hMixer,
						0,
						dwInstance,
						NULL,
						MIXER_OBJECTF_MIXER | CALLBACK_WINDOW)
			!= MMSYSERR_NOERROR)
		{
			return ;//FALSE;
		}

		if (::mixerGetDevCaps(reinterpret_cast<UINT>(m_hMixer),
							  &m_mxcaps, sizeof(MIXERCAPS))
			!= MMSYSERR_NOERROR)
		{
			return ;//FALSE;
		}
	}
}

CMicrophoneVolumn::~CMicrophoneVolumn(void)
{
		if (m_hMixer != NULL)
	{
		::mixerClose(m_hMixer);
		m_hMixer = NULL;
	}
}

bool CMicrophoneVolumn::getSelect(){
	if (m_hMixer == NULL ||
		m_dwMultipleItems == 0 ||
		m_dwIndex >= m_dwMultipleItems)
	{
		return FALSE;
	}

	BOOL bRetVal = FALSE;

	MIXERCONTROLDETAILS_BOOLEAN *pmxcdSelectValue =
		new MIXERCONTROLDETAILS_BOOLEAN[m_dwMultipleItems];

	if (pmxcdSelectValue != NULL)
	{
		MIXERCONTROLDETAILS mxcd;
		mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
		mxcd.dwControlID = m_dwSelectControlID;
		mxcd.cChannels = 1;
		mxcd.cMultipleItems = m_dwMultipleItems;
		mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
		mxcd.paDetails = pmxcdSelectValue;
		if (::mixerGetControlDetails(reinterpret_cast<HMIXEROBJ>(m_hMixer),
									 &mxcd,
									 MIXER_OBJECTF_HMIXER |
									 MIXER_GETCONTROLDETAILSF_VALUE)
			== MMSYSERR_NOERROR)
		{
			if ( pmxcdSelectValue[m_dwIndex].fValue != 0){
				bRetVal = TRUE;
			}				
		}

		delete []pmxcdSelectValue;
	}

	return bRetVal;
}

bool CMicrophoneVolumn::setSelect(bool enable)const{
	LONG lVal = enable?1:0;

	if (m_hMixer == NULL ||
		m_dwMultipleItems == 0 ||
		m_dwIndex >= m_dwMultipleItems)
	{
		return FALSE;
	}

	BOOL bRetVal = FALSE;

	// get all the values first
	MIXERCONTROLDETAILS_BOOLEAN *pmxcdSelectValue =
		new MIXERCONTROLDETAILS_BOOLEAN[m_dwMultipleItems];

	if (pmxcdSelectValue != NULL)
	{
		MIXERCONTROLDETAILS mxcd;
		mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
		mxcd.dwControlID = m_dwSelectControlID;
		mxcd.cChannels = 1;
		mxcd.cMultipleItems = m_dwMultipleItems;
		mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
		mxcd.paDetails = pmxcdSelectValue;
		if (::mixerGetControlDetails(reinterpret_cast<HMIXEROBJ>(m_hMixer),
									 &mxcd,
									 MIXER_OBJECTF_HMIXER |
									 MIXER_GETCONTROLDETAILSF_VALUE)
			== MMSYSERR_NOERROR)
		{
//			ASSERT(m_dwControlType == MIXERCONTROL_CONTROLTYPE_MIXER ||
//				   m_dwControlType == MIXERCONTROL_CONTROLTYPE_MUX);

			// MUX restricts the line selection to one source line at a time.
			if (lVal != 0 && m_dwControlType == MIXERCONTROL_CONTROLTYPE_MUX)
			{
				::ZeroMemory(pmxcdSelectValue,
							 m_dwMultipleItems * sizeof(MIXERCONTROLDETAILS_BOOLEAN));
			}

			// set the Microphone value
			pmxcdSelectValue[m_dwIndex].fValue = lVal;

			mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
			mxcd.dwControlID = m_dwSelectControlID;
			mxcd.cChannels = 1;
			mxcd.cMultipleItems = m_dwMultipleItems;
			mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
			mxcd.paDetails = pmxcdSelectValue;
			if (::mixerSetControlDetails(reinterpret_cast<HMIXEROBJ>(m_hMixer),
										 &mxcd,
										 MIXER_OBJECTF_HMIXER |
										 MIXER_SETCONTROLDETAILSF_VALUE)
				== MMSYSERR_NOERROR)
			{
				bRetVal = TRUE;
			}
		}

		delete []pmxcdSelectValue;
	}

	return bRetVal;
}

/**
 * Select Control ¬O§_¦s¦b
 *
 *
 */
bool CMicrophoneVolumn::isSelectControl(){
	if (m_hMixer == NULL)
	{
		return false;
	}

	// get dwLineID
	MIXERLINE mxl;
	mxl.cbStruct = sizeof(MIXERLINE);
	mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_WAVEIN;
	if (::mixerGetLineInfo(reinterpret_cast<HMIXEROBJ>(m_hMixer),
						   &mxl,
						   MIXER_OBJECTF_HMIXER |
						   MIXER_GETLINEINFOF_COMPONENTTYPE)
		!= MMSYSERR_NOERROR)
	{
		return false;
	}

	// get dwControlID
	MIXERCONTROL mxc;
	MIXERLINECONTROLS mxlc;
	m_dwControlType = MIXERCONTROL_CONTROLTYPE_MIXER;
	mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
	mxlc.dwLineID = mxl.dwLineID;
	mxlc.dwControlType = m_dwControlType;
	mxlc.cControls = 1;
	mxlc.cbmxctrl = sizeof(MIXERCONTROL);
	mxlc.pamxctrl = &mxc;
	if (::mixerGetLineControls(reinterpret_cast<HMIXEROBJ>(m_hMixer),
							   &mxlc,
							   MIXER_OBJECTF_HMIXER |
							   MIXER_GETLINECONTROLSF_ONEBYTYPE)
		!= MMSYSERR_NOERROR)
	{
		// no mixer, try MUX
		m_dwControlType = MIXERCONTROL_CONTROLTYPE_MUX;
		mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
		mxlc.dwLineID = mxl.dwLineID;
		mxlc.dwControlType = m_dwControlType;
		mxlc.cControls = 1;
		mxlc.cbmxctrl = sizeof(MIXERCONTROL);
		mxlc.pamxctrl = &mxc;
		if (::mixerGetLineControls(reinterpret_cast<HMIXEROBJ>(m_hMixer),
								   &mxlc,
								   MIXER_OBJECTF_HMIXER |
								   MIXER_GETLINECONTROLSF_ONEBYTYPE)
			!= MMSYSERR_NOERROR)
		{
			return false;
		}
	}

	// store dwControlID, cMultipleItems
//	m_strDstLineName = mxl.szName;
//	m_strSelectControlName = mxc.szName;
	m_dwSelectControlID = mxc.dwControlID;
	m_dwMultipleItems = mxc.cMultipleItems;

	if (m_dwMultipleItems == 0)
	{
		return false;
	}

	// get the index of the Microphone Select control
	MIXERCONTROLDETAILS_LISTTEXT *pmxcdSelectText =
		new MIXERCONTROLDETAILS_LISTTEXT[m_dwMultipleItems];

	if (pmxcdSelectText != NULL)
	{
		MIXERCONTROLDETAILS mxcd;
		mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
		mxcd.dwControlID = m_dwSelectControlID;
		mxcd.cChannels = 1;
		mxcd.cMultipleItems = m_dwMultipleItems;
		mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_LISTTEXT);
		mxcd.paDetails = pmxcdSelectText;
		DWORD dwi;
		if (::mixerGetControlDetails(reinterpret_cast<HMIXEROBJ>(m_hMixer),
									 &mxcd,
									 MIXER_OBJECTF_HMIXER |
									 MIXER_GETCONTROLDETAILSF_LISTTEXT)
			== MMSYSERR_NOERROR)
		{
			// determie which controls the Microphone source line
			for (dwi = 0; dwi < m_dwMultipleItems; dwi++)
			{
				// get the line information
				MIXERLINE mxl;
				mxl.cbStruct = sizeof(MIXERLINE);
				mxl.dwLineID = pmxcdSelectText[dwi].dwParam1;
				if (::mixerGetLineInfo(reinterpret_cast<HMIXEROBJ>(m_hMixer),
									   &mxl,
									   MIXER_OBJECTF_HMIXER |
									   MIXER_GETLINEINFOF_LINEID)
					== MMSYSERR_NOERROR &&
					mxl.dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_ANALOG/*MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE*/ &&
					::lstrcmp(mxl.szName, _TEXT("Auxiliary")) != 0
					)
				{

					// found, dwi is the index.
					m_dwIndex = dwi;
//					m_strMicName = pmxcdSelectText[dwi].szName;
					//break;
				}else{
					std::cout << mxl.dwComponentType << std::endl;
				}
			}

			if (dwi >= m_dwMultipleItems)
			{
				// could not find it using line IDs, some mixer drivers have
				// different meaning for MIXERCONTROLDETAILS_LISTTEXT.dwParam1.
				// let's try comparing the item names.
				for (dwi = 0; dwi < m_dwMultipleItems; dwi++)
				{
					if (::lstrcmp(pmxcdSelectText[dwi].szName,
								  _T("Microphone")) == 0)
					{
						// found, dwi is the index.
						m_dwIndex = dwi;
//						m_strMicName = pmxcdSelectText[dwi].szName;
						break;
					}
				}
			}
		}

		delete []pmxcdSelectText;
	}

	return m_dwIndex < m_dwMultipleItems;
}