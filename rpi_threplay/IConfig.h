#pragma once

#include <Windows.h>

class IConfig
{
public:
	virtual ~IConfig() = 0;

	virtual bool Load(HINSTANCE hInstance) = 0;
	virtual bool Save(HINSTANCE hInstance) = 0;

protected:
	template <size_t appNameSize, size_t iniPathSize>
	static bool GetFilenames(
		HINSTANCE hInstance, TCHAR (&appName)[appNameSize], TCHAR (&iniPath)[iniPathSize]);

private:
	static bool GetFilenames(
		HINSTANCE hInstance, LPTSTR appName, size_t appNameSize, LPTSTR iniPath, size_t iniPathSize);
};

template <size_t appNameSize, size_t iniPathSize>
bool IConfig::GetFilenames(HINSTANCE hInstance, TCHAR (&appName)[appNameSize], TCHAR (&iniPath)[iniPathSize])
{
	return GetFilenames(hInstance, appName, appNameSize, iniPath, iniPathSize);
}
