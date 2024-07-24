#include <windows.h>

void my_printf(const char* format, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    wvsprintfA(buffer, format, args);
    va_end(args);

    DWORD written;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteFile(hStdOut, buffer, lstrlenA(buffer), &written, NULL);
}

void my_scanf(const char* format, ...) {
    char buffer[1024];
    DWORD read;
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    ReadFile(hStdIn, buffer, sizeof(buffer) - 1, &read, NULL);
    buffer[read] = '\0';  // Null-terminate the input

    va_list args;
    va_start(args, format);

    const char* p = format;
    char* b = buffer;
    while (*p) {
        if (*p == '%' && *(p + 1) != '\0') {
            p++;
            if (*p == 'd') {
                int* ip = va_arg(args, int*);
                *ip = 0;
                while (*b >= '0' && *b <= '9') {
                    *ip = (*ip * 10) + (*b - '0');
                    b++;
                }
            }
            else if (*p == 's') {
                char* sp = va_arg(args, char*);
                while (*b != ' ' && *b != '\0' && *b != '\n' && *b != '\r') {
                    *sp++ = *b++;
                }
                *sp = '\0';
            }
            // Add more format specifiers if needed
        }
        else {
            if (*b != *p) {
                break;  // Mismatch between input and format string
            }
            b++;
        }
        p++;
    }

    va_end(args);
}

// Custom entry point
void WinMainCRTStartup(void) {
    my_printf("enter a number: \n");

    int number;
    my_scanf("%d", &number);

    my_printf("You entered: %d\n", number);

    // Exit the process with status code 0
    ExitProcess(0);
}

