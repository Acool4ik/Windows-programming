#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0A00
#include <windows.h>

void testFromClipboard(char **str) {
    // IsClipboardFormatAvailable - ��������� �������� �� ������ �� ������� ������
    // �������� ����� ������
    // CF_TEXT - ������ 1 �������� �������� ANSI
    if(IsClipboardFormatAvailable(CF_TEXT)) {

        if(OpenClipboard(0)) {
            // ���������� ��������� �� ������ ��������� ���� � ������� ������
            char *buffer = GetClipboardData(CF_TEXT);
            int length = strlen(buffer) + 1;

            *str = malloc(length * sizeof(char));
            sprintf(*str, "%s", buffer);

            // ������ ������ ����� �������, �.�. ���� �� �� ������ �� ��� �� �����
            // ������������ � ������ �����������
            CloseClipboard();

            printf("Clipboard data: %s\n", *str);
        }
    }
}



int main()
{
    HWND hwnd = GetConsoleWindow();
    char *string = NULL;

    while(1) {
        if(GetForegroundWindow() != hwnd) continue;
        if(GetKeyState(VK_ESCAPE) < 0) break;
        if(GetKeyState(VK_LCONTROL) < 0) {
            if(GetKeyState('V') < 0) {
                testFromClipboard(&string);
            }
        }

        Sleep(5);
    }

    return 0;
}
