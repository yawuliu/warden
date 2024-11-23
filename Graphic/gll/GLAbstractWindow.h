#pragma once


#include <cstdint>
#include <windows.h>
#include <QOpenGLContext>
#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include "NTempest/CRect.h"

class GLAbstractWindow : public QOpenGLWindow {
public:
    // Virtual member functions
    virtual void SetOpenGLContext(QOpenGLContext *) = 0;
};


