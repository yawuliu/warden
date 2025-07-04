#include "GLWindow.h"
#include "GLContext.h"
#include "Storm/Autorelease.h"
#include "Storm/Debug.h"
#include <cmath>
//#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QDebug>


GLWindowCallbacks DefaultCallbacks = {
        // TODO
};

bool GLWindow::CanEnterFullscreenMode() {
    return true;
}


void GLWindow::EnterFullscreenMode() {
    m_FullscreenWindow = this;
    this->showFullScreen();
}

void GLWindow::ExitFullscreenMode() {
    if (m_FullscreenWindow) {
        this->showNormal();
        m_FullscreenWindow = nullptr;
    }
}

GLWindow::GLWindow( GLWindowCallbacks *callbacks) {//QScreen *primaryScreen,
    this->SetCallbacks(callbacks);
}

CRect GLWindow::GetRect(void) {
    return CRect();
}

void GLWindow::Show(void) {

}

void GLWindow::Resize(uint32_t uint32, uint32_t uint321) {

}

void GLWindow::SetTitle(const char *string) {

}

void GLWindow::CreateView(void) {

}

HWND GLWindow::GetNSView(void) {
    return nullptr;
}

CRect GLWindow::GetBackingRect() {
    return CRect();
}

void GLWindow::SetCallbacks(GLWindowCallbacks *callbacks) {
    if (callbacks) {
        this->m_Callbacks = callbacks;
        this->m_ActiveCallbacks = callbacks;
    } else {
        this->m_Callbacks = &DefaultCallbacks;
        this->m_ActiveCallbacks = &DefaultCallbacks;
    }
}

void GLWindow::SetOpenGLContext(GLContext *context) {
    setSurfaceType(OpenGLSurface);

    QSurfaceFormat fmt;
    fmt.setMajorVersion(4);
    fmt.setMinorVersion(2);
    fmt.setProfile(QSurfaceFormat::CoreProfile); //whatever this is

    this->setFormat(fmt);

    m_Context = context;
    m_Context->setFormat(fmt);

    m_Context->create();

    if (!m_Context->isValid()) {
        qCritical() << "The OpenGL context is invalid!"; //I allways get this message
    }

    qDebug() << "Window format version is: " << this->format().majorVersion() << "." << this->format().minorVersion();
    qDebug() << "Context format version is: " << m_Context->format().majorVersion() << "."
             << m_Context->format().minorVersion();
}

int32_t GLWindow::GetWidth(void) {
    return 0;
}

int32_t GLWindow::GetHeight(void) {
    return 0;
}

int32_t GLWindow::GetBackingWidth() {
    return 0;
}

int32_t GLWindow::GetBackingHeight() {
    return 0;
}







