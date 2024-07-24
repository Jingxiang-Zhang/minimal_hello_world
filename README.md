# Minimal Hello World Program Without C Runtime Library (CRT)



### Description

This program creates a minimal "Hello World" application using basic `printf` and `scanf` functions, without relying on the C runtime library (CRT). The goal is to maintain a minimal executable file size. 



### C Runtime Library Overview

The CRT provides essential services such as:

- Security checks
- Command-line parameter parsing
- Global/static variable initialization
- Heap memory management
- Standard I/O functions



### Without CRT Initialization

- No security checks like buffer overflows
- No automatic command-line parameter parsing
- No global/static variable initialization
- No heap memory management
- No automatic call to `main`



### How to Avoid Using CRT

1. **User-Defined Entry Point**: Define `WinMainCRTStartup` as entry point.
2. **Ignore Default Libraries**: Configure the linker to ignore CRT libraries.
3. **Disable Security Checks**: Use the `/GS-` option.



### Visual Studio Configuration

Only work for release mode:

1. Set custom entry point:
   - Project -> Properties -> Linker -> Advanced -> Entry Point: `WinMainCRTStartup`.
2. Disable CRT initialization:
   - Project -> Properties -> C/C++ -> Code Generation -> Runtime Library: `Multi-threaded (/MT)` or `Multi-threaded DLL (/MD)`.
   - Project -> Properties -> Linker -> Input -> Ignore All Default Libraries: `Yes`.
3. Disable security checks:
   - Project -> Properties -> C/C++ -> Code Generation -> Security Check (/GS): `Disabled (/GS-)`.
4. Set subsystem:
   - Project -> Properties -> Linker -> System -> Subsystem: `Windows (/SUBSYSTEM:WINDOWS)`.

### File Size Reduction

- **/MD (Multi-threaded DLL)**: Links against the CRT dynamically, reducing the file size but requiring the CRT DLL (For example, Microsoft Visual C++ 2010 x64 Redistributable) at runtime. File size decreases from 10 KB to 4 KB.
- **/MT (Multi-threaded)**: Statically links the CRT into the executable, increasing the file size but not requiring external DLLs. File size decreases from 76 KB to 4 KB.



### Custom printf and scanf

`printf` and `scanf` are part of the C standard library, but their implementations vary by system. This program includes a custom `printf` function using Windows API functions to handle formatted output.



This program is for educational purposes, demonstrating how to create a minimal executable by avoiding the CRT.
