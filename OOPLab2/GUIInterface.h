#ifndef GUIInterface__
#define GUIInterface__

#include <Windows.h>

namespace KHAS {
    class GUIInterface
    {
    private:
        HWND hwnd_;
        HDC hdc_;
        RECT window_rect_;
        RECT drawing_rect_;

        int top_offset_;
        int right_offset_;

    private:

        inline bool isKeyDown(int key)          const;
        void hideCursor()                       const;
        void setWindowPosition()                const;
        void setBufferWindowSize()              const;
        void updateStyleWindow()                const;
        void disableSelectionInConsole()        const;
        void deletePropertiesFromSystemMenu()   const;

    public:
        GUIInterface() = delete;
        GUIInterface(long width, long height);

        void loop();
    };
}

#endif