#pragma once

#include <windows.h>
#include "GLWindow.h"

class GLWindow;

class GLLayerView {
public:
    HMONITOR m_display;             // Monitor display ID, corresponds to CGDirectDisplayID
    GLWindow *m_GLWindow;           // Pointer to the associated window
    HGLRC m_savedContext;           // Saved OpenGL context (similar to NSOpenGLContext)
    HCURSOR m_cursor;               // Mouse cursor (similar to NSCursor)

    // Constructor
    GLLayerView();

    // Methods corresponding to macOS events and functionality
    bool acceptsFirstResponder();

    void drawRect(RECT dirtyRect);  // In Win32, RECT is used instead of NSRect
    int initWithFrame(RECT frame, GLWindow *window);

    void keyDown(WPARAM keyCode);

    void keyUp(WPARAM keyCode);

    void mouseDown(WPARAM button, LPARAM coords);

    void mouseDragged(LPARAM coords);

    void mouseMoved(LPARAM coords);

    void mouseUp(WPARAM button, LPARAM coords);

    void otherMouseDown(WPARAM button, LPARAM coords);

    void otherMouseDragged(LPARAM coords);

    void otherMouseUp(WPARAM button, LPARAM coords);

    void rightMouseDown(LPARAM coords);

    void rightMouseDragged(LPARAM coords);

    void rightMouseUp(LPARAM coords);

    void scrollWheel(WPARAM wParam, LPARAM lParam);

    void viewDidChangeBackingProperties();

    void viewDidEndLiveResize();

    void update();

    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};







