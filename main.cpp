#include <Windows.h>
#include <iostream>

void WriteBytes(PVOID address, void* val, int bytes)
{
	memcpy(address, val, bytes);
}

int main()
{
	static int Time = 0;
	printf("[+] CreateMapping");
	HANDLE hFileMap = CreateFileMappingA(NULL, NULL, PAGE_READWRITE, NULL, 32768, "CSO.SharedDict");
	HANDLE pFileMap = MapViewOfFile(hFileMap, SECTION_MAP_EXECUTE | FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pFileMap)
	{
		printf("[+] Fill FileMapping\n");
		WriteBytes((LPVOID)pFileMap, (BYTE*)"\x00\x00\x00\x00\x05\x00\x00\x00\x08\x00\x00\x00\x6C\x61\x75\x6E\x63\x68\x65\x64\x01\x00\x00\x00\x31\x04\x00\x00\x00\x6D\x6F\x64\x65\x00\x00\x00\x00\x08\x00\x00\x00\x70\x61\x73\x73\x70\x6F\x72\x74\x00\x00\x00\x00\x06\x00\x00\x00\x72\x65\x67\x69\x6F\x6E\x01\x00\x00\x00\x35\x04\x00\x00\x00\x74\x79\x70\x65\x01\x00\x00\x00\x30\x30", 82);
		printf("[+] Create GameProcess\n");
		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;
		CreateProcess("cstrike-online.exe",
			"", // CommandLine -noforcemparms -noforcemaccel -noforcemspd etc.
			NULL,
			NULL,
			FALSE,
			CREATE_NEW_CONSOLE,
			NULL,
			NULL,
			&si,
			&pi);
		if (pi.hThread)
		{
			while (Time <= 10)
			{

				Time++;
				Sleep(1000);
			}
			printf("[+] I'll closed. Have a good game!\n");
			Sleep(5000);
			ExitProcess(0xDEAD);
		}
		else
		{
			printf("[-] Cannot Open GameProcess\n");
			return 0;
		}
	}
	else
	{
		printf("[-] Cannot Open File\n");
		return 0;
	}

	return 0;
}