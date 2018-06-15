#include "PCH.h"
#include "main.h"
#include "direct2d.h"
#include "timer.h"
#include "debugFile.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
void draw();   //�`��֐�

HWND g_hWnd;   //�E�B���h�E��hwnd
TCHAR szClassName[] = TEXT("happy shooting 2");    // �E�B���h�E�N���X

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
	LPSTR lpsCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL bRet;

	if (!InitApp(hCurInst))
		return FALSE;
	if (!InitInstance(hCurInst, nCmdShow))
		return FALSE;
	try{
		debugFile::Create();
		timer::timer::Create();
	}catch(...) {
		return FALSE;
	}

	// ���b�Z�[�W���擾
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1) {
			break;
		}
		else {
			TranslateMessage(&msg);    // ���b�Z�[�W��ϊ�
			DispatchMessage(&msg);     // ���b�Z�[�W�𑗏o
		}
	}
	timer::timer::Destroy();
	debugFile::Destroy();
	return (int)msg.wParam;
}

// �E�B���h�E�N���X�̓o�^
ATOM InitApp(HINSTANCE hInst)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);           // �\���̂̃T�C�Y
	wc.style = CS_HREDRAW | CS_VREDRAW;       // �N���X�̃X�^�C��
	wc.lpfnWndProc = WndProc;                 // �v���V�[�W����
	wc.cbClsExtra = 0;                        // �⏕������
	wc.cbWndExtra = 0;                        // �⏕������
	wc.hInstance = hInst;                     // �C���X�^���X
	wc.hIcon = (HICON)LoadImage(              // �A�C�R��
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(          // �J�[�\��
		NULL, MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR, 0, 0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground =                        // �w�i�u���V
		(HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;                   // ���j���[��
	wc.lpszClassName = szClassName;           // �N���X��
	wc.hIconSm = (HICON)LoadImage(            // �������A�C�R��
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0,
		LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));
}

// �E�B���h�E�̐���
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	RECT rect;
	GetWindowRect(GetDesktopWindow(),&rect);
	g_hWnd = CreateWindow(szClassName, // �N���X��
		TEXT("Happy Shooting 2"),
		// �E�B���h�E��
		WS_OVERLAPPEDWINDOW,     // �E�B���h�E�X�^�C��
		(rect.right-WIDTH)/2,           // x�ʒu
		(rect.bottom-HEIGHT)/2,           // y�ʒu
		WIDTH,           // �E�B���h�E��
		HEIGHT,           // �E�B���h�E����
		NULL,  // �e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
		NULL,  // ���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
		hInst, // �C���X�^���X�n���h��
		NULL   // �E�B���h�E�쐬�f�[�^
	);
	if (!g_hWnd)
		return FALSE;
	ShowWindow(g_hWnd, nCmdShow);  // �E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(g_hWnd);          // �E�B���h�E���X�V
	return TRUE;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) {
	case WM_CREATE:
		debugFile::Create();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		draw();
		break;
	default:
		return (DefWindowProc(hWnd, msg, wp, lp));
	}
	return 0;
}

DWORD before = 0;

void draw() {
	DWORD now = timeGetTime();
	if (now - before < 33)return;
	debugFile().write(std::string(std::to_string(timeGetTime()-before)));
	before = timeGetTime();
}