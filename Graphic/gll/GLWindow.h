#pragma once


#include "GLAbstractWindow.h"
#include "CGRect.h"
#include "GLLayerView.h"
#include <string>


struct GLWindowCallbacks {
    void (*OnResized)(int32_t, int32_t, bool);

    void (*OnMouseDown)(int16_t, int32_t, int32_t);

    void (*OnMouseMoved)(int32_t, int32_t);

    void (*OnMouseUp)(int16_t, int32_t, int32_t);

    void (*OnKeyDown)(WPARAM);  // Using WPARAM for key codes
    void (*OnKeyUp)(WPARAM);
};

class GLWindow : public GLAbstractWindow {
public:
//    // Member variables
//    // void** var0; // _vptr$GLAbstractWindow
    HGLRC m_Context = nullptr;
    HWND m_Window = nullptr;
    bool m_Shown = false;
//    GLLayerView *m_View = nullptr;
    std::string m_ViewClass;
    GLAbstractWindow *m_FullscreenWindow = nullptr;
    GLWindowCallbacks *m_Callbacks;
    GLWindowCallbacks *m_ActiveCallbacks;
    RECT m_WindowedRect;

    // Member functions
    bool CanEnterFullscreenMode();

    void CreateView();

    NTempest::CRect GetBackingRect();

    HWND GetNSView();

    NTempest::CRect GetRect();

    void EnterFullscreenMode();

    void ExitFullscreenMode();

    void Init(const NTempest::CRect &, GLWindowCallbacks *);

    void Resize(uint32_t, uint32_t);

    void SetOpenGLContext(HGLRC context);

    void SetViewClass(const std::string &viewClass);

    void Show();

    // Virtual member functions
    virtual void SetCallbacks(GLWindowCallbacks *);

    virtual void SetTitle(const char *);

    int32_t GetWidth(void) override;

    int32_t GetHeight(void) override;

    void SetOpenGLContext(GLContext *context) override;

    int32_t GetBackingWidth() override;

    int32_t GetBackingHeight() override;
};


