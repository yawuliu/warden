#include "GLContext.h"
#include "Graphic/gll/GLDevice.h"
#include "Storm/Debug.h"


GLContext *GLContext::s_MainContext;
Blizzard::Thread::TLSSlot GLContext::s_CurrentContext;
Blizzard::Thread::TLSSlot GLContext::s_CurrentGLContext;
int GLContext::s_DesktopMode;

// https://github.com/bkaradzic/bgfx/blob/932302d8f460e514b933deba8c0e575a00f0bcd6/src/glcontext_wgl.cpp
// https://github.com/CrossVR/dolphin/blob/90500ed90ee4d0fa7937442f8273314d15d33799/Source/Core/Common/GL/GLInterface/WGL.cpp
// https://github.com/quyse/inanity/blob/415cc7f45dde03722161cf6bd1e13f5986507699/graphics/GlContext.cpp#L59

GLContext *GLContext::GetNSOpenGLCurrentContext() {
    return s_MainContext;
}

GLContext *GLContext::GetCurrentContext() {
    return s_MainContext;
}

void GLContext::SetCurrentContext(GLContext *context) {
    s_MainContext = context;
}

GLContext *GLContext::GetCurrentGLContext() {
    return s_MainContext;
}

void GLContext::SetCurrentGLContext(GLContext *context) {
    s_MainContext = context;
}

GLContext::GLContext(GLDevice *a2, const char *a3) {
    this->m_Context = nullptr;
    this->m_Window = nullptr;
    this->m_Windowed = false;
    this->m_MTGLEnabled = false;
    this->m_Device = a2;
    this->m_Width = 0;
    this->m_Height = 0;
    this->m_RefreshRate = 0;
}

int32_t GLContext::GetBackingWidth() {
    if (this->m_Windowed) {
        return this->m_Window->width();
    } else {
        return this->m_Width;
    }
}

int32_t GLContext::GetBackingHeight() {
    if (this->m_Windowed) {
        return this->m_Window->height();
    } else {
        return this->m_Height;
    }
}

int32_t GLContext::GetWidth() {
    if (this->m_Windowed) {
        return this->m_Window->width();
    } else {
        return this->m_Width;
    }
}

int32_t GLContext::GetHeight() {
    if (this->m_Windowed) {
        return this->m_Window->height();
    } else {
        return this->m_Height;
    }
}

bool GLContext::IsCurrentContext() {
    return GLContext::GetCurrentGLContext() == this;
}

void GLContext::MakeCurrent(bool a2) {
    BLIZZARD_ASSERT(this->m_Context != nullptr);

    if (a2) {
        GLContext *v6 = GLContext::GetNSOpenGLCurrentContext();
        GLContext::SetCurrentContext(v6);
    }

    if (this->m_Context != GLContext::GetCurrentContext()) {
        int32_t mtglEnabled = 0;
        GLDevice *device = GLDevice::Get();
        if (GLContext::GetCurrentContext() && device) {
            mtglEnabled = this->m_MTGLEnabled;
            device->glFlush();
        }
        this->m_Context->makeCurrent(this->surface());

        GLContext::SetCurrentContext(this->m_Context);
        GLContext::SetCurrentGLContext(this);


        if (device) {
            device->ApplyGLStates(device->m_States, 1);
            device->ApplyGLBindings(device->m_States, 1);
            device->m_DefaultVertexArrayObject.ApplyGLStates(device->m_DefaultVertexArrayObject.m_GLStates);
        }
    }
}

void GLContext::SetContextFormat(GLTextureFormat a2, uint32_t sampleCount) {
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(4, 5); // 设置 OpenGL 版本为 4.5
    format.setProfile(QSurfaceFormat::CoreProfile); // 核心模式
    format.setSamples(sampleCount); // 设置多重采样数
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer); // 双缓冲

    setFormat(format);

    if (this->m_Window) {
        this->m_Window->SetOpenGLContext(this);
    }

    if (this->m_Context != GLContext::GetCurrentContext()) {
        this->MakeCurrent(false);
    }
}

void GLContext::SetFullscreenMode(uint32_t, uint32_t, uint32_t, bool) {
    this->m_Window->showFullScreen();
}

void GLContext::SetWindow(GLAbstractWindow *pWindow, bool show) {
    if (!pWindow) {
        if (this->m_Window) {
            this->m_Window->SetOpenGLContext(nullptr);
        }

        this->m_Window = nullptr;
        return;
    }

    if (this->m_Windowed && pWindow == this->m_Window) {
        if (show) {
            pWindow->show();
        }
        return;
    }

    if (this->m_Window) {
        if (this->m_Windowed && pWindow != this->m_Window) {
            this->m_Window = pWindow;
            this->m_Window->SetOpenGLContext(this);
            return;
        }
    }
}

void GLContext::Swap() {
    this->m_Context->swapBuffers(this->m_Window);
}


