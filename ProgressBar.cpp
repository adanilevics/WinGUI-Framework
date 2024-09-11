#include "ProgressBar.h"
#include <sstream>
#include <iomanip>

ProgressBar::ProgressBar(int x, int y, int width, int height, int maxValue)
    : BaseUIElement(x, y, width, height, RGB(240, 240, 240)),  // Light gray background
      currentValue(0), maxValue(maxValue), 
      barColor(RGB(0, 120, 215)), // Blue bar color
      textColor(RGB(0, 0, 0)) {
    font = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                      OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, 
                      DEFAULT_PITCH | FF_DONTCARE, L"Arial");
}

ProgressBar::~ProgressBar() {
    if (font) DeleteObject(font);
}

void ProgressBar::SetValue(int value) {
    currentValue = (value < 0) ? 0 : (value > maxValue) ? maxValue : value;
}

int ProgressBar::GetValue() const {
    return currentValue;
}

void ProgressBar::SetBarColor(COLORREF color) {
    barColor = color;
}

void ProgressBar::SetTextColor(COLORREF color) {
    textColor = color;
}

void ProgressBar::Draw(HDC hdc) {
    // Draw background
    HBRUSH bgBrush = CreateSolidBrush(backgroundColor);
    HPEN borderPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 200));
    SelectObject(hdc, bgBrush);
    SelectObject(hdc, borderPen);
    Rectangle(hdc, x, y, x + width, y + height);

    // Draw progress bar
    int barWidth = (int)((float)currentValue / maxValue * width);
    HBRUSH barBrush = CreateSolidBrush(barColor);
    SelectObject(hdc, barBrush);
    Rectangle(hdc, x, y, x + barWidth, y + height);

    // Draw text
    SetBkMode(hdc, TRANSPARENT);
    ::SetTextColor(hdc, textColor);
    SelectObject(hdc, font);

    std::wostringstream woss;
    woss << std::setw(3) << (int)((float)currentValue / maxValue * 100) << L"%";
    std::wstring progressText = woss.str();
    
    RECT textRect = { x, y, x + width, y + height };
    DrawTextW(hdc, progressText.c_str(), -1, &textRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    // Clean up
    DeleteObject(bgBrush);
    DeleteObject(borderPen);
    DeleteObject(barBrush);
}

void ProgressBar::HandleEvent(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // Progress bar doesn't handle events in this implementation
}