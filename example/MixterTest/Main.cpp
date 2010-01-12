//---------------------------------------------------------------------------
// ²V­µ¾¹¸Ë¸m
#include <iostream>
#include <windows.h>
#pragma hdrstop

#include "waveIN_simple.h"
//---------------------------------------------------------------------------
using namespace std;

#pragma argsused

struct DoMuteMyPlayBackLine{
	void operator()(CMixerLine* line){
		if (line->isWave() || line->isMicrophone() ){
			line->UnMute();
		}
	}
};
int main(int argc, char* argv[])
{
    CMixer*  mixer;
    CMixerLine* mixerline;

    mixer           = &CWaveINSimple::GetDevice().OpenMixer();
    mixerline       = &mixer->GetLine();
/*
    mixer->ForEachPlayBackLines( DoMuteMyPlayBackLine() );
    mixerline->UnMute();
    mixerline->SetVolume(100);
    mixerline->Select();
*/
    mixer->Close();
    CWaveINSimple::CleanUp();
    return 0;
}
//---------------------------------------------------------------------------
 