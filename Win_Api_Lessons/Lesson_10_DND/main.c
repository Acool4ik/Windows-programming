#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0A00
#include <windows.h>


void proccessDnD(HDROP hdr) {
    // ���������� ����
    POINT pt;
    DragQueryPoint(hdr, &pt);
    printf("Coordinates: [%d, %d]\n", pt.x, pt.y);


    char path[MAX_PATH];
    // DragQueryFile - ��������� ������ ����� ������ � �� ����������
    // 0xffffffff - ������� ���������� ������
    int cnt = DragQueryFile(hdr, 0xffffffff, NULL, 0);
    printf("cnt=%d\n", cnt);


    // ������ ���� �� �����
    for(int i = 0; i < cnt; i++) {
        DragQueryFile(hdr, i, path, MAX_PATH);
        printf("Name[%d]=%s\n", i, path);
    }

    DragFinish(hdr);
}

LRESULT castomHandler(HWND hwnd ,UINT message, WPARAM wparam, LPARAM lparam) {
    if(message == WM_DESTROY) {
        PostQuitMessage(0);
    }
    else if(message == WM_KEYDOWN) {
        printf("Code symbol: %d\n", wparam);
    }
    else if(message == WM_DROPFILES) {
        printf("Drop!\n");
        proccessDnD(wparam);
    }
    else if(message == WM_MOUSEMOVE) {
        int X = LOWORD(lparam);
        int Y = HIWORD(lparam);
    }

    else if(message == WM_LBUTTONDOWN) {
        printf("Left button mouse's have been pressed!\n");
    }

    else return DefWindowProcA(hwnd, message, wparam, lparam);
}

int main()
{
    WNDCLASSA wndclassa;
        memset(&wndclassa, 0, sizeof(WNDCLASSA));
        wndclassa.lpszClassName = "Window class A";
        wndclassa.lpfnWndProc = castomHandler;
    RegisterClassA(&wndclassa);

    HWND hwnd = CreateWindow(
                             wndclassa.lpszClassName, // ��� ������ ����, ������������������� �����
                             "Name of window's",        // ��������� ���� ��� ������������
                             WS_OVERLAPPEDWINDOW, // ����� ����
                             10, 10, // ���������� �������� ������ ���� ��� ��� ��������
                             640, 480, // ������� ����
                             NULL, NULL, NULL, NULL
                             );


    ShowWindow(hwnd, SW_SHOWNORMAL);

    // ��������� ���
    DragAcceptFiles(hwnd, TRUE);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


    return 0;
}
