#include <iostream>
#include <windows.h>
using namespace std;

HANDLE hInEvent;
CHAR lpEventName[] = "InEventName";

int main()
{
	HANDLE hSemaphore;
	hSemaphore = CreateSemaphore(NULL, 0, 2, NULL);
	if (hSemaphore == NULL)
		return GetLastError();

	if (ReleaseSemaphore(hSemaphore, 1, NULL))
	{
		hInEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, lpEventName);

		WaitForSingleObject(hInEvent, INFINITE);

	}
	else
		WaitForSingleObject(hSemaphore, INFINITY);

	return 0;
}