#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <windows.h>
#include <vector>
#include "BaseUIElement.h"
#include "CustomButton.h"
#include "ProgressBar.h"
#include "MenuBar.h"

class WindowManager {
public:
    WindowManager(const wchar_t* title, int width, int height);
    ~WindowManager();

    void Run();

    MenuBar* AddMenuBar(int height);
    CustomButton* AddButton(const wchar_t* text, int x, int y, int width, int height, std::function<void()> onClick);
    ProgressBar* AddProgressBar(int x, int y, int width, int height, int maxValue);

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND m_hwnd;
    std::vector<BaseUIElement*> m_elements;
};

#endif // WINDOW_MANAGER_H