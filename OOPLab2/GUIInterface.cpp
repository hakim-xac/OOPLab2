#include "GUIInterface.h"
#include "Funcions.h"
#include <cassert>


namespace KHAS {

    inline bool GUIInterface::isKeyDown(int key) const
    {
        return (GetKeyState(key) & 0x8000) != 0;
    }

    void GUIInterface::hideCursor() const
    {
        HANDLE handle{ GetStdHandle(STD_OUTPUT_HANDLE) };
        CONSOLE_CURSOR_INFO structCursorInfo;
        GetConsoleCursorInfo(handle, &structCursorInfo);
        if (structCursorInfo.bVisible) {
            structCursorInfo.bVisible = false;
            SetConsoleCursorInfo(handle, &structCursorInfo);
        }
    }

    void GUIInterface::setWindowPosition() const
    {
        HANDLE handle{ GetStdHandle(STD_OUTPUT_HANDLE) };
        auto width{ window_rect_.right - window_rect_.left };
        auto height{ window_rect_.bottom - window_rect_.top };

        auto window_pos_x{ (GetSystemMetrics(SM_CXSCREEN) >> 1) - (width >> 1) };
        auto window_pos_y{ (GetSystemMetrics(SM_CYSCREEN) >> 1) - (height >> 1) };
        MoveWindow(hwnd_, window_pos_x, window_pos_y, width, height, TRUE);
    }

    void GUIInterface::setBufferWindowSize() const
    {
        CONSOLE_SCREEN_BUFFER_INFO csi;
        GetConsoleScreenBufferInfo(hwnd_, &csi);
        short y{ csi.srWindow.Bottom - csi.srWindow.Top + 1 };
        SetConsoleScreenBufferSize(hwnd_, { csi.dwSize.X, y });
    }

    void GUIInterface::updateStyleWindow() const
    {
        LONG_PTR style_ptr{ SetWindowLongPtr(hwnd_, GWL_STYLE
            , WS_SIZEBOX & ~WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION) };
        SetWindowPos(hwnd_, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
        ShowWindow(hwnd_, SW_SHOW);
    }

    void GUIInterface::disableSelectionInConsole() const
    {
        HANDLE hConsole{ GetStdHandle(STD_INPUT_HANDLE) };
        DWORD prevConsoleMode{};
        GetConsoleMode(hConsole, &prevConsoleMode);
        SetConsoleMode(hConsole, ENABLE_EXTENDED_FLAGS |
            (prevConsoleMode & ~ENABLE_QUICK_EDIT_MODE));
    }
        
    void GUIInterface::deletePropertiesFromSystemMenu() const
    {
        HMENU hMenu{ GetSystemMenu(hwnd_, false) };
        DeleteMenu(hMenu, GetMenuItemCount(hMenu) - 1, MF_BYPOSITION);
    }

    GUIInterface::GUIInterface(long width, long height)
        : hwnd_( GetConsoleWindow() )
        , hdc_( GetDC(hwnd_) )
        , window_rect_( { 0l, 0l, width, height } )
        , drawing_rect_()
        , top_offset_(39)
        , right_offset_(16)
    {
        setWindowPosition();
        setBufferWindowSize(); 
        hideCursor();
        disableSelectionInConsole();
        deletePropertiesFromSystemMenu();
        updateStyleWindow();

        GetClientRect(hwnd_, &window_rect_);
        
        assert(window_rect_.bottom >= (180 + 280 - top_offset_));

        drawing_rect_ = RECT{ 0, 180, window_rect_.right,window_rect_.bottom - 280 };
    }

    void GUIInterface::loop()
    {
        while (isKeyDown(VK_ESCAPE)) {

            hideCursor();
            HDC memDC{ CreateCompatibleDC(hdc_) };
            auto width{ window_rect_.right - window_rect_.left };
            auto height{ window_rect_.bottom - window_rect_.top };

            HBITMAP memBM{ CreateCompatibleBitmap(hdc_, width, height) };
            SelectObject(memDC, memBM);
            FillRect(memDC, &window_rect_, CreateSolidBrush(Functions::rgbToCOLORREF(255, 255, 255)));
            //showHeader(memDC);
            //showMenu(memDC);
            //showTPoints();
            BitBlt(hdc_, 0, 0, width, height, memDC, 0, 0, SRCCOPY);
            DeleteDC(memDC);
            DeleteObject(memBM);

            //readQueue();
        }
    }


}