#include "WindowManager.h"

WindowManager::WindowManager(const wchar_t* title, int width, int height) {
    const wchar_t CLASS_NAME[] = L"WindowManagerClass";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    m_hwnd = CreateWindowExW(
        0, CLASS_NAME, title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, GetModuleHandle(NULL), this
    );

    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

WindowManager::~WindowManager() {
    for (auto element : m_elements) {
        delete element;
    }
}

void WindowManager::Run() {
    ShowWindow(m_hwnd, SW_SHOWDEFAULT);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

MenuBar* WindowManager::AddMenuBar(int height) {
    MenuBar* menuBar = new MenuBar(0, 0, 800, height);
    m_elements.push_back(menuBar);
    return menuBar;
}

CustomButton* WindowManager::AddButton(const wchar_t* text, int x, int y, int width, int height, std::function<void()> onClick) {
    CustomButton* button = new CustomButton(text, x, y, width, height, onClick);
    m_elements.push_back(button);
    return button;
}

ProgressBar* WindowManager::AddProgressBar(int x, int y, int width, int height, int maxValue) {
    ProgressBar* progressBar = new ProgressBar(x, y, width, height, maxValue);
    m_elements.push_back(progressBar);
    return progressBar;
}

LRESULT CALLBACK WindowManager::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    WindowManager* manager = reinterpret_cast<WindowManager*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (manager) {
        return manager->HandleMessage(hwnd, uMsg, wParam, lParam);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT WindowManager::HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        for (auto element : m_elements) {
            element->Draw(hdc);
        }
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
        for (auto element : m_elements) {
            element->HandleEvent(uMsg, wParam, lParam);
        }
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}