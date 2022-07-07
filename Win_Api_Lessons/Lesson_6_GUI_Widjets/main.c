#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0A00
#include <windows.h>

#define IDBtn1 1
#define IDBtn2 2
#define IDInput 3
#define IDText 4
#define IDCombo 5

HWND button_quite;
HWND button_noop;
HWND input;
HWND text;
HWND combo;

int SELECTED_ITEM = 0;


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


    // ��� WM_COMMAND ��������� � ����������� wparam ������������ ����� 2 ��������
    else if(message == WM_COMMAND) {
        if(lparam == button_quite)
            PostQuitMessage(0);
        if(LOWORD(wparam) == IDBtn2)
            printf("Click noop!\n");


        // LOWORD - ������ ��������� ������ 2 ����� -> ������������� �������
        // wparam - 4-x �������� �����
        if(LOWORD(wparam) == IDInput) {
            printf("Input: printing...\n");

            char buffer[256];
            // �������� ����� �� ��������� ������� � ������
            GetWindowText(lparam, buffer, 256);

            // HIWORD - ������ ��������� ��������� 2 ����� -> ��� �����������
            int code =  HIWORD(wparam);

            if(code == EN_UPDATE) {
                SetWindowText(text, buffer);
                printf("Update code: %s\n", buffer);
            }
            if(code == EN_CHANGE) {
                printf("Change code: %s\n", buffer);
            }
        }


        if(LOWORD(wparam) == IDCombo) {
            // CBN_SELCHANGE - ����������� � ������ ������ �������� �� ����������
            if(HIWORD(wparam) == CBN_SELCHANGE) {
                // CB_GETCURSEL - ��������� �������� ������� ��������� �������
                SELECTED_ITEM = SendMessage(lparam, CB_GETCURSEL, 0, 0);

                printf("SELECTED_ITEM=%d\n", SELECTED_ITEM);
            }
        }
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
                             wndclassa.lpszClassName,
                             "Name of window's",
                             WS_OVERLAPPEDWINDOW,
                             10, 10,
                             640, 480,
                             NULL, NULL, NULL, NULL
                             );

    ShowWindow(hwnd, SW_SHOWNORMAL);


    button_quite = CreateWindow("button", "quite",
                 WS_CHILD | WS_VISIBLE, 0, 0, 200, 100, hwnd, IDBtn1, NULL, NULL);

    button_noop = CreateWindow("button", "noop",
                 WS_CHILD | WS_VISIBLE, 200, 0, 200, 100, hwnd, IDBtn2, NULL, NULL);

    input = CreateWindow("Edit", "0",
                 WS_CHILD | WS_VISIBLE | ES_RIGHT | WS_BORDER, 0, 100, 200, 20, hwnd, IDInput, NULL, NULL);

    text = CreateWindow("Static", "start text noop",
                 WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT , 200, 100, 200, 20, hwnd, IDText, NULL, NULL);

    combo = CreateWindow("COMBOBOX", "",
                 WS_CHILD | WS_VISIBLE, 0, 120, 200, 480 - 120, hwnd, IDCombo, NULL, NULL);


    // SendMessage - ��������� ��������� � ��������� ���� ��� ���������� �������
    // CB_ADDSTRING - ��� ���������
    SendMessage(combo, CB_ADDSTRING, 0, "<undefined>");
    SendMessage(combo, CB_ADDSTRING, 0, "<undefined 2>");
    SendMessage(combo, CB_ADDSTRING, 0, "<undefined 3>");
    SendMessage(combo, CB_ADDSTRING, 0, "<undefined 4>");
    // CB_SETCURSEL, 0 - ������� ���������� ������� � ���������� ���
    SendMessage(combo, CB_SETCURSEL, 0, 0);

    MSG msg;
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
    return 0;
}
