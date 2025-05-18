#include "GLContext.h"
#include "Graphic/gll/GLDevice.h"
#include "Storm/Debug.h"
#include "glad/glad.h"

GLContext *GLContext::s_MainContext;
Blizzard::Thread::TLSSlot GLContext::s_CurrentContext;
Blizzard::Thread::TLSSlot GLContext::s_CurrentGLContext;
int GLContext::s_DesktopMode;

// https://github.com/bkaradzic/bgfx/blob/932302d8f460e514b933deba8c0e575a00f0bcd6/src/glcontext_wgl.cpp
// https://github.com/CrossVR/dolphin/blob/90500ed90ee4d0fa7937442f8273314d15d33799/Source/Core/Common/GL/GLInterface/WGL.cpp
// https://github.com/quyse/inanity/blob/415cc7f45dde03722161cf6bd1e13f5986507699/graphics/GlContext.cpp#L59

QOpenGLContext *GLContext::GetNSOpenGLCurrentContext() {
    return QOpenGLContext::currentContext();
}

QOpenGLContext *GLContext::GetCurrentContext() {
    return GLContext::s_CurrentContext;
}

void GLContext::SetCurrentContext(QOpenGLContext *context) {
    GLContext::s_CurrentContext = context;
}

GLContext *GLContext::GetCurrentGLContext() {
    return GLContext::s_CurrentGLContext;
}

void GLContext::SetCurrentGLContext(GLContext *context) {
    GLContext::s_CurrentGLContext = context;
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
    BLIZZARD_ASSERT(this->m_Context->context != nullptr);

    if (a2) {
        QOpenGLContext *v6 = GLContext::GetNSOpenGLCurrentContext();
        GLContext::SetCurrentContext(v6);
    }

    if (this->m_Context->context != GLContext::GetCurrentContext()) {
        int32_t mtglEnabled = 0;
        GLDevice *device = GLDevice::Get();
        if (GLContext::GetCurrentContext() && device) {
            mtglEnabled = this->m_MTGLEnabled;
            glFlush();
        }
        this->m_Context->context->makeCurrent(this->m_Window);

        GLContext::SetCurrentContext(this->m_Context->context);
        GLContext::SetCurrentGLContext(this);


        if (device) {
            device->ApplyGLStates(device->m_States, 1);
            device->ApplyGLBindings(device->m_States, 1);
            device->m_DefaultVertexArrayObject.ApplyGLStates(device->m_DefaultVertexArrayObject.m_GLStates);
        }
    }
}

void GLContext::SetContextFormat(GLTextureFormat textureFormat, uint32_t sampleCount) {
    uint32_t key = sampleCount | (static_cast<uint32_t>(textureFormat) << 8);

    // 尝试查找已存在的上下文配置
    if (m_Contexts.contains(key)) {
        m_Context = &m_Contexts[key];
    } else {
        // 创建新的上下文配置
        auto &contextInfo = m_Contexts[key];
        contextInfo.sampleCount = sampleCount;

        // 配置 QSurfaceFormat
        QSurfaceFormat format;
        format.setVersion(4, 5); // 设置 OpenGL 版本
        format.setProfile(QSurfaceFormat::CoreProfile);
        format.setSwapInterval(0); // 设置 V-sync 等参数

        // 根据 GLTextureFormat 设置深度和模板缓冲区大小
        switch (textureFormat) {
            case GLTF_INVALID:
                // 不设置深度和模板缓冲区
                break;
            case GLTF_D32:
                format.setDepthBufferSize(32);
                break;
            case GLTF_D24:
                format.setDepthBufferSize(24);
                break;
            case GLTF_D16:
                format.setDepthBufferSize(16);
                break;
            case GLTF_D24S8:
                format.setDepthBufferSize(24);
                format.setStencilBufferSize(8);
                break;
            default:
                // 处理未知格式，可抛出异常或返回错误等
                break;
        }

        // 设置多重采样
        if (sampleCount > 1) {
            format.setSamples(sampleCount);
        }

        // 创建 QOpenGLContext
        contextInfo.context = new QOpenGLContext();
        contextInfo.context->setFormat(format);
        // 如果需要共享上下文，可以指定共享的上下文
        contextInfo.context->setShareContext(s_MainContext);
        bool createContext = contextInfo.context->create();
        if (!createContext) {
            // 处理创建失败的情况
        }

        // 将创建好的上下文信息保存
        contextInfo.pixelFormat = &format;
        m_Context = &contextInfo;
    }

    // 将上下文设置为当前上下文
    if (m_Context->context != GLContext::GetCurrentContext()) {
        MakeCurrent(0);
    }
}

void GLContext::SetFullscreenMode(uint32_t, uint32_t, uint32_t, bool) {
    this->m_Window->show();
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
    this->m_Context->context->swapBuffers(this->m_Window);
}

void GLContext::Update() {
    this->m_Context->context->swapBuffers(this->m_Window);
}

