#include "WindowManager.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    WindowManager window(L"Custom UI Elements Demo", 800, 600);

    // Menu bar setup
    MenuBar* menuBar = window.AddMenuBar(30);
    menuBar->AddMenu(L"File");
    menuBar->AddMenu(L"Edit");
    menuBar->AddMenu(L"View");
    menuBar->AddMenu(L"Help");
    menuBar->SetMenuTextColor(RGB(0, 0, 0));
    menuBar->SetHoverColor(RGB(200, 220, 240));

    // Progress bar setup
    ProgressBar* progressBar = window.AddProgressBar(50, 200, 300, 30, 100);
    progressBar->SetValue(50);
    progressBar->SetBarColor(RGB(0, 200, 0));

    // Button setup
    CustomButton* button1 = window.AddButton(L"Increment", 50, 100, 120, 40, [progressBar]() {
        int currentValue = progressBar->GetValue();
        progressBar->SetValue(currentValue + 10);
    });
    button1->SetButtonTextColor(RGB(255, 255, 255));
    button1->SetBackgroundColor(RGB(0, 120, 215));
    button1->SetHoverColor(RGB(0, 100, 200));

    CustomButton* button2 = window.AddButton(L"Decrement", 200, 100, 120, 40, [progressBar]() {
        int currentValue = progressBar->GetValue();
        progressBar->SetValue(currentValue - 10);
    });
    button2->SetButtonTextColor(RGB(255, 255, 255));
    button2->SetBackgroundColor(RGB(220, 0, 0));
    button2->SetHoverColor(RGB(200, 0, 0));

    window.Run();

    return 0;
}

int main(int argc, char* argv[]) {
    return wWinMain(GetModuleHandle(NULL), NULL, GetCommandLineW(), SW_SHOWNORMAL);
}