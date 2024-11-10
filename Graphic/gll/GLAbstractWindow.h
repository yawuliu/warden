#pragma once


#include <cstdint>
#include <windows.h>

#include "NTempest/CRect.h"

class GLContext;

class GLAbstractWindow {
public:
    // Virtual member functions
    virtual int32_t GetWidth();

    virtual int32_t GetHeight();

    virtual NTempest::CRect GetRect() = 0;

    virtual void Show() = 0;

    virtual void Resize(uint32_t, uint32_t) = 0;

    virtual void SetTitle(const char *) = 0;

    virtual void CreateView() = 0;

    virtual void SetOpenGLContext(GLContext *) = 0;

    // virtual NSWindow* GetNSWindow() = 0;
    virtual HWND GetNSView() = 0;

    virtual bool CanEnterFullscreenMode() = 0;

    // virtual void EnterFullscreenMode(uint32_t, bool) = 0;
    virtual void ExitFullscreenMode() = 0;

    virtual NTempest::CRect GetBackingRect() = 0;

    virtual int32_t GetBackingWidth();

    virtual int32_t GetBackingHeight();
};


