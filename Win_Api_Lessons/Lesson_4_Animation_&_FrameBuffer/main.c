#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define _WIN32_WINNT 0x0A00
#include <windows.h>

#define WSize 800
#define HSize 600
#define sizeSquare 150

#define mapSize 50
RECT map[mapSize];


void initMap(void) {
    srand(time(NULL));

    for(int i = 0; i < mapSize; i++) {
        map[i].left = rand() % (WSize - sizeSquare); // x start
        map[i].top = rand() % (HSize - sizeSquare); // y start
        map[i].right = map[i].left + sizeSquare;
        map[i].bottom = map[i].top + sizeSquare;
    }
}

void winMove(void) {
    const int dx = 3;

    for(int i = 0; i < mapSize; i++) {
        map[i].left += dx;
        if(map[i].left >= WSize) map[i].left = -sizeSquare;
        map[i].right = map[i].left + sizeSquare;
    }
}

void printMap(void) {
    for(int i = 0; i < mapSize; i++)
        printf("x1=%d, y1=%d, x2=%d, y2=%d\n", map[i].left, map[i].top, map[i].right, map[i].bottom);
}

void showSquaresInWindow(HDC hdc) {
    // ����������� �������� ��� ��������� � ������
    HDC memDc = CreateCompatibleDC(hdc);
    // ������� �������� �� ������� ����� �������� ����� ����������� ��������
    HBITMAP memBm = CreateCompatibleBitmap(hdc, WSize, HSize);

    // �������� ���� �������� � �������� ��������� ��� ���������
    SelectObject(memDc, memBm);

    // ����������� ���
    SelectObject(memDc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(memDc, RGB(255, 255, 255));
    Rectangle(memDc, 0, 0, WSize, HSize);

    // ����� ��� ���������
    SelectObject(memDc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(memDc, RGB(10, 255, 10));
    SelectObject(memDc, GetStockObject(DC_PEN));
    SetDCPenColor(memDc, RGB(10, 10, 255));

    // ������ ��������
    for(int i = 0; i < mapSize; i++)
        Rectangle(memDc, map[i].left, map[i].top, map[i].right, map[i].bottom);

    // �������� ����������� �� ����� ����������� ������ � ���� ����
    // �.�. �� ��������� memDc --to--> hdc

    // ������� ������ �� �������� hdc
    //                        |        |                             |����� ����������� ���
    BitBlt(hdc, 0, 0, WSize, HSize, memDc, 0, 0, SRCCOPY);
    //             ^^                                    ^^
    // ����� ������ �������. �� ��������� hdc
    //
    // ����� ����������� �������. �� ��������� memDc

    // ������� ���������� ������
    DeleteDC(memDc);
    DeleteObject(memBm);
}



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
                             0, 0, // ���������� �������� ������ ���� ��� ��� ��������
                             WSize, HSize, // ������� ����
                             NULL, NULL, NULL, NULL
                             );

    // ������� �������� ����������, ����� �������� � ���
    HDC hdc = GetDC(hwnd);

    // ���������� ����, SW_SHOWNORMAL - ��� ������ ������ ����
    ShowWindow(hwnd, SW_SHOWNORMAL);

    initMap();
    printMap();

    MSG msg;
    while(1) {
        // ��������� ������� ��������� � �������, ���� ��� ���� - ���������� � MSG
        // ����� ���������� false
        // PM_REMOVE - ����� ��������� ��������� ��� ����� �������
        if(PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {

            if(msg.message == WM_QUIT) break;

            // ���� �������� ��������� ������� �������, ����������� ��� ��������� � ������
            // � ���������� ����� ���������
            TranslateMessage(&msg);
            // �������� ���������� ��������� ������ ����
            DispatchMessage(&msg);
        }
        else {
            winMove();
            showSquaresInWindow(hdc);
            Sleep(10);
        }
    }


    /*
        ����� ��������� ���������� ���� ������� Project/properties/build target/type
        ������ console application to GUI
        ���� ������ "rebuild"
    */

    printf("Hello world!\n");
    return 0;
}
