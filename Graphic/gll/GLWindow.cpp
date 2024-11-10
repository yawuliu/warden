#include "GLWindow.h"
#include "GLContext.h"
#include <cmath>


GLWindowCallbacks DefaultCallbacks = {
        // TODO
};

bool GLWindow::CanEnterFullscreenMode() {
    return true;
}

void GLWindow::CreateView() {
    // Create an OpenGL rendering context for the window if it doesn't exist
    if (!m_Context) {
        // Get the device context for the window
        HDC hdc = GetDC(m_Window);

        // Setup the pixel format for OpenGL rendering
        PIXELFORMATDESCRIPTOR pfd;
        memset(&pfd, 0, sizeof(pfd));
        pfd.nSize = sizeof(pfd);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 24;
        pfd.iLayerType = PFD_MAIN_PLANE;

        // Choose the closest pixel format that matches the PFD
        int pixelFormat = ChoosePixelFormat(hdc, &pfd);
        SetPixelFormat(hdc, pixelFormat, &pfd);

        // Create an OpenGL rendering context
        m_Context = wglCreateContext(hdc);

        // Make the rendering context current
        wglMakeCurrent(hdc, m_Context);

        // Release the device context after setting up
        ReleaseDC(m_Window, hdc);
    }
}

NTempest::CRect GLWindow::GetBackingRect() {
    RECT rect;
    GetClientRect(m_Window, &rect);
    NTempest::CRect ret(rect.bottom, rect.left, rect.top, rect.right);
    return ret;
}

HWND GLWindow::GetNSView() {
    return m_Window;
}

NTempest::CRect GLWindow::GetRect() {
    RECT rect;
    GetWindowRect(m_Window, &rect);
    NTempest::CRect ret(rect.bottom, rect.left, rect.top, rect.right);
    return ret;
}

void GLWindow::EnterFullscreenMode() {
// Check if already in fullscreen mode
    if (m_FullscreenWindow) {
        return;  // Already in fullscreen
    }

    // Get the current window position and size before going fullscreen
    GetWindowRect(m_Window, &m_WindowedRect);

    // Set the window to fullscreen style (borderless window)
    SetWindowLongPtr(m_Window, GWL_STYLE, WS_POPUP | WS_VISIBLE);

    // Get the screen dimensions
    HMONITOR hMonitor = MonitorFromWindow(m_Window, MONITOR_DEFAULTTONEAREST);
    MONITORINFO monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(hMonitor, &monitorInfo);
    RECT fullscreenRect = monitorInfo.rcMonitor;

    // Set window position and size to cover the entire screen
    SetWindowPos(m_Window, nullptr, fullscreenRect.left, fullscreenRect.top,
                 fullscreenRect.right - fullscreenRect.left,
                 fullscreenRect.bottom - fullscreenRect.top,
                 SWP_NOZORDER | SWP_FRAMECHANGED);

    // Mark the window as fullscreen
    m_FullscreenWindow = this;  // Assign the current window to m_FullscreenWindow

    // Hide the cursor in fullscreen if desired
    ShowCursor(FALSE);
}

void GLWindow::ExitFullscreenMode() {
    // Check if the window is already in fullscreen mode
    if (m_FullscreenWindow) {
        // Restore the window to its original style (from fullscreen mode)
        SetWindowLongPtr(m_Window, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);

        // Set the window to its previous size and position before fullscreen
        SetWindowPos(m_Window, nullptr, m_WindowedRect.left, m_WindowedRect.top,
                     m_WindowedRect.right - m_WindowedRect.left,
                     m_WindowedRect.bottom - m_WindowedRect.top,
                     SWP_NOZORDER | SWP_FRAMECHANGED);

        // Show the window with its borders and title bar again
        ShowWindow(m_Window, SW_NORMAL);

        // Clean up the fullscreen window flag
        m_FullscreenWindow = nullptr;
    }
}

void GLWindow::Init(const NTempest::CRect &rect, GLWindowCallbacks *callbacks) {
    m_Callbacks = callbacks;

//    WNDCLASS wc = {0};
//    wc.lpfnWndProc = GLWindow::WindowProc;
//    wc.hInstance = GetModuleHandle(nullptr);
//    wc.lpszClassName = "GLWindowClass";
//
//    RegisterClass(&wc);

    m_Window = CreateWindowEx(0, "GLWindowClass", "OpenGL Window",
                              WS_OVERLAPPEDWINDOW | WS_VISIBLE, rect.minX, rect.minY,
                              rect.Width(), rect.Height(),
                              nullptr, nullptr, GetModuleHandle(nullptr), this);
}

void GLWindow::Resize(uint32_t width, uint32_t height) {
    SetWindowPos(m_Window, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
    if (m_Callbacks && m_Callbacks->OnResized) {
        m_Callbacks->OnResized(width, height, true);
    }
}

void GLWindow::SetCallbacks(GLWindowCallbacks *callbacks) {
    if (callbacks) {
        this->m_Callbacks = callbacks;
        this->m_ActiveCallbacks = callbacks;
    } else {
        this->m_Callbacks = &DefaultCallbacks;
        this->m_ActiveCallbacks = &DefaultCallbacks;
    }
}

void GLWindow::SetOpenGLContext(HGLRC context) {
    m_Context = context;
    wglMakeCurrent(GetDC(m_Window), m_Context);
}

void GLWindow::SetTitle(const char *title) {
    SetWindowText(m_Window, title);
}

void GLWindow::SetViewClass(const std::string &viewClass) {
    // Store the view class in the class member variable
    m_ViewClass = viewClass;

    // Register the custom window class for future window creation
//    if (!RegisterClassEx(&m_ViewClass)) {
//        MessageBox(nullptr, "Failed to register window class!", "Error", MB_OK | MB_ICONERROR);
//    }
}

void GLWindow::Show() {
    ShowWindow(m_Window, SW_SHOW);
    m_Shown = true;
}

int32_t GLWindow::GetWidth(void) {
    return GetWidth();
}

int32_t GLWindow::GetHeight(void) {
    return GetHeight();
}

void GLWindow::SetOpenGLContext(GLContext *context) {

}

int32_t GLWindow::GetBackingWidth() {
    return GLAbstractWindow::GetBackingWidth();
}

int32_t GLWindow::GetBackingHeight() {
    return GLAbstractWindow::GetBackingHeight();
}


