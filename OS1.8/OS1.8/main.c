#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

int _tmain(int argc, TCHAR* argv[]) {
	//vytvoreni handlu, ktery vytvori nebo otevre soubor
	HANDLE hFileZapis = CreateFile( 
		_T("soubor.txt"),						//cesta k souboru
		GENERIC_READ | GENERIC_WRITE,					//rezim prace se souborem
		FILE_SHARE_READ,						//rezim sdileneho pristupu k soubor (jen pro cteni)
		NULL,								//bezpecnostni atributy
		OPEN_ALWAYS,							//jak nalozit s (ne)existujicimi soubory
		0,								//priznaky souboru
		NULL);								//odkaz na sablonu

	if (hFileZapis == INVALID_HANDLE_VALUE) {				//protoze handle nevraci v pripade chyby null
		printf("error opening file\n");					//ale INVALID_HANDLE_VALUE	
	}

	_TCHAR* str = _T("cau svete!");

	if (WriteFile(hFileZapis, str, sizeof(_TCHAR) * _tcslen(str), NULL, NULL)) {
		_tprintf(_T("soubor byl v poradku otevren a probehl zapis :)\n"));
	}
	//zavreni handlu
	CloseHandle(hFileZapis);
	
	//------------------------------------------------------------------------------------------------
	//funkce pro precteni souboru
	//krok 1.
	HANDLE hFileCteni = CreateFile(
		_T("soubor.txt"),						//cesta k souboru		
		GENERIC_READ,							//access mode
		FILE_SHARE_READ,						//rezim sdileneho pristupu k souboru
		NULL,								//bezpecnostni atributy
		OPEN_EXISTING,							//otevreni, pokud soubor existuje
		0,										
		NULL);

	if (hFileCteni == INVALID_HANDLE_VALUE) {
		_tprintf(_T("chyba"));
		return 0;
	}

	char buffer[256];							//vytvoreni bufferu, kam se budou znaky ukladat
	DWORD dwBytesToRead = 256 - 1;				
	DWORD dwBytesRead = 0;

	BOOL precteniFile = ReadFile(
		hFileCteni,							//file handle
		buffer,								//buffer s prectenym textem
		dwBytesToRead,							//buffer size-1
		&dwBytesRead,							//pocet prectenych bajtu
		NULL);

	if (dwBytesRead > 0) {
		printf("%s", buffer);						//vypis bufferu
	}

	CloseHandle(hFileCteni);						//zavreni handlu
	return 0;
}
