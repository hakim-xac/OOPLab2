#include "GUIInterface.h"
#include "Funcions.h"
#include "Point.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Line.h"
#include "Triangle.h"
#include "Rectangle.h"
#include <vector>
#include <cassert>
#include <algorithm>


namespace KHAS {


    GUIInterface::GUIInterface(long width, long height)
        : hwnd_(GetConsoleWindow())
        , hdc_(GetDC(hwnd_))
        , window_rect_({ 0l, 0l, width, height })
        , drawing_rect_()
        , header_rect_()
        , menu_rect_()
        , text_metric_()
        , drawing_section_background_color_(Functions::rgbToCOLORREF(180, 200, 200))
        , rest_section_background_color_(Functions::rgbToCOLORREF(160, 180, 180))
        , rest_section_text_color_(Functions::rgbToCOLORREF(10, 30, 80))
        , top_offset_(39)
        , right_offset_(16)
        , active_figure_(MenuItems::Empty)
        , move_type_(MoveTypes::Empty)
    {
        GetTextMetrics(hdc_, &text_metric_);
        setWindowPosition();
        setBufferWindowSize();
        hideCursor();
        disableSelectionInConsole();
        deletePropertiesFromSystemMenu();
        updateStyleWindow();

        GetClientRect(hwnd_, &window_rect_);

        assert(window_rect_.bottom >= (180 + 280 - top_offset_));
        assert(window_rect_.right >= (640 - right_offset_));

        header_rect_ = RECT{ 0, 0, window_rect_.right, 180 };
        menu_rect_ = RECT{ 0, window_rect_.bottom - 180, window_rect_.right,window_rect_.bottom };

        drawing_rect_ = RECT{ 0, header_rect_.bottom, window_rect_.right,menu_rect_.top };

    }

    inline bool GUIInterface::isKeyDown(int key) const
    {
        return (GetKeyState(key) & 0x8000) != 0;
    }

    inline bool GUIInterface::isKeyUp(int key) const
    {
        bool ret{};
        while ((GetKeyState(key) & 0x8000) != 0) {
            Sleep(10);
            ret = true;
        }
        return ret;
    }

    void GUIInterface::pointDraw(const HDC& hdc) const
    {
        static std::vector<Point> points;
        const int size{ 100 };
        if (points.size() == 0) {
            points.reserve(size);

            for (int i{}, ie{ size }; i != ie; ++i) {
                points.emplace_back(Point(drawing_rect_));
            }
        }
        std::for_each(points.begin(), points.end(), [&](auto&& elem) {

            if (move_type_ == MoveTypes::Random) {
                elem.moveRandom();
            }
            else if (move_type_ == MoveTypes::Movement) {
                if (!isKeyDown(VK_CONTROL)) {
                    if (isKeyDown(VK_DOWN)) {
                        elem.move(MoveDirection::Down);
                    }
                    else if (isKeyDown(VK_UP)) {
                        elem.move(MoveDirection::Up);
                    }

                    if (isKeyDown(VK_LEFT)) {
                        elem.move(MoveDirection::Left);
                    }
                    else if (isKeyDown(VK_RIGHT)) {
                        elem.move(MoveDirection::Right);
                    }
                }
            }

            elem.draw(hdc);
            });
    }

    void GUIInterface::circleDraw(const HDC& hdc) const
    {
        static std::vector<Circle> circles;
        const int size{ 100 };
        if (circles.size() == 0) {
            circles.reserve(size);

            for (int i{}, ie{ size }; i != ie; ++i) {
                circles.emplace_back(Circle(drawing_rect_));
            }
        }
        std::for_each(circles.begin(), circles.end(), [&](auto&& elem) {

            if (move_type_ == MoveTypes::Random) {
                elem.moveRandom();
            }
            else if (move_type_ == MoveTypes::Movement) {
                if (!isKeyDown(VK_CONTROL)) {
                    if (isKeyDown(VK_DOWN)) {
                        elem.move(MoveDirection::Down);
                    }
                    else if (isKeyDown(VK_UP)) {
                        elem.move(MoveDirection::Up);
                    }

                    if (isKeyDown(VK_LEFT)) {
                        elem.move(MoveDirection::Left);
                    }
                    else if (isKeyDown(VK_RIGHT)) {
                        elem.move(MoveDirection::Right);
                    }
                }
            }

            elem.draw(hdc);
            });
    }

    void GUIInterface::ellipseDraw(const HDC& hdc) const
    {
        static std::vector<MyEllipse> ellipses;
        const int size{ 100 };
        if (ellipses.size() == 0) {
            ellipses.reserve(size);

            for (int i{}, ie{ size }; i != ie; ++i) {
                ellipses.emplace_back(MyEllipse(drawing_rect_));
            }
        }
        std::for_each(ellipses.begin(), ellipses.end(), [&](auto&& elem) {

            if (move_type_ == MoveTypes::Random) {
                elem.moveRandom();
            }
            else if (move_type_ == MoveTypes::Movement) {
                if (!isKeyDown(VK_CONTROL)) {
                    if (isKeyDown(VK_DOWN)) {
                        elem.move(MoveDirection::Down);
                    }
                    else if (isKeyDown(VK_UP)) {
                        elem.move(MoveDirection::Up);
                    }

                    if (isKeyDown(VK_LEFT)) {
                        elem.move(MoveDirection::Left);
                    }
                    else if (isKeyDown(VK_RIGHT)) {
                        elem.move(MoveDirection::Right);
                    }
                }
            }

            elem.draw(hdc);
            });
    }

    void GUIInterface::lineDraw(const HDC& hdc) const
    {
        static std::vector<Line> lines;
        const int size{ 100 };
        if (lines.size() == 0) {
            lines.reserve(size);

            for (int i{}, ie{ size }; i != ie; ++i) {
                lines.emplace_back(Line(drawing_rect_));
            }
        }
        std::for_each(lines.begin(), lines.end(), [&](auto&& elem) {

            if (move_type_ == MoveTypes::Random) {
                elem.moveRandom();
            }
            else if (move_type_ == MoveTypes::Movement) {
                if (!isKeyDown(VK_CONTROL)) {
                    if (isKeyDown(VK_DOWN)) {
                        elem.move(MoveDirection::Down);
                    }
                    else if (isKeyDown(VK_UP)) {
                        elem.move(MoveDirection::Up);
                    }

                    if (isKeyDown(VK_LEFT)) {
                        elem.move(MoveDirection::Left);
                    }
                    else if (isKeyDown(VK_RIGHT)) {
                        elem.move(MoveDirection::Right);
                    }
                }
            }

            elem.draw(hdc);
            });
    
    }

    void GUIInterface::triangleDraw(const HDC& hdc) const
    {
        static std::vector<Triangle> triangles;
        const int size{ 100 };
        if (triangles.size() == 0) {
            triangles.reserve(size);

            for (int i{}, ie{ size }; i != ie; ++i) {
                triangles.emplace_back(Triangle(drawing_rect_));
            }
        }
        std::for_each(triangles.begin(), triangles.end(), [&](auto&& elem) {

            if (move_type_ == MoveTypes::Random) {
                elem.moveRandom();
            }
            else if (move_type_ == MoveTypes::Movement) {
                if (!isKeyDown(VK_CONTROL)) {
                    if (isKeyDown(VK_DOWN)) {
                        elem.move(MoveDirection::Down);
                    }
                    else if (isKeyDown(VK_UP)) {
                        elem.move(MoveDirection::Up);
                    }

                    if (isKeyDown(VK_LEFT)) {
                        elem.move(MoveDirection::Left);
                    }
                    else if (isKeyDown(VK_RIGHT)) {
                        elem.move(MoveDirection::Right);
                    }
                }
            }

            elem.draw(hdc);
            });
    }

    void GUIInterface::rectangleDraw(const HDC& hdc) const
    {
        static std::vector<MyRectangle> rectangles;
        const int size{ 100 };
        if (rectangles.size() == 0) {
            rectangles.reserve(size);

            for (int i{}, ie{ size }; i != ie; ++i) {
                rectangles.emplace_back(MyRectangle(drawing_rect_));
            }
        }
        std::for_each(rectangles.begin(), rectangles.end(), [&](auto&& elem) {

            if (move_type_ == MoveTypes::Random) {
                elem.moveRandom();
            }
            else if (move_type_ == MoveTypes::Movement) {
                if (!isKeyDown(VK_CONTROL)) {
                    if (isKeyDown(VK_DOWN)) {
                        elem.move(MoveDirection::Down);
                    }
                    else if (isKeyDown(VK_UP)) {
                        elem.move(MoveDirection::Up);
                    }

                    if (isKeyDown(VK_LEFT)) {
                        elem.move(MoveDirection::Left);
                    }
                    else if (isKeyDown(VK_RIGHT)) {
                        elem.move(MoveDirection::Right);
                    }
                }
            }

            elem.draw(hdc);
            });
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
        DeleteMenu(hMenu, GetMenuItemCount(hMenu) - 1, MF_BYPOSITION);
        DeleteMenu(hMenu, GetMenuItemCount(hMenu) - 1, MF_BYPOSITION);
        DeleteMenu(hMenu, 0, MF_BYPOSITION);
        DeleteMenu(hMenu, 1, MF_BYPOSITION);
        DeleteMenu(hMenu, 2, MF_BYPOSITION);
    }

    void GUIInterface::showHeader(const HDC& hdc) const
    {

        fillRect(hdc, header_rect_, rest_section_background_color_);

        std::vector<std::wstring> base{
            { joinToString(L"����������:", delimiter(20), L"��������-��������������� ����������������")}
            , { joinToString(L"������������ ������:", delimiter(5), L"� 2") }
            , { joinToString(L"�������:", delimiter(27), L"�1") }
            , { joinToString(L"����:", delimiter(32), L"������� ������������. ����������� ������.") }
            , { joinToString(L"�������:", delimiter(27), L"������� �.�.") }
            , { joinToString(L"������:", delimiter(29), L"��-11") }
        };

        SetBkMode(hdc, TRANSPARENT);
        SelectObject(hdc, GetStockObject(DC_PEN));
        SetTextColor(hdc, rest_section_text_color_);
        {
            int step{ 20 };
            auto del{ delimiter(78, '=') };
            TextOut(hdc, 0, step, del.c_str(), static_cast<int>(del.length()));
            for (auto&& elem : base) {
                TextOut(hdc, 100, (step += 20), elem.c_str(), static_cast<int>(elem.length()));
            }

            TextOut(hdc, 0, step+20, del.c_str(), static_cast<int>(del.length()));
        }
        
    }

    void GUIInterface::showMenuFigureSelected(const HDC& hdc)
    {
        fillRect(hdc, menu_rect_, rest_section_background_color_);

        static std::vector<std::pair<MenuItems, std::wstring>> base{
            { MenuItems::Point, L"�����" }
            , { MenuItems::Circle, L"����������" }
            , { MenuItems::Ellipse, L"������" }
            , { MenuItems::Line, L"�������" }
            , { MenuItems::Triangle, L"�����������" }
            , { MenuItems::Rectangle, L"�������������" }
        };

        static auto iter{ base.begin() };

        drawMenu(base, hdc, iter->first);

        if (isKeyUp(VK_DOWN)) {
            ++iter;
            if (iter == base.end()) iter = base.end() - 1;
        }
        else if (isKeyUp(VK_UP)) {
            if (iter == base.begin()) return;
            --iter;
        }

        if (isKeyUp(VK_RETURN)) active_figure_ = iter->first;
    }

    void GUIInterface::showMenuMoveTypes(const HDC& hdc)
    {
        fillRect(hdc, menu_rect_, rest_section_background_color_);

        static std::vector<std::pair<MoveTypes, std::wstring>> base{
            { MoveTypes::Random, L"��������� ��������" }
            , { MoveTypes::Movement, L"������ ��������" }
            , { MoveTypes::Back, L"����� �� �������" }
        };

        static auto iter{ base.begin() };

        drawMenu(base, hdc, iter->first);

        if (isKeyUp(VK_DOWN)) {
            ++iter;
            if (iter == base.end()) iter = base.end() - 1;
        }
        else if (isKeyUp(VK_UP)) {
            if (iter == base.begin()) return;
            --iter;
        }
        else if (isKeyUp(VK_ESCAPE)) active_figure_ = MenuItems::Empty;
        else if (isKeyUp(VK_RETURN)) move_type_ = iter->first;        

    }

    void GUIInterface::showDraw(const HDC& hdc)
    {
        if (move_type_ == MoveTypes::Back) {
            active_figure_ = MenuItems::Empty;
            move_type_ = MoveTypes::Empty;
            return;
        }

        switch (active_figure_)
        {
        case KHAS::MenuItems::Point:    pointDraw(hdc);         break;
        case KHAS::MenuItems::Circle:   circleDraw(hdc);        break;
        case KHAS::MenuItems::Ellipse:  ellipseDraw(hdc);       break;
        case KHAS::MenuItems::Line:     lineDraw(hdc);          break;
        case KHAS::MenuItems::Triangle: triangleDraw(hdc);      break;
        case KHAS::MenuItems::Rectangle: rectangleDraw(hdc);    break;
        case KHAS::MenuItems::Empty:                            break;
        }



        fillRect(hdc, menu_rect_, rest_section_background_color_);

        static std::vector<std::pair<DrawMenuItems, std::wstring>> base{
            { DrawMenuItems::Back, L"��������� �����" }
            , { DrawMenuItems::Exit, L"����� �� �������" }
        };
        static auto iter{ base.begin() };

        drawMenu(base, hdc, iter->first);

        std::wstring description{ L"��� ���������� �������� ����, ������� CTRL � ������� ������ ��� ����." };
        TextOut(hdc, 40, menu_rect_.bottom - 50, description.c_str(), static_cast<int>(description.length()));

        if (isKeyDown(VK_CONTROL) && isKeyUp(VK_DOWN)) {
            ++iter;
            if (iter == base.end()) iter = base.end() - 1;
        }
        else if (isKeyDown(VK_CONTROL) && isKeyUp(VK_UP)) {
            if (iter == base.begin()) return;
            --iter;
        }
        else if (isKeyUp(VK_RETURN)) {
            if (iter->first == DrawMenuItems::Back) move_type_ = MoveTypes::Empty;
            else if (iter->first == DrawMenuItems::Exit) {
                move_type_ = MoveTypes::Empty;
                active_figure_ = MenuItems::Empty;
            };
        }
    }

    void GUIInterface::fillRect(const HDC& hdc, const RECT& rect, COLORREF color) const
    {
        HBRUSH solidBrush{ CreateSolidBrush(color) };
        assert(solidBrush != NULL);
        assert(FillRect(hdc, &rect, solidBrush) != 0);
        DeleteObject(solidBrush);
    }

    constexpr std::wstring GUIInterface::delimiter(size_t lenght, char del) const
    {
        return std::wstring(lenght, del);
    }

    
    void GUIInterface::loop()
    {        

        while (true) {
            
            HDC memDC{ CreateCompatibleDC(hdc_) };
            assert(memDC != NULL);
            auto width{ window_rect_.right - window_rect_.left };
            auto height{ window_rect_.bottom - window_rect_.top };

            HBITMAP memBM{ CreateCompatibleBitmap(hdc_, width, height) };
            assert(memBM != NULL);

            SelectObject(memDC, memBM);
            HBRUSH solidBrush{ CreateSolidBrush(drawing_section_background_color_) };
            assert(solidBrush != NULL);
            assert(FillRect(memDC, &window_rect_, solidBrush) != 0);
            DeleteObject(solidBrush);
            /*//////////////////////////////////*/
            
            if (active_figure_ == MenuItems::Empty) showMenuFigureSelected(memDC);
            else if (move_type_ == MoveTypes::Empty) showMenuMoveTypes(memDC);
            else showDraw(memDC);
            showHeader(memDC);
            /*/////////////////////////////////*/

            BitBlt(hdc_, 0, 0, width, height, memDC, 0, 0, SRCCOPY);
            DeleteDC(memDC);
            DeleteObject(memBM);

            Sleep(50);
        }
    }


}