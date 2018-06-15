#include "PCH.h"
#include "timer.h"

extern HWND g_hWnd;

timer::timer* timer::timer::s_pInstance = NULL;
HANDLE handle;

void WINAPI TimerProc(LPVOID lpParameter,DWORD ,DWORD) {
	InvalidateRect(g_hWnd, NULL, FALSE);
}

void timer::timer::Create() {
	if (!s_pInstance) {
		s_pInstance = new timer;
		handle = CreateWaitableTimer(NULL,TRUE,NULL);
		if (handle== NULL)throw;
		LARGE_INTEGER interval;
		interval.QuadPart = -10 * 1000 * 1;
		if (!SetWaitableTimer(
			handle, &interval, (LONG)33, TimerProc, NULL, FALSE))throw;
	}
}

void timer::timer::Destroy() {
	if (s_pInstance != nullptr) {
		CloseHandle(handle);
		delete s_pInstance;
		s_pInstance = NULL;
	}
}