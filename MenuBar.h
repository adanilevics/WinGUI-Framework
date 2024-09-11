#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <windows.h>
#include <vector>
#include <string>
#include "BaseUIElement.h"

class MenuBar : public BaseUIElement {
public:
    MenuBar(int x, int y, int width, int height);
    ~MenuBar();

    void AddMenu(const wchar_t* menuTitle);
    void SetFont(HFONT font);
    void SetMenuTextColor(COLORREF color);
    void SetHoverColor(COLORREF color);
    
    void Draw(HDC hdc) override;
    void HandleEvent(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

private:
    std::vector<const wchar_t*> menus;
    HFONT font;
    COLORREF menuTextColor;
    COLORREF hoverColor;
    int hoveredIndex;
};

#endif // MENU_BAR_H