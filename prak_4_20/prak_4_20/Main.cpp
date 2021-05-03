#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>


#define ID_TIMER_1 1


static TCHAR szMainWindowClass[] = _T("MainWindowClass");
static TCHAR szChildWindowClass[] = _T("ChildWindowClass");

static TCHAR szMainWindowTitle[] = _T("MainWindow");
static TCHAR szChildTitle[] = _T("Child Window");

HINSTANCE hInst;

UINT uFirstDeltaTime = 1500;

BOOL bMouseFlag = false;

HWND hWndChild;
HDC hdc;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcChild(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szMainWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindow(
        szMainWindowClass,
        szMainWindowTitle,
        WS_OVERLAPPEDWINDOW,
        0, 0,
        600, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

   
    if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) {
        CreateWindow(TEXT("STATIC"), TEXT("Caps on"),
            WS_VISIBLE | WS_CHILD,
            0, 0, 100, 20,
            hWnd, (HMENU)NULL, NULL, NULL);
    }
    else {
        CreateWindow(TEXT("STATIC"), TEXT("Caps off"),
            WS_VISIBLE | WS_CHILD,
            0, 0, 100, 20,
            hWnd, (HMENU)NULL, NULL, NULL);
    }

   

    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    SetTimer(hWnd, ID_TIMER_1, uFirstDeltaTime, NULL);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_TIMER:
        switch (wParam) {
        case ID_TIMER_1: {

            KillTimer(hWnd, ID_TIMER_1);

            WNDCLASSEX wcexFirstChild;

            wcexFirstChild.cbSize = sizeof(WNDCLASSEX);
            wcexFirstChild.style = CS_HREDRAW | CS_VREDRAW;
            wcexFirstChild.lpfnWndProc = WndProcChild;
            wcexFirstChild.cbClsExtra = 0;
            wcexFirstChild.cbWndExtra = 0;
            wcexFirstChild.hInstance = hInst;
            wcexFirstChild.hIcon = LoadIcon(hInst, IDI_APPLICATION);
            wcexFirstChild.hCursor = LoadCursor(NULL, IDC_ARROW);
            wcexFirstChild.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcexFirstChild.lpszMenuName = NULL;
            wcexFirstChild.lpszClassName = szChildWindowClass;
            wcexFirstChild.hIconSm = LoadIcon(wcexFirstChild.hInstance, IDI_APPLICATION);

            if (!RegisterClassEx(&wcexFirstChild))
            {
                MessageBox(NULL,
                    _T("Call to RegisterClassEx failed! (wcexFirstChild)"),
                    _T("Windows Desktop Guided Tour"),
                    NULL);

                return 1;
            }


            hWndChild = CreateWindow(
                szChildWindowClass,
                szChildTitle,
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                200, 200,
                200, 200,
                hWnd,
                NULL,
                hInst,
                NULL
            );

            if (!hWndChild)
            {
                MessageBox(NULL,
                    _T("Call to CreateWindow failed! (hWndFirstChild)"),
                    _T("Windows Desktop Guided Tour"),
                    NULL);

                return 1;
            }

            if ((GetKeyState(VK_NUMLOCK) & 0x0001) != 0) {
                CreateWindow(TEXT("STATIC"), TEXT("Numlock on"),
                    WS_VISIBLE | WS_CHILD,
                    0, 0, 100, 20,
                    hWndChild, (HMENU)NULL, NULL, NULL);
            }
            else {
                CreateWindow(TEXT("STATIC"), TEXT("Numlock off"),
                    WS_VISIBLE | WS_CHILD,
                    0, 0, 100, 20,
                    hWndChild, (HMENU)NULL, NULL, NULL);
            }

            break;
        }
        default:
            break;
        }
        break;

    case WM_KEYDOWN:

        switch (wParam) {

        case VK_CAPITAL:
            
            if (!bMouseFlag) {
                if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) {
                    CreateWindow(TEXT("STATIC"), TEXT("Caps on"),
                        WS_VISIBLE | WS_CHILD,
                        0, 0, 100, 20,
                        hWnd, (HMENU)NULL, NULL, NULL);
                }
                else {
                    CreateWindow(TEXT("STATIC"), TEXT("Caps off"),
                        WS_VISIBLE | WS_CHILD,
                        0, 0, 100, 20,
                        hWnd, (HMENU)NULL, NULL, NULL);
                }
            }
            break;
        case VK_NUMLOCK:
            if (bMouseFlag) {
                if ((GetKeyState(VK_NUMLOCK) & 0x0001) != 0) {
                    CreateWindow(TEXT("STATIC"), TEXT("Numlock on"),
                        WS_VISIBLE | WS_CHILD,
                        0, 0, 100, 20,
                        hWnd, (HMENU)NULL, NULL, NULL);
                }
                else {
                    CreateWindow(TEXT("STATIC"), TEXT("Numlock off"),
                        WS_VISIBLE | WS_CHILD,
                        0, 0, 100, 20,
                        hWnd, (HMENU)NULL, NULL, NULL);
                }
            }
            break;

        default:
            break;
        }

        break;

    case WM_RBUTTONDOWN:
        if (bMouseFlag) {
            bMouseFlag = false;
        } else {
            bMouseFlag = true;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}




LRESULT CALLBACK WndProcChild(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:

        switch (wParam) {

        case VK_NUMLOCK:
            if (!bMouseFlag) {
                if ((GetKeyState(VK_NUMLOCK) & 0x0001) != 0) {
                    CreateWindow(TEXT("STATIC"), TEXT("Numlock on"),
                        WS_VISIBLE | WS_CHILD,
                        0, 0, 100, 20,
                        hWnd, (HMENU)NULL, NULL, NULL);
                }
                else {
                    CreateWindow(TEXT("STATIC"), TEXT("Numlock off"),
                        WS_VISIBLE | WS_CHILD,
                        0, 0, 100, 20,
                        hWnd, (HMENU)NULL, NULL, NULL);
                }
            }
            break;
        case VK_CAPITAL:

            if (bMouseFlag) {
                if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) {
                    CreateWindow(TEXT("STATIC"), TEXT("Caps on"),
                        WS_VISIBLE | WS_CHILD,
                        0, 0, 100, 20,
                        hWnd, (HMENU)NULL, NULL, NULL);
                }
                else {
                    CreateWindow(TEXT("STATIC"), TEXT("Caps off"),
                        WS_VISIBLE | WS_CHILD,
                        0, 0, 100, 20,
                        hWnd, (HMENU)NULL, NULL, NULL);
                }
            }
            break;

        default:
            break;
        }

        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}