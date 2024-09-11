#include "MenuBar.h"
#include <windowsx.h>

MenuBar::MenuBar(int x, int y, int width, int height)
    : BaseUIElement(x, y, width, height) {
    menuTextColor = RGB(0, 0, 0);
    backgroundColor = RGB(240, 240, 240);
    hoverColor = RGB(220, 220, 220);

    font = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                       OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                       DEFAULT_PITCH | FF_DONTCARE, L"Arial");
}

MenuBar::~MenuBar() {
    if (font) DeleteObject(font);
}

void MenuBar::AddMenu(const wchar_t* menuTitle) {
    menus.push_back(menuTitle);
}

void MenuBar::SetFont(HFONT newFont) {
    if (font) DeleteObject(font);
    font = newFont;
}

void MenuBar::SetMenuTextColor(COLORREF color) {
    menuTextColor = color;
}

void MenuBar::SetHoverColor(COLORREF color) {
    hoverColor = color;
}

void MenuBar::Draw(HDC hdc) {
    HBRUSH brush = CreateSolidBrush(backgroundColor);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    Rectangle(hdc, x, y, x + width, y + height);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, menuTextColor);
    HFONT oldFont = (HFONT)SelectObject(hdc, font);

    int menuWidth = width / menus.size();
    for (size_t i = 0; i < menus.size(); ++i) {
        RECT menuRect = {(LONG)(x + i * menuWidth), y, (LONG)(x + (i + 1) * menuWidth), y + height};
        
        if (i == hoveredIndex) {
            HBRUSH hoverBrush = CreateSolidBrush(hoverColor);
            FillRect(hdc, &menuRect, hoverBrush);
            DeleteObject(hoverBrush);
        }

        DrawTextW(hdc, menus[i], -1, &menuRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    }

    SelectObject(hdc, oldFont);
}

void MenuBar::HandleEvent(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_MOUSEMOVE: {
            int mouseX = GET_X_LPARAM(lParam);
            int mouseY = GET_Y_LPARAM(lParam);
            if (mouseY >= y && mouseY < y + height) {
                int menuWidth = width / menus.size();
                int newHoveredIndex = (mouseX - x) / menuWidth;
                if (newHoveredIndex >= 0 && newHoveredIndex < static_cast<int>(menus.size()) && newHoveredIndex != hoveredIndex) {
                    hoveredIndex = newHoveredIndex;
                    // TODO: Request redraw
                }
            } else if (hoveredIndex != -1) {
                hoveredIndex = -1;
                // TODO: Request redraw
            }
            break;
        }
         if (uMsg == WM_LBUTTONDOWN) {
        int clickedIndex = (GET_X_LPARAM(lParam) - x) / (width / menus.size());
        if (clickedIndex >= 0 && clickedIndex < static_cast<int>(menus.size())) {
            OutputDebugStringW((L"Clicked menu: " + std::wstring(menus[clickedIndex]) + L"\n").c_str());
        }
            break;
        }
    }
}