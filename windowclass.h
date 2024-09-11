#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

class WindowClass {
public:
    WindowClass(const wchar_t* windowTitle, const wchar_t* className, COLORREF backgroundColor, bool closeAllOnExit);

    bool Create(HINSTANCE hInstance, int nCmdShow, int width, int height, int xPos, int yPos);
    int RunMessageLoop();

    void AddButton(const wchar_t* buttonText, int x, int y, int width, int height);

private:
    const wchar_t* windowTitle;
    const wchar_t* className;
    COLORREF backgroundColor;
    HWND hwnd;
    bool closeAllOnExit;  // Determines if closing one window closes all windows

    static int windowCount; // Track the number of open windows
    static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    void PaintWindow(HWND hwnd);
};

#endif // WINDOW_CLASS_H
