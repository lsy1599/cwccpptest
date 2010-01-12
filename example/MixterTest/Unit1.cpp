//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
// ²V­µ¾¹¸Ë¸m
#include "sync_simple.h"
#include "waveIN_simple.h"
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
struct DoMuteMyPlayBackLine{
	void operator()(CMixerLine* line){
		if (line->isWave() || line->isMicrophone() ){
			line->UnMute();
		}
	}
};

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    CMixer*  mixer;
    CMixerLine* mixerline;

    mixer           = &CWaveINSimple::GetDevice().OpenMixer();
    mixerline       = &mixer->GetLine();

    mixer->ForEachPlayBackLines( DoMuteMyPlayBackLine() );
    mixerline->UnMute();
    mixerline->SetVolume(100);
    mixerline->Select();

    mixer->Close();
    CWaveINSimple::CleanUp();
}
//---------------------------------------------------------------------------
