#pragma once


#include <windef.h>

class WGLContext {
public:
    //  设备上下文
    HDC m_hdc;           // Handle to the device context
    // opengl渲染上下文
    HGLRC m_hglrc;       // Handle to the OpenGL rendering context
    // 窗口句柄
    HWND m_hwnd;         // Handle to the window

    WGLContext(HWND hwnd);

    ~WGLContext();

    // Methods similar to NSOpenGLContext
    void makeCurrentContext();    // Equivalent to makeCurrentContext
    void clearCurrentContext();   // Equivalent to clearDrawable
    void flushBuffer();           // Equivalent to flushBuffer
    void update();                // Equivalent to update

    // Utility function to initialize and destroy the OpenGL context
    bool initialize();

    void destroy();
};



