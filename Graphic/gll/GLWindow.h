#pragma once


#include "GLAbstractWindow.h"
#include "CGRect.h"
#include <string>
//#include <QScreen>

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
    GLWindow(GLWindowCallbacks *);//QScreen *primaryScreen,

//    QOpenGLContext *m_Context = nullptr;
    GLAbstractWindow *m_FullscreenWindow = nullptr;
    GLWindowCallbacks *m_Callbacks;
    GLWindowCallbacks *m_ActiveCallbacks;

    // Member functions
    bool CanEnterFullscreenMode();


    void EnterFullscreenMode();

    void ExitFullscreenMode();


    // Virtual member functions
    virtual void SetCallbacks(GLWindowCallbacks *);

    // void SetOpenGLContext() override;//QOpenGLContext *context
    void SetOpenGLContext(GLContext *context) override;

    CRect GetRect(void) override;

    void Show(void) override;

    void Resize(uint32_t uint32, uint32_t uint321) override;

    void SetTitle(const char *string) override;

    void CreateView(void) override;

    HWND GetNSView(void) override;

    CRect GetBackingRect() override;

    int32_t GetWidth(void) override;

    int32_t GetHeight(void) override;

    int32_t GetBackingWidth() override;

    int32_t GetBackingHeight() override;
};


