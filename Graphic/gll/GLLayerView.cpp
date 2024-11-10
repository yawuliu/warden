#include "GLLayerView.h"
#include <windows.h>
#include <iostream>

LRESULT CALLBACK GLLayerView::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    GLWindow *window = reinterpret_cast<GLWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (uMsg) {
        case WM_SIZE:
            if (window && window->m_Callbacks && window->m_Callbacks->OnResized) {
                window->m_Callbacks->OnResized(LOWORD(lParam), HIWORD(lParam), true);
            }
            break;
        case WM_LBUTTONDOWN:
            if (window && window->m_Callbacks && window->m_Callbacks->OnMouseDown) {
                window->m_Callbacks->OnMouseDown(LOWORD(lParam), HIWORD(lParam), wParam);
            }
            break;
        case WM_MOUSEMOVE:
            if (window && window->m_Callbacks && window->m_Callbacks->OnMouseMoved) {
                window->m_Callbacks->OnMouseMoved(LOWORD(lParam), HIWORD(lParam));
            }
            break;
        case WM_LBUTTONUP:
            if (window && window->m_Callbacks && window->m_Callbacks->OnMouseUp) {
                window->m_Callbacks->OnMouseUp(LOWORD(lParam), HIWORD(lParam), wParam);
            }
            break;
        case WM_KEYDOWN:
            if (window && window->m_Callbacks && window->m_Callbacks->OnKeyDown) {
                window->m_Callbacks->OnKeyDown(wParam);
            }
            break;
        case WM_KEYUP:
            if (window && window->m_Callbacks && window->m_Callbacks->OnKeyUp) {
                window->m_Callbacks->OnKeyUp(wParam);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

GLLayerView::GLLayerView() {
    m_display = nullptr;  // Initialize display (HMONITOR)
    m_GLWindow = nullptr; // Initialize pointer to GLWindow
    m_savedContext = nullptr;  // Initialize OpenGL context
    m_cursor = LoadCursor(nullptr, IDC_ARROW);  // Load default cursor
}

int GLLayerView::initWithFrame(RECT frame, GLWindow *window) {
    m_GLWindow = window;
    // Set up OpenGL context or initialize the view here
    // Example: set window size or create OpenGL resources
    return 0; // Return success
}

void GLLayerView::keyDown(WPARAM keyCode) {
    // Handle key down event (use keyCode to determine which key was pressed)
    std::cout << "Key down: " << keyCode << std::endl;
}

void GLLayerView::keyUp(WPARAM keyCode) {
    // Handle key up event
    std::cout << "Key up: " << keyCode << std::endl;
}

void GLLayerView::mouseDown(WPARAM button, LPARAM coords) {
    // Handle mouse down event (button indicates which button, coords contains the mouse position)
//    int x = GET_X_LPARAM(coords);
//    int y = GET_Y_LPARAM(coords);
//    std::cout << "Mouse down at (" << x << ", " << y << ")" << std::endl;
}

void GLLayerView::mouseDragged(LPARAM coords) {
    // Handle mouse dragging (moving with button pressed)
//    int x = GET_X_LPARAM(coords);
//    int y = GET_Y_LPARAM(coords);
//    std::cout << "Mouse dragged at (" << x << ", " << y << ")" << std::endl;
}

void GLLayerView::mouseMoved(LPARAM coords) {
    // Handle mouse moved event (without pressing any buttons)
//    int x = GET_X_LPARAM(coords);
//    int y = GET_Y_LPARAM(coords);
//    std::cout << "Mouse moved at (" << x << ", " << y << ")" << std::endl;
}

void GLLayerView::mouseUp(WPARAM button, LPARAM coords) {
    // Handle mouse up event
//    int x = GET_X_LPARAM(coords);
//    int y = GET_Y_LPARAM(coords);
//    std::cout << "Mouse up at (" << x << ", " << y << ")" << std::endl;
}

void GLLayerView::rightMouseDown(LPARAM coords) {
//    int x = GET_X_LPARAM(coords);
//    int y = GET_Y_LPARAM(coords);
//    std::cout << "Right mouse button down at (" << x << ", " << y << ")" << std::endl;
}

void GLLayerView::rightMouseDragged(LPARAM coords) {
//    int x = GET_X_LPARAM(coords);
//    int y = GET_Y_LPARAM(coords);
//    std::cout << "Right mouse button dragged at (" << x << ", " << y << ")" << std::endl;
}

void GLLayerView::rightMouseUp(LPARAM coords) {
//    int x = GET_X_LPARAM(coords);
//    int y = GET_Y_LPARAM(coords);
//    std::cout << "Right mouse button up at (" << x << ", " << y << ")" << std::endl;
}

void GLLayerView::scrollWheel(WPARAM wParam, LPARAM lParam) {
    int delta = GET_WHEEL_DELTA_WPARAM(wParam);
    std::cout << "Mouse wheel scrolled: " << delta << std::endl;
}

void GLLayerView::drawRect(RECT dirtyRect) {
    // Handle drawing within the dirtyRect using OpenGL or GDI (OpenGL preferred for cross-platform)
    // OpenGL rendering can be done here.
    std::cout << "Drawing rectangle (" << dirtyRect.left << ", " << dirtyRect.top << ", "
              << dirtyRect.right << ", " << dirtyRect.bottom << ")" << std::endl;

    // Example OpenGL rendering (requires OpenGL context setup)
    // glClear(GL_COLOR_BUFFER_BIT);
    // SwapBuffers(m_GLWindow->m_hdc);  // Swap OpenGL buffers if using double buffering
}

void GLLayerView::viewDidChangeBackingProperties() {
    // Handle backing properties change, like DPI awareness
    std::cout << "Backing properties changed" << std::endl;
}

void GLLayerView::viewDidEndLiveResize() {
    // Handle the end of a live resize operation
    std::cout << "View finished resizing" << std::endl;
}

void GLLayerView::update() {
    // Handle view update (usually for redrawing or refreshing content)
    std::cout << "View update called" << std::endl;
    // Redraw the window or refresh the contents
    RECT rect;
    GetClientRect(m_GLWindow->m_Window, &rect);
    drawRect(rect);  // Call drawRect to redraw the entire client area
}
