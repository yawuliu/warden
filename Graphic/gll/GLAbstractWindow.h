#pragma once


#include <cstdint>
#include <windows.h>
#include <QWindow>
#include "NTempest/CRect.h"
using namespace NTempest;
class GLContext;

class GLAbstractWindow: public QWindow  {//
public:
    // Virtual member functions
    virtual int32_t GetWidth(void)= 0;
    virtual int32_t GetHeight(void)= 0;
    virtual CRect GetRect(void) = 0;
    virtual void Show(void) = 0;
    virtual void Resize(uint32_t, uint32_t) = 0;
    virtual void SetTitle(const char*) = 0;
    virtual void CreateView(void) = 0;
    virtual void SetOpenGLContext(GLContext*) = 0;
    // virtual NSWindow* GetNSWindow(void) = 0;
    virtual HWND GetNSView(void) = 0;
    virtual bool CanEnterFullscreenMode(void) = 0;
    // virtual void EnterFullscreenMode(uint32_t, bool) = 0;
    virtual void ExitFullscreenMode(void) = 0;
    virtual CRect GetBackingRect() = 0;
    virtual int32_t GetBackingWidth()= 0;
    virtual int32_t GetBackingHeight()= 0;
};


