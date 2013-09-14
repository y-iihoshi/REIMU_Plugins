#include "IConfig.h"
#include "TCHAR.h"

IConfig::~IConfig()
{
}

bool IConfig::GetFilenames(
	HINSTANCE hInstance, LPTSTR appName, size_t appNameSize, LPTSTR iniPath, size_t iniPathSize)
{
	TCHAR appPath[_MAX_PATH + 1] = { TEXT('\0') };

	DWORD nAppPathLength = GetModuleFileName(hInstance, appPath, _MAX_PATH);
	if (nAppPathLength == 0)
		return false;

	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	errno_t retval;

	retval = _tsplitpath_s(appPath, drive, dir, fname, ext);
	if (retval == 0)
	{
		retval = _tmakepath_s(appName, appNameSize, NULL, NULL, fname, ext);
		if (retval == 0)
		{
			retval = _tmakepath_s(iniPath, iniPathSize, drive, dir, TEXT("threplay"), TEXT("ini"));
		}
	}
	return retval == 0;
}
