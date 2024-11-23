#pragma once


#include "GLAbstractWindow.h"
#include "CGRect.h"
#include <string>
#include <QScreen>

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
    GLWindow(QScreen *primaryScreen, GLWindowCallbacks *);

    QOpenGLContext *m_Context = nullptr;
    GLAbstractWindow *m_FullscreenWindow = nullptr;
    GLWindowCallbacks *m_Callbacks;
    GLWindowCallbacks *m_ActiveCallbacks;

    // Member functions
    bool CanEnterFullscreenMode();


    void EnterFullscreenMode();

    void ExitFullscreenMode();


    // Virtual member functions
    virtual void SetCallbacks(GLWindowCallbacks *);

    void SetOpenGLContext(QOpenGLContext *context) override;
};


