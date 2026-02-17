# TimeStomper
A simple Windows utility written in C that modifies file timestamps using the native Windows API (CreateFile + SetFileTime).

This project demonstrates direct interaction with the WinAPI to modify:

- Creation Time
- Last Access Time
- Last Write Time
---
# Features
Uses direct WinAPI calls

Supports:
- Hardcoded file path version
- Command-line argument version
- Minimal dependencies
- Cross-compilable from Linux using MinGW
---
# Compilation
Compile from Linux using MinGW:

```
bash
x86_64-w64-mingw32-gcc timer.c -o timer.exe
```

Or compile natively on Windows using MSVC:

```
CMD
cl timer.c
```
---
# Usage
## Hardcoded Version
In the hardcoded version, the file path and timestamp are embedded directly in the source code.

To change the target file, edit this line:

```
HANDLE hFile = CreateFileA(
    "C:\\Users\\Attacker\\Downloads\\test.exe",
```

Replace the string with your desired path (escape backslashes properly):

```
"C:\\Path\\To\\Your\\File.exe"
```

Recompile after modifying the source.

## Argument Version
This version accepts:

stomper.exe <filepath> <YYYY-MM-DD> <HH:MM:SS>


Example:
```
timer.exe "C:\Temp\file.exe" 2022-03-06 12:00:00
```

If the file path contains spaces, wrap it in quotes.

Arguments
Argument	Description
<filepath>	Full path to the target file
<YYYY-MM-DD>	Date to set
<HH:MM:SS>	Time to set
---
# How It Works
The program:
- Opens the file with FILE_WRITE_ATTRIBUTES
- Builds a SYSTEMTIME structure
- Converts it to FILETIME
- Calls SetFileTime() to update:
  - Creation time
  - Access time
  - Modification time
  - WinAPI Functions Used
  - CreateFileA
  - SystemTimeToFileTime
  - SetFileTime
  - CloseHandle

No external libraries are used — only native Windows API calls.
---
## Important Notes
SystemTimeToFileTime() expects UTC time.
The program requires permission to modify file attributes.
The file must already exist.
---
# ⚠️ Disclaimer

For educational and authorized testing only. Use only with explicit permission. The authors assume no liability for misuse.
---
# Author

 💀 B5null

