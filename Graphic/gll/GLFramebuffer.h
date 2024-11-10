#pragma once


#include <cstdint>
#include "GL.h"
#include "GLObject.h"

#define MAX_ATTACHMENT 6

class GLDevice;

class GLMipmap;

class GLFramebuffer : public GLObject {
public:
    // Static functions
    static GLFramebuffer *Create(bool);

    // Member variables
    int32_t m_Width = 0;
    int32_t m_Height = 0;
    uint32_t m_FramebufferID = 0;
    GLDevice *m_Device;
    GLMipmap *m_Attachments[6] = {};
    uint32_t m_NumAttach = 0;

    // Virtual member functions
    virtual void ReleaseObject();

    // Member functions
    GLFramebuffer(bool);

    void Attach(GLMipmap *, GLenum, int32_t);

    void Detach(GLenum);

    GLMipmap *GetAttachment(GLEnum);

    int32_t GetSampleCount();

    bool IsValid();
};


