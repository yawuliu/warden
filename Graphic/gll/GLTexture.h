#pragma once

#include "GL.h"
#include "GLObject.h"
#include "GLTypes.h"
#include "Storm/Thread.h"
#include <list>
#include <vector>
#include <atomic>


#define GLTFLAG_RENDERTARGET 0x1
#define GLTFLAG_DEPTH 0x2
#define GLTFLAG_STENCIL 0x4
#define GLTFLAG_AUTOGEN_MIPMAP 0x8
#define GLTFLAG_READ_ACCESS 0x10
#define GLTFLAG_SYSTEM_BUFFER 0x20

class CGxTex;

class GLMipmap;

class GLDevice;

class GLTexture : public GLObject {
public:
    // Types
    struct Binding {
        uint8_t boundStages[16];
        GLDevice *device;
    };

    // Static variables
    static Blizzard::Thread::TLSSlot m_Bindings[4];

    // Static functions
    static void *CreateBindings(void *);

    static void DestroyBindings(void *);

    // Member variables
    uint32_t m_TextureID = 0;
    GLEnum m_TextureType = 0;
    GLMipmap **m_Mipmaps = nullptr;
    std::list<GLTexture *>::iterator var7;
    uint32_t m_LastFrameUsed;
    uint32_t m_Width = 0;
    uint32_t m_Height = 0;
    uint32_t m_Depth = 0;
    uint32_t var12 = 0;
    uint32_t m_Size = 0;
    GLTextureFormat m_Format = GLTF_INVALID;
    uint32_t m_Flags = 0;
    uint32_t m_NumMipmap = 0;
    uint32_t m_RequestedNumMipmaps;
    char *m_Data = nullptr;
    std::atomic<int32_t> m_MappedMipmaps = {0};
    GLStates::Sampler m_Sampler;
    bool m_GenerateMipmaps = 0;
    int32_t m_MaxMipmapLevel = 1000;
    int32_t m_BaseMipmapLevel = 0;
    int32_t m_CompareMode = 0;

    // Member functions
    void Bind(GLDevice *, bool);

    void FreeTexture();

    std::vector<Binding> &GetBindings(); // invented name
    GLTextureFormat GetFormat();

    TextureFormatInfo &GetFormatInfo();

    GLMipmap *GetMipmap(uint32_t, GLEnum);

    bool IsRenderTarget();

    bool IsSystemBuffer();

    bool IsValid();

    void *Map(uint32_t, const GLRect *, uint32_t &, GLEnum);

    void RecreateGLTexture();

    void ResizeMipmaps();

    void SetAddressModeR(GLEnum);

    void SetAddressModeS(GLEnum);

    void SetAddressModeT(GLEnum);

    void SetBorderColor(const GLColor4f &);

    void SetCompareMode(GLEnum);

    void SetMagFilterMode(GLEnum);

    void SetMaxAnisotropy(int32_t);

    void SetMinFilterMode(GLEnum);

    void SetupTexture();

    void Unbind(GLDevice *, uint32_t); // invented name
    void Unmap(uint32_t level, GLEnum face);
};

class GLTexture2D : public GLTexture {
public:
    // Static functions
    static GLTexture2D *Create(uint32_t, uint32_t, uint32_t, GLTextureFormat, uint32_t);

    // Virtual member functions
    virtual void ReleaseObject();

    // Member functions
    GLTexture2D();
};

void GLLTexSetFlags(CGxTex *, GLTexture *);


