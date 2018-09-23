using namespace std;

DWORD FindModule(const DWORD ProcessId, const char *szModuleName);
int RPM_int(HANDLE handle,LPCVOID adress, int buf);
float RPM_float(HANDLE handle, LPCVOID adress, float buf);
char * RPM_char(HANDLE handle, DWORD adress);

//Функция поиска модуля в процессе
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
// Рпм для целого более компактный 
int RPM_int(HANDLE handle, DWORD adress)
{
	int result;
	ReadProcessMemory(handle, (LPCVOID)adress, &result, sizeof(result), 0);
	return result;
}
// Рпм для флота более компактный
float RPM_float(HANDLE handle, DWORD adress)
{
	float result;
	ReadProcessMemory(handle, (LPCVOID)adress, &result, sizeof(result), 0);
	return result;
}
// Рпм для символов (не работает, фикси передачу массива)
char * RPM_char(HANDLE handle, DWORD adress)
{
	char result[128];
	ReadProcessMemory(handle, (LPCVOID)adress, &result, sizeof(result), 0);
	return result;
}