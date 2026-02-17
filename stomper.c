#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hFile = CreateFileA(
        "C:\\Users\\Attacker\\Downloads\\test.exe",
        FILE_WRITE_ATTRIBUTES,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Error opening file: %d\n", GetLastError());
        return 1;
    }

    SYSTEMTIME st = {0};
    st.wYear = 2022;
    st.wMonth = 3;
    st.wDay = 6;
    st.wHour = 12;
    st.wMinute = 0;
    st.wSecond = 0;

    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);
    SetFileTime(hFile, &ft, &ft, &ft);

    CloseHandle(hFile);
    printf("Timestamps updated successfully!\n");
    return 0;
}
