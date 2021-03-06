#include "stdafx.h"
#include "MyFirstWin32.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_DESTROY) PostQuitMessage(0);
    else if (uMsg == WM_CLOSE) {
        if (IDCANCEL == MessageBox(hWnd, L"마지막으로 아르토리아 최고인거 인정하고 가자", L"어 인정", MB_OKCANCEL));
        PostQuitMessage(0);

        return 1;
    }
    else if (uMsg == WM_LBUTTONDOWN) {
        HDC h_dc =  GetDC(hWnd);
        auto x = LOWORD(lParam);
        auto y = HIWORD(lParam);
        HBRUSH h_red_brush = CreateSolidBrush(RGB(255, 0, 0));
        HBRUSH h_blue_brush = CreateSolidBrush(RGB(0, 0, 255));

        if (wParam & MK_CONTROL) {
            HGDIOBJ h_old_brush = SelectObject(h_dc, h_red_brush);
            Ellipse(h_dc, x - 10, y - 10, x + 10, y + 10);
        }
        else {
            HGDIOBJ h_old_brush = SelectObject(h_dc, h_blue_brush);
            Rectangle(h_dc, x - 10, y - 10, x + 10, y + 10);
            SelectObject(h_dc, h_old_brush);
        }
        
        DeleteObject(h_red_brush);
        DeleteObject(h_blue_brush);
        ReleaseDC(hWnd, h_dc);

    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc;

    wchar_t my_class_name[] = L"HelloWin32";
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = my_class_name;
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wc);

    HWND hWnd = CreateWindow(my_class_name, L"Artoria First",
        WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    ShowScrollBar(hWnd, 0, true);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

