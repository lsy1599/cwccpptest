//---------------------------------------------------------------------------
#ifndef HookProcH
#define HookProcH
//---------------------------------------------------------------------------
#define KBDEXP __declspec(dllexport) __stdcall

extern "C" {
  KBDEXP bool InstallHook();
  KBDEXP bool RemoveHook();
};

#endif
