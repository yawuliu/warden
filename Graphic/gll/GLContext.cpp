#include "GLContext.h"
#include "Graphic/gll/GLDevice.h"
#include "Storm/Debug.h"
#include "Storm/Autorelease.h"
#include "opengl/wglext.h"


WGLContext *GLContext::s_MainContext;
Blizzard::Thread::TLSSlot GLContext::s_CurrentContext;
Blizzard::Thread::TLSSlot GLContext::s_CurrentGLContext;
int GLContext::s_DesktopMode;

// https://github.com/bkaradzic/bgfx/blob/932302d8f460e514b933deba8c0e575a00f0bcd6/src/glcontext_wgl.cpp
// https://github.com/CrossVR/dolphin/blob/90500ed90ee4d0fa7937442f8273314d15d33799/Source/Core/Common/GL/GLInterface/WGL.cpp
// https://github.com/quyse/inanity/blob/415cc7f45dde03722161cf6bd1e13f5986507699/graphics/GlContext.cpp#L59
void *NewHGLRC(void *ptr) {
    HGLRC *ptrptr = new HGLRC;
    *ptrptr = nullptr;
    return ptrptr;
}

void DeleteHGLRC(void *ptr) {
    delete static_cast<HGLRC *>(ptr);
}

void *NewGLContext(void *ptr) {
    GLContext **ptrptr = new GLContext *;
    *ptrptr = nullptr;
    return ptrptr;
}

void DeleteGLContext(void *ptr) {
    delete static_cast<GLContext **>(ptr);
}

GLContext::Context::~Context() {
    if (this->context) {
        glFlush();


        // Unbind the current OpenGL rendering context
        this->context->clearCurrentContext();

        // Delete the OpenGL rendering context
        this->context->destroy();
        this->context = nullptr;


        if (GLContext::GetCurrentContext() == context) {
            // NSOpenGLContext->clearCurrentContext();
            GLContext::SetCurrentContext(nullptr);
        }
        // this->context->release();
    }
//
//    this->pixelFormat->release();
}

HGLRC GLContext::GetNSOpenGLCurrentContext() {
    return wglGetCurrentContext();
}

WGLContext *GLContext::GetCurrentContext() {
    return *static_cast<WGLContext **>(
            Blizzard::Thread::RegisterLocalStorage(&GLContext::s_CurrentContext, NewHGLRC, 0, DeleteHGLRC)
    );
}

void GLContext::SetCurrentContext(WGLContext *context) {
    *static_cast<WGLContext **>(
            Blizzard::Thread::RegisterLocalStorage(&GLContext::s_CurrentContext, NewHGLRC, 0, DeleteHGLRC)
    ) = context;
}

GLContext *GLContext::GetCurrentGLContext() {
    return *static_cast<GLContext **>(
            Blizzard::Thread::RegisterLocalStorage(&GLContext::s_CurrentGLContext, NewGLContext, 0, DeleteGLContext)
    );
}

void GLContext::SetCurrentGLContext(GLContext *context) {
    *static_cast<GLContext **>(
            Blizzard::Thread::RegisterLocalStorage(&GLContext::s_CurrentGLContext, NewGLContext, 0, DeleteGLContext)
    ) = context;
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
        return this->m_Window->GetBackingHeight();
    } else {
        return this->m_Height;
    }
}

int32_t GLContext::GetBackingHeight() {
    if (this->m_Windowed) {
        return this->m_Window->GetBackingHeight();
    } else {
        return this->m_Height;
    }
}

int32_t GLContext::GetWidth() {
    if (this->m_Windowed) {
        return this->m_Window->GetWidth();
    } else {
        return this->m_Width;
    }
}

int32_t GLContext::GetHeight() {
    if (this->m_Windowed) {
        return this->m_Window->GetHeight();
    } else {
        return this->m_Height;
    }
}

bool GLContext::IsCurrentContext() {
    return GLContext::GetCurrentGLContext() == this;
}

void GLContext::MakeCurrent(bool a2) {
    BLIZZARD_ASSERT(this->m_Context->context != nullptr);

    //if (a2) {
    //    HGLRC v6 = GLContext::GetNSOpenGLCurrentContext();
    //    GLContext::SetCurrentContext(v6);
    //}

    if (this->m_Context->context != GLContext::GetCurrentContext()) {
        int32_t mtglEnabled = 0;

        if (GLContext::GetCurrentContext()) {
            mtglEnabled = this->m_MTGLEnabled;

            // TODO
            // this->ToggleMTGL(0);
            // GLOcclusionQuery::DeleteAllQueries();
            // GLFence::DeleteAllFences();

            glFlush();
        }
        wglMakeCurrent(this->m_Context->context->m_hdc, this->m_Context->context->m_hglrc);

        GLContext::SetCurrentContext(this->m_Context->context);
        GLContext::SetCurrentGLContext(this);

        // TODO
        // GLOcclusionQuery::RecreateAllQueries();
        // GLFence::RecreateAllFences();
        // this->ToggleMTGL(mtglEnabled);

        GLDevice *device = GLDevice::Get();

        if (device && this->m_Contexts.size() > 1) {
            device->ApplyGLStates(device->m_States, 1);
            device->ApplyGLBindings(device->m_States, 1);
            device->m_DefaultVertexArrayObject.ApplyGLStates(device->m_DefaultVertexArrayObject.m_GLStates);
        }
    }
}

void GLContext::SetContextFormat(GLTextureFormat a2, uint32_t sampleCount) {
    System_Autorelease::ScopedPool autorelease;

    uint32_t v61 = sampleCount | (a2 << 8);

    if (this->m_Contexts.find(v61) != this->m_Contexts.end()) {
        this->m_Context = &this->m_Contexts[v61];

        if (this->m_Window) {
            this->m_Window->SetOpenGLContext(this);
        }
    } else {
        auto &context = this->m_Contexts[v61];

        int v6 = 0;// CGMainDisplayID();

        int formatAttributes[] = {
                WGL_DOUBLE_BUFFER_ARB,
                WGL_NO_RESET_NOTIFICATION_ARB,
                WGL_GENERIC_ACCELERATION_ARB,
                WGL_DEPTH_BITS_ARB, 8,
                WGL_STENCIL_BITS_ARB, 8,
                WGL_COLOR_BITS_ARB, 32,
                WGL_DRAW_TO_WINDOW_ARB,
                WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
                0, 0, 0, 0, 0
        };
//
        switch (a2) {
            case GLTF_INVALID:
                break;

            case GLTF_D32:
                formatAttributes[4] = 32;
                break;

            case GLTF_D24:
                formatAttributes[4] = 24;
                break;

            case GLTF_D16:
                formatAttributes[4] = 16;
                break;

            case GLTF_D24S8:
                formatAttributes[4] = 24;
                formatAttributes[6] = 8;
                break;

            default:
            BLIZZARD_ASSERT(false);
                break;
        }

        if (sampleCount > 1) {
            BLIZZARD_ASSERT(sampleCount % 2 == 0);
            BLIZZARD_ASSERT(formatAttributes[13] == 0);
            BLIZZARD_ASSERT(formatAttributes[14] == 0);
            BLIZZARD_ASSERT(formatAttributes[15] == 0);
            BLIZZARD_ASSERT(formatAttributes[16] == 0);
            BLIZZARD_ASSERT(formatAttributes[17] == 0);

            formatAttributes[13] = WGL_SAMPLE_BUFFERS_ARB;
            formatAttributes[14] = 1;
            formatAttributes[15] = WGL_SAMPLES_ARB;
            formatAttributes[16] = sampleCount;
        }

        context.sampleCount = sampleCount;

//        context.pixelFormat = NSOpenGLPixelFormat->alloc();
//        initWithAttributes:
//        formatAttributes;
//
//
//        BLIZZARD_ASSERT(context.pixelFormat != nullptr);

        context.context = new WGLContext(this->m_Window->GetNSView());
        initWithFormat:
        context.pixelFormat;
        shareContext:
        GLContext::s_MainContext;


        BLIZZARD_ASSERT(context.context != nullptr);

        this->m_Context = &context;

//        auto contextObj = context.context->CGLContextObj;
//
//        int32_t vsyncEnabled = this->m_VSyncEnabled;
//        CGLSetParameter(contextObj, kCGLCPSwapInterval, &vsyncEnabled);
//
//        auto result = this->m_MTGLEnabled
//                      ? CGLEnable(contextObj, kCGLCEMPEngine)
//                      : CGLDisable(contextObj, kCGLCEMPEngine);
//        BLIZZARD_ASSERT(result == kCGLNoError);

        if (this->m_Window) {
            this->m_Window->SetOpenGLContext(this);
        }
    }

    if (this->m_Context->context != GLContext::GetCurrentContext()) {
        this->MakeCurrent(false);
    }
}

void GLContext::SetFullscreenMode(uint32_t, uint32_t, uint32_t, bool) {
// TODO
}

void GLContext::SetWindow(GLAbstractWindow *a2, bool a3) {
    if (!a2) {
        if (this->m_Window) {
            this->m_Window->SetOpenGLContext(nullptr);
        }

        this->m_Window = nullptr;

        return;
    }

    if (this->m_Windowed && a2 == this->m_Window) {
        if (a3) {
            a2->Show();
        }

        return;
    }

    HWND v5;

    if (this->m_Window) {
        v5 = this->m_Window->GetNSView();

        if (v5 && this->m_Windowed && a2 != this->m_Window) {
            this->m_Window = a2;
            this->m_Window->SetOpenGLContext(this);

            return;
        }
    } else {
        v5 = nullptr;
    }

    this->m_Window = a2;

    if (!a2->GetNSView()) {
        this->m_Window->CreateView();
    }

    //float v15;
    //bool v16 = false;
    //int v17 = 0;

    //if (v5 && GLDevice::GetRendererInfo().unk100 > 2639 && this->m_Window->CanEnterFullscreenMode()) {
    //    if (!this->m_Windowed) {
    //        if (!GLContext::s_DesktopMode) {
    //            // TODO
    //            // Blizzard::Debug::Assert(
    //            //     "s_DesktopMode",
    //            //     "/Users/Shared/BuildServer/wow2.old/work/WoW-code/branches/wow-patch-3_3_5-BNet/WoW/Source/Mac/../../../"
    //            //     "Engine/Source/Gx/CGxDeviceGLL/GLLayer/GLContext.cpp",
    //            //     215
    //            // );
    //        }

    //        v15 = 1.25;
    //        v16 = false;
    //        int v8 = 0;

    //        CGError v7 = CGAcquireDisplayFadeReservation(2.25, &v17);

    //        if (!v7) {
    //            v8 = v17;
    //        }

    //        v17 = v8;

    //        if (v8) {
    //            v16 = CGDisplayFade(v8, 0.25, 0, 1.0, 0, 0, 0, 1) == kCGErrorSuccess;
    //        }

    //        int v10 = CGMainDisplayID();
    //        CGDisplaySwitchToMode(v10, GLContext::s_DesktopMode);

    //        this->m_Window->ExitFullscreenMode();

    //        // TODO
    //        // SetSystemUIMode(0, 0);
    //    }

    //    CGReleaseAllDisplays();
    //}

    //if (a3) {
    //    this->m_Window->Show();
    //}

    //this->m_Windowed = 1;
    //CGDisplayRestoreColorSyncSettings();

    //if (v17) {
    //    if (v16) {
    //        float v6 = v15;

    //        if (v15 > 1.0) {
    //            usleep(1000);
    //            v6 = v15 - 1.0;
    //        }

    //        CGDisplayFade(v17, v6, 1.0, 0, 0, 0, 0, 0);
    //    }

    //    CGReleaseDisplayFadeReservation(v17);
    //}

    return;
}

void GLContext::Swap() {
    this->m_Context->context->flushBuffer();
}

void GLContext::Update() {
    // If the window size has changed, update the OpenGL viewport
    RECT rect;
    GetClientRect(m_Window->GetNSView(), &rect);  // Get new window size
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // Ensure the OpenGL context is still current
    this->m_Context->context->makeCurrentContext();

    // Update the OpenGL viewport to the new window size
    glViewport(0, 0, width, height);
}
