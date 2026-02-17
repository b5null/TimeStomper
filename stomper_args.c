#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Usage: %s <filepath> <YYYY-MM-DD> <HH:MM:SS>\n", argv[0]);
        return 1;
    }

    const char *filePath = argv[1];

    int year, month, day;
    int hour, minute, second;

    if (sscanf(argv[2], "%d-%d-%d", &year, &month, &day) != 3) {
        printf("Invalid date format. Use YYYY-MM-DD\n");
        return 1;
    }

    if (sscanf(argv[3], "%d:%d:%d", &hour, &minute, &second) != 3) {
        printf("Invalid time format. Use HH:MM:SS\n");
        return 1;
    }

    HANDLE hFile = CreateFileA(
        filePath,
        FILE_WRITE_ATTRIBUTES,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Error opening file: %lu\n", GetLastError());
        return 1;
    }

    SYSTEMTIME st = {0};
    st.wYear   = (WORD)year;
    st.wMonth  = (WORD)month;
    st.wDay    = (WORD)day;
    st.wHour   = (WORD)hour;
    st.wMinute = (WORD)minute;
    st.wSecond = (WORD)second;

    FILETIME ft;
    if (!SystemTimeToFileTime(&st, &ft)) {
        printf("Error converting time: %lu\n", GetLastError());
        CloseHandle(hFile);
        return 1;
    }

    if (!SetFileTime(hFile, &ft, &ft, &ft)) {
        printf("Error setting file time: %lu\n", GetLastError());
        CloseHandle(hFile);
        return 1;
    }

    CloseHandle(hFile);
    printf("Timestamps updated successfully!\n");

    return 0;
}
