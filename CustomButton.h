#ifndef CUSTOM_BUTTON_H
#define CUSTOM_BUTTON_H

#include <windows.h>
#include <functional>
#include "BaseUIElement.h"

class CustomButton : public BaseUIElement {
public:
    CustomButton(const wchar_t* text, int x, int y, int width, int height, std::function<void()> onClick);
    ~CustomButton();

    void SetBackgroundColor(COLORREF color);
    void SetFont(HFONT font);
    void SetButtonTextColor(COLORREF color);
    void SetHoverColor(COLORREF color);
    void SetPressedColor(COLORREF color);
    
    void Draw(HDC hdc) override;
    void HandleEvent(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

private:
    const wchar_t* text;
    std::function<void()> onClick;
    HFONT font;
    COLORREF buttonTextColor;
    COLORREF hoverColor;
    COLORREF pressedColor;
    bool isHovered;
    bool isPressed;
};

#endif // CUSTOM_BUTTON_H