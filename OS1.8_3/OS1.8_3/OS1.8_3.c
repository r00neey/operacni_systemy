#include <windows.h>
#include <tchar.h>
#include <stdio.h>

int _tmain(int argc, TCHAR* argv[]) {
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	//vytvori novy proces
	if (!CreateProcess(
		_T("C:\\WINDOWS\\system32\\notepad.exe"),
		//_T("C:\\WINDOWS\\system32\\calc.exe"),
		_T("C:\\WINDOWS\\system32\\notepad.exe foo.txt"),
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi)
		) {
			_tprintf(_T("CreateProcess failed (%d).\n"), GetLastError());
			return 1;
		}

	//ceka na ukonceni programu
	WaitForSingleObject(pi.hProcess, INFINITE);
	
	//ukol 4
	//funkce vraci navratovy kod ukonceneho procesu + jeho vypis
	DWORD exitCode;
	BOOL result = GetExitCodeProcess(pi.hProcess, &exitCode);
	if (result) {
		_tprintf(_T("Exit code: %lu\n"), exitCode); // Výpis exit code (0)
	}
	else {
		_tprintf(_T("GetExitCodeProcess failed (%d).\n"), GetLastError()); // Pokud volání selže, vypiš chybový kód
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 8220);
	TerminateProcess(hProcess, 0);


	//uzavre proces
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}