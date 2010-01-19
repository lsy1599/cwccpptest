#include <windows.h>
#include <mmsystem.h>
#pragma once

class CMicrophoneVolumn{
public:
	CMicrophoneVolumn(DWORD dwInstance);
	~CMicrophoneVolumn(void);

public:
	bool getSelect();
	bool setSelect(bool enable)const;

	bool isSelectControl();

private:
	UINT		m_nNumMixers;
	HMIXER		m_hMixer;
	MIXERCAPS	m_mxcaps;
	DWORD m_dwControlType, m_dwSelectControlID, m_dwMultipleItems, m_dwIndex;
};
