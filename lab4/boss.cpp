#include <iostream>
#include <windows.h>
using namespace std;

HANDLE hInEvent;
CHAR lpEventName[] = "InEventName";

int main()
{
	hInEvent = CreateEvent(NULL, FALSE, FALSE, lpEventName);

	setlocale(LC_ALL, "rus");
	int numParent, numChild;
	cout << "¬ведите количество процессов Parent: ";
	cin >> numParent;
	cout << "¬ведите количество процессов Child: ";
	cin >> numChild;

	int numMessParent, numMessChild;
	cout << "¬ведите количество сообщений, отправленых Parent: ";
	cin >> numMessParent;
	cout << "¬ведите количество  сообщений, отправленых Child: ";
	cin >> numMessChild;

	STARTUPINFO si;
	PROCESS_INFORMATION *piParent = new PROCESS_INFORMATION[numParent];
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	HANDLE* hParent = new HANDLE[numParent];
	char parentCommandLine[] = "Parent.exe";
	for (int i = 0; i < numParent; i++)
	{
		CreateProcess(NULL, parentCommandLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piParent[i]);
	}

	for (int i = 0; i < numParent; i++)
	{
		hParent[i] = piParent[i].hProcess;
	}
	SetEvent(hInEvent);


	HANDLE* hChild = new HANDLE[numChild];
	char childCommandLine[] = "Child.exe";
	PROCESS_INFORMATION *piChild = new PROCESS_INFORMATION[numChild];
	for (int i = 0; i < numParent; i++)
	{
		CreateProcess(NULL, childCommandLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piChild[i]);
	}
	for (int i = 0; i < numParent; i++)
	{
		hChild[i] = piChild[i].hProcess;
	}

	WaitForMultipleObjects(numChild, hChild, TRUE, INFINITE);

	for (int i = 0; i < numParent; i++)
	{
		CloseHandle(piParent[i].hProcess);
		CloseHandle(piChild[i].hProcess);
	}

	return 0;
}