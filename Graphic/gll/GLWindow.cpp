#include "GLWindow.h"
#include "GLContext.h"
#include "Storm/Autorelease.h"
#include "Storm/Debug.h"
#include <cmath>
#include <QOpenGLWindow>
#include <QScreen>
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

GLWindow::GLWindow(QScreen *primaryScreen, GLWindowCallbacks *callbacks) {
    this->SetCallbacks(callbacks);
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

void GLWindow::SetOpenGLContext(QOpenGLContext *context) {
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
//now another test:
//the next line prints: "Window format version is: 4.2" which is correct
    qDebug() << "Window format version is: " << this->format().majorVersion() << "." << this->format().minorVersion();
//the next line prints: "Context format version is: 2.0" Which is ofcourse not correct! WTF?
    qDebug() << "Context format version is: " << m_Context->format().majorVersion() << "."
             << m_Context->format().minorVersion();
}







