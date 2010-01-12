#ifdef __DLL__
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

extern "C"
{
void DLL_EXPORT SetData(int x);
int DLL_EXPORT GetData(void);
}
 