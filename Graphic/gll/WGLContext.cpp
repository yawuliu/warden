#include <Windows.h>
#include "WGLContext.h"
#include "GL/glew.h"

WGLContext::WGLContext(HWND hwnd) {
    m_hwnd = hwnd;
    initialize();
}

bool WGLContext::initialize() {
    m_hdc = GetDC(m_hwnd);  // Get device context for the window
    if (!m_hdc) {
        return false;
    }

    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
    if (pixelFormat == 0 || !SetPixelFormat(m_hdc, pixelFormat, &pfd)) {
        return false;
    }

    // Create the OpenGL rendering context
    m_hglrc = wglCreateContext(m_hdc);
    if (!m_hglrc) {
        return false;
    }

    return true;
}

void WGLContext::makeCurrentContext() {
    if (m_hdc && m_hglrc) {
        wglMakeCurrent(m_hdc, m_hglrc);
    }
}

void WGLContext::clearCurrentContext() {
    wglMakeCurrent(nullptr, nullptr);
}

void WGLContext::flushBuffer() {
    if (m_hdc) {
        SwapBuffers(m_hdc);
    }
}

void WGLContext::update() {
    RECT rect;
    GetClientRect(m_hwnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    glViewport(0, 0, width, height);  // Update the OpenGL viewport
}

WGLContext::~WGLContext() {
    destroy();
}

void WGLContext::destroy() {
    if (m_hglrc) {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(m_hglrc);
        m_hglrc = nullptr;
    }
    if (m_hdc) {
        ReleaseDC(m_hwnd, m_hdc);
        m_hdc = nullptr;
    }
}



