#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0A00
#include <windows.h>

LRESULT castomHandler(HWND hwnd ,UINT message, WPARAM wparam, LPARAM lparam) {
    // ��������� ���������� � ���� ����������� ����
    if(message == WM_DESTROY) {
        // ��������� ������� ��������� � ������� ��������� � �������� ����
        PostQuitMessage(0);
        // ����� ������ ��������� "GetMessage" ������ false
    }
    // ��������� ���������� � ���� ������� ������ �� ����������
    else if(message == WM_KEYDOWN) {
        printf("Code symbol: %d\n", wparam);
    }
    // ����� ��������� ������
    else if(message == WM_CHAR) {
        printf("Symbol: %c\n", wparam);
    }
    // ��������� �� ��������� ��������� ���� ������ ����
    else if(message == WM_MOUSEMOVE) {
        int X = LOWORD(lparam);
        int Y = HIWORD(lparam);
        printf("[%d, %d]\n", X, Y);
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

    // ������� ���� � ���������� ��� ����������
    HWND hwnd = CreateWindow(
                             wndclassa.lpszClassName, // ��� ������ ����, ������������������� �����
                             "Name of window's",        // ��������� ���� ��� ������������
                             WS_OVERLAPPEDWINDOW, // ����� ����
                             10, 10, // ���������� �������� ������ ���� ��� ��� ��������
                             640, 480, // ������� ����
                             NULL, NULL, NULL, NULL
                             );

    // ���������� ����, SW_SHOWNORMAL - ��� ������ ������ ����
    ShowWindow(hwnd, SW_SHOWNORMAL);

    MSG msg;
    // GetMessage - ��������� ��������� �� ������� ��������� � ��������� � "msg"
    // ���� ��������� ���, �� ������� ����� �������, �.�. ���� ����� ����� �����������, ����� ����� �������� ���������
    // ���� ���� �������� ��������� � �������� ���������� - return false;
    while(GetMessage(&msg, NULL, 0, 0)) {
        // ���� �������� ��������� ������� �������, ����������� ��� ��������� � ������
        // � ���������� ����� ���������
        TranslateMessage(&msg);
        // �������� ���������� ��������� ������ ����
        DispatchMessage(&msg);
    }


    /*
        ����� ��������� ���������� ���� ������� Project/properties/build target/type
        ������ console application to GUI
        ���� ������ "rebuild"
    */

    printf("Hello world!\n");
    return 0;
}
