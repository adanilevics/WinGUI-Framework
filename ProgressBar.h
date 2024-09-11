#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <windows.h>
#include <string>
#include "BaseUIElement.h"

class ProgressBar : public BaseUIElement {
public:
    ProgressBar(int x, int y, int width, int height, int maxValue);
    ~ProgressBar();

    void SetValue(int value);
    int GetValue() const;
    void SetBarColor(COLORREF color);
    void SetTextColor(COLORREF color);
    void Draw(HDC hdc) override;
    void HandleEvent(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

private:
    int currentValue;
    int maxValue;
    COLORREF barColor;
    COLORREF textColor;
    HFONT font;
};

#endif // PROGRESS_BAR_H