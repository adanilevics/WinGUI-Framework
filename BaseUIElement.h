#ifndef BASE_UI_ELEMENT_H
#define BASE_UI_ELEMENT_H

#include <windows.h>

// Base class for all UI elements
class BaseUIElement {
public:
    BaseUIElement(int x, int y, int width, int height, COLORREF backgroundColor = RGB(240, 240, 240));

    virtual void Draw(HDC hdc) = 0;  // Method to draw the element
    virtual void HandleEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);  // Handle events like mouse clicks, etc.

    // Getter methods
    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    COLORREF GetBackgroundColor() const { return backgroundColor; }

    // Setter methods
    void SetX(int newX) { x = newX; }
    void SetY(int newY) { y = newY; }
    void SetWidth(int newWidth) { width = newWidth; }
    void SetHeight(int newHeight) { height = newHeight; }
    void SetBackgroundColor(COLORREF newColor) { backgroundColor = newColor; }

protected:
    int x, y, width, height;  // Position and size of the element
    COLORREF backgroundColor; // Background color
    HFONT font;               // Font used for text rendering

    // Helper method to create a font
    void CreateElementFont(int fontSize = 16, const wchar_t* fontName = L"Arial");
};

#endif // BASE_UI_ELEMENT_H