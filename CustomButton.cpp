#include "CustomButton.h"
#include <windowsx.h>

CustomButton::CustomButton(const wchar_t* text, int x, int y, int width, int height, std::function<void()> onClick)
    : BaseUIElement(x, y, width, height), text(text), onClick(onClick) {
    buttonTextColor = RGB(0, 0, 0);
    backgroundColor = RGB(200, 200, 200);
    hoverColor = RGB(180, 180, 180);
    isHovered = false;

    font = CreateFontW(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                       OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                       DEFAULT_PITCH | FF_DONTCARE, L"Arial");
}

CustomButton::~CustomButton() {
    if (font) DeleteObject(font);
}

void CustomButton::SetBackgroundColor(COLORREF color) {
    backgroundColor = color;
}

void CustomButton::SetFont(HFONT newFont) {
    if (font) DeleteObject(font);
    font = newFont;
}

void CustomButton::SetButtonTextColor(COLORREF color) {
    buttonTextColor = color;
}

void CustomButton::SetHoverColor(COLORREF color) {
    hoverColor = color;
}

void CustomButton::SetPressedColor(COLORREF color) {
    pressedColor = color;
}

void CustomButton::Draw(HDC hdc) {
    HBRUSH brush = CreateSolidBrush(isHovered ? hoverColor : backgroundColor);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    Rectangle(hdc, x, y, x + width, y + height);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, buttonTextColor);
    HFONT oldFont = (HFONT)SelectObject(hdc, font);
    RECT textRect = {x, y, x + width, y + height};
    DrawTextW(hdc, text, -1, &textRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    SelectObject(hdc, oldFont);
}

void CustomButton::HandleEvent(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_MOUSEMOVE: {
            int mouseX = GET_X_LPARAM(lParam);
            int mouseY = GET_Y_LPARAM(lParam);
            bool newHovered = (mouseX >= x && mouseX < x + width && mouseY >= y && mouseY < y + height);
            if (newHovered != isHovered) {
                isHovered = newHovered;
                // TODO: Request redraw
            }
            break;
        }
        case WM_LBUTTONDOWN: {
            int mouseX = GET_X_LPARAM(lParam);
            int mouseY = GET_Y_LPARAM(lParam);
            if (mouseX >= x && mouseX < x + width && mouseY >= y && mouseY < y + height) {
                isPressed = true;
                // TODO: Request redraw
            }
            break;
        }
        case WM_LBUTTONUP: {
            if (isPressed) {
                isPressed = false;
                int mouseX = GET_X_LPARAM(lParam);
                int mouseY = GET_Y_LPARAM(lParam);
                if (mouseX >= x && mouseX < x + width && mouseY >= y && mouseY < y + height) {
                    if (onClick) onClick();
                }
                // TODO: Request redraw
            }
            break;
        }
    }
}