#pragma once


#include "Graphic/CGxDevice.h"
#include "GLWindow.h"
#include "GLDevice.h"
#include <NTempest/CRect.h>

using namespace NTempest;

class CGxBatch;

class CGxShader;

class CGxDeviceGLL : public CGxDevice {
public:
    // Static variables
    static GLEnum s_glCubeMapFaces[];
    static GLEnum s_glDstBlend[];
    static GLEnum s_glSrcBlend[];
    static GLTextureFormat s_gxTexFmtToGLLFmt[];
    static GLEnum s_poolTarget2BufferFormat[];
    static GLEnum s_poolTarget2BufferType[];
    static GLEnum s_poolUsage2BufferUsage[];
    static GLEnum s_primitiveConversion[];

    // Member variables
    HWND m_hwnd = nullptr;
    ATOM m_hwndClass;
    GLDevice m_glDevice;
    GLWindow *m_glWindow;
    GLVertexFormat m_glFormats[GxVertexBufferFormats_Last] = {};

    // Virtual member functions
    virtual void ITexMarkAsUpdated(CGxTex *);

    virtual void IRsSendToHw(EGxRenderState);

    virtual int32_t
    DeviceCreate(int32_t (*windowProc)(void *window, uint32_t message, uintptr_t wparam, intptr_t lparam),
                 const CGxFormat &);

    virtual int32_t DeviceSetFormat(const CGxFormat &);

    virtual void *DeviceWindow();

    virtual void DeviceWM(EGxWM wm, uintptr_t param1, uintptr_t param2) {};

    virtual void CapsWindowSize(CRect &);

    virtual void CapsWindowSizeInScreenCoords(CRect &dst);

    virtual void ScenePresent();

    virtual void SceneClear(uint32_t, CImVector);

    virtual void XformSetProjection(const C44Matrix &);

    virtual void XformSetView(const C44Matrix &);

    virtual void Draw(CGxBatch *batch, int32_t indexed);

    virtual void PoolSizeSet(CGxPool *, uint32_t);

    virtual char *BufLock(CGxBuf *);

    virtual int32_t BufUnlock(CGxBuf *, uint32_t);

    virtual void BufData(CGxBuf *buf, const void *data, size_t size, uintptr_t offset);

    virtual void TexDestroy(CGxTex *texId);

    virtual void IShaderCreate(CGxShader *);

    virtual void ShaderCreate(CGxShader *[], EGxShTarget, const char *, const char *, int32_t);

    virtual int32_t StereoEnabled();

    // Member functions
    CGxDeviceGLL();

    char *IBufLock(CGxBuf *);

    int32_t IBufUnlock(CGxBuf *);

    void ISceneBegin();

    void ISetCaps(const CGxFormat &format);

    void IShaderBindPixel(CGxShader *);

    void IShaderBindVertex(CGxShader *);

    void IShaderConstantsFlush();

    void IShaderCreatePixel(CGxShader *);

    void IShaderCreateVertex(CGxShader *);

    void IStateSetGLLDefaults();

    void IStateSync();

    void IStateSyncEnables();

    void IStateSyncIndexPtr();

    void IStateSyncLights();

    void IStateSyncMaterial();

    void IStateSyncScissorRect();

    void IStateSyncVertexPtrs();

    void IStateSyncXforms();

    void ITexCreate(CGxTex *);

    void ITexSetFlags(CGxTex *);

    void ITexUpload(CGxTex *);

    void IXformSetProjection(const C44Matrix &);

    void IXformSetView(const C44Matrix &);

    void IXformSetViewport();

    void PatchPixelShader(CGxShader *);

    void PatchVertexShader(CGxShader *);

    void Resize(uint32_t width, uint32_t height);
};


