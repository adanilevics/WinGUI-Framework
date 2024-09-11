#include "WindowClass.h"

// Initialize the static window count to 0
int WindowClass::windowCount = 0;

WindowClass::WindowClass(const wchar_t* windowTitle, const wchar_t* className, COLORREF backgroundColor, bool closeAllOnExit)
    : windowTitle(windowTitle), className(className), backgroundColor(backgroundColor), hwnd(NULL), closeAllOnExit(closeAllOnExit) {}

bool WindowClass::Create(HINSTANCE hInstance, int nCmdShow, int width, int height, int xPos, int yPos) {
    WNDCLASS wc = { };
    wc.lpfnWndProc = StaticWindowProc; // Use the static method for all windows
    wc.hInstance = hInstance;
    wc.lpszClassName = className;

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        className,                      // Window class
        windowTitle,                    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        xPos, yPos, width, height,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        this        // Pass 'this' pointer as additional data
    );

    if (hwnd == NULL) {
        return false;
    }

    // Store the 'this' pointer in the window's user data
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    ShowWindow(hwnd, nCmdShow);

    // Increase the window count when a new window is created
    windowCount++;
    return true;
}

void WindowClass::AddButton(const wchar_t* buttonText, int x, int y, int width, int height) {
    // Create a button control inside the window
    CreateWindow(
        L"BUTTON",     // Button class
        buttonText,    // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Button styles
        x, y, width, height,   // Button position and size
        hwnd,         // Parent window
        (HMENU) 1,    // Button ID
        (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), 
        NULL          // Pointer not needed
    );
}

int WindowClass::RunMessageLoop() {
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WindowClass::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    WindowClass* pThis = reinterpret_cast<WindowClass*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    if (pThis) {
        return pThis->WindowProc(hwnd, uMsg, wParam, lParam);
    } else {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

LRESULT CALLBACK WindowClass::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            // Decrease the window count when a window is destroyed
            windowCount--;

            // If `closeAllOnExit` is true, or no windows remain, quit the message loop
            if (closeAllOnExit || windowCount == 0) {
                PostQuitMessage(0);
            }
            return 0;

        case WM_PAINT:
            PaintWindow(hwnd);
            return 0;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {  // If the button with ID 1 is pressed
                MessageBox(hwnd, L"Button Pressed!", L"Information", MB_OK);
            }
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void WindowClass::PaintWindow(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // Create a solid brush with the instance's background color
    HBRUSH hBrush = CreateSolidBrush(backgroundColor);
    FillRect(hdc, &ps.rcPaint, hBrush);

    // Clean up
    DeleteObject(hBrush);
    EndPaint(hwnd, &ps);
}
