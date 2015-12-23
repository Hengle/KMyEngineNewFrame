#include "MyTestInterfaces.h"
#include "ApplicationClass.h"

__declspec(dllexport) ITestApp* fnCreateITerrainInterface(void)
{
	CApplicationClass* piTestApp = new CApplicationClass();
	return piTestApp;
}
__declspec(dllexport) void fnReleaseITerrainInterface(ITestApp *piInterface)
{
	CApplicationClass* piTestApp = dynamic_cast<CApplicationClass *>(piInterface);

	piTestApp->Shutdown();
	delete piTestApp;
}