using namespace std;

DWORD FindModule(const DWORD ProcessId, const char *szModuleName);
int RPM_int(HANDLE handle,LPCVOID adress, int buf);
float RPM_float(HANDLE handle, LPCVOID adress, float buf);
char * RPM_char(HANDLE handle, DWORD adress);

//Find Module of proces func
DWORD FindModule(const DWORD ProcessId, const char *szModuleName)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessId);
	if (!hSnap)
	{
		return 0;
	}

	MODULEENTRY32 me32;
	me32.dwSize = sizeof(MODULEENTRY32);

	DWORD dwReturn = 0;

	if (Module32First(hSnap, &me32))
	{
		while (Module32Next(hSnap, &me32))
		{
			if (lstrcmpi(me32.szModule, (LPCSTR)szModuleName) == 0)
			{
				dwReturn = (DWORD)me32.modBaseAddr;
				break;
			}
		}
	}
	CloseHandle(hSnap);
	return dwReturn;
} 
// rpm int
int RPM_int(HANDLE handle, DWORD adress)
{
	int result;
	ReadProcessMemory(handle, (LPCVOID)adress, &result, sizeof(result), 0);
	return result;
}
// rpm float
float RPM_float(HANDLE handle, DWORD adress)
{
	float result;
	ReadProcessMemory(handle, (LPCVOID)adress, &result, sizeof(result), 0);
	return result;
}
// rpm char , ur fucked up it does not work correct 
char * RPM_char(HANDLE handle, DWORD adress)
{
	char result[128];
	ReadProcessMemory(handle, (LPCVOID)adress, &result, sizeof(result), 0);
	return result;
}
