#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include "Storm/Thread.h"
#include "GLTypes.h"
#include "WGLContext.h"


// https://github.com/SFML/SFML/blob/master/src/SFML/Window/Win32/WglContext.hpp
// https://docs.kanzi.com/3.9.8/en/reference/kanzi-runtime-api/a01314.html
// https://doc.qt.io/qt-6/qopenglcontext.html
class GLDevice;

class GLAbstractWindow;

class GLContext {
public:
    // Types
    struct Context {
        WGLContext *context;
        int pixelFormat;
        int32_t sampleCount;

        ~Context();
    };

    struct GammaFormula {
        float m_RedMin;
        float m_RedMax;
        float m_RedGamma;
        float m_GreenMin;
        float m_GreenMax;
        float m_GreenGamma;
        float m_BlueMin;
        float m_BlueMax;
        float m_BlueGamma;
    };

    // Static variables
    static WGLContext *s_MainContext;
    static Blizzard::Thread::TLSSlot s_CurrentContext;
    static Blizzard::Thread::TLSSlot s_CurrentGLContext;
    static int s_DesktopMode;

    // Static functions
    static WGLContext *GetNSOpenGLCurrentContext();

    static WGLContext *GetCurrentContext();

    static void SetCurrentContext(WGLContext *);

    static GLContext *GetCurrentGLContext();

    static void SetCurrentGLContext(GLContext *);

    // Member variables
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> m_DebugName;
    std::map<uint32_t, GLContext::Context, std::less<uint32_t>, std::allocator<std::pair<const uint32_t, GLContext::Context>>> m_Contexts;
    Context *m_Context;
    GLDevice *m_Device;
    GLAbstractWindow *m_Window;
    bool m_Windowed;
    bool m_MTGLEnabled;
    bool m_VSyncEnabled;
    bool m_CaptureDisplay;
    uint32_t m_Width;
    uint32_t m_Height;
    uint32_t m_RefreshRate;
    GammaFormula m_GammaFormula;
    bool m_GammaTablesSet;
    std::vector<uint16_t, std::allocator<uint16_t>> m_GammaTableR;
    std::vector<uint16_t, std::allocator<uint16_t>> m_GammaTableG;
    std::vector<uint16_t, std::allocator<uint16_t>> m_GammaTableB;
    std::vector<uint16_t, std::allocator<uint16_t>> m_OsGammaTableR;
    std::vector<uint16_t, std::allocator<uint16_t>> m_OsGammaTableG;
    std::vector<uint16_t, std::allocator<uint16_t>> m_OsGammaTableB;

    // Member functions
    GLContext(GLDevice *, const char *);

    int32_t GetBackingWidth();

    int32_t GetBackingHeight();

    int32_t GetWidth();

    int32_t GetHeight();

    bool IsCurrentContext();

    void MakeCurrent(bool);

    void SetContextFormat(GLTextureFormat, uint32_t);

    void SetFullscreenMode(uint32_t, uint32_t, uint32_t, bool);

    void SetWindow(GLAbstractWindow *, bool);

    void Swap();

    void Update();
};


