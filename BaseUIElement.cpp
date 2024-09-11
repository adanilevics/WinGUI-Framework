#include "BaseUIElement.h"

BaseUIElement::BaseUIElement(int x, int y, int width, int height, COLORREF backgroundColor)
    : x(x), y(y), width(width), height(height), backgroundColor(backgroundColor), font(NULL) {
    CreateElementFont();
}

void BaseUIElement::HandleEvent(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // Default implementation does nothing
}

void BaseUIElement::CreateElementFont(int fontSize, const wchar_t* fontName) {
    if (font) {
        DeleteObject(font);
    }
    font = CreateFontW(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                       OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                       DEFAULT_PITCH | FF_DONTCARE, fontName);
}