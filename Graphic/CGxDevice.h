#pragma once

#include "Buffer.h"
#include "CGxCaps.h"
#include "CGxFormat.h"
#include "CGxMatrixStack.h"
#include "CGxStateBom.h"
#include "Types.h"
#include "Shader.h"
#include <cstdint>
#include "NTempest/C4Vector.h"
#include "NTempest/C3Vector.h"
#include "NTempest/C44Matrix.h"
#include "NTempest/CRect.h"
#include "NTempest/CiRect.h"
#include "NTempest/CBoundingBox.h"
#include "CGxBatch.h"
#include "Graphic/texture/CGxTex.h"

using namespace NTempest;


struct CGxAppRenderState {
    CGxStateBom m_value;
    uint32_t m_stackDepth;
    int32_t m_dirty;
};

struct CGxPushedRenderState {
    EGxRenderState m_which;
    CGxStateBom m_value;
    uint32_t m_stackDepth;
};

struct ShaderConstants {
    C4Vector constants[256];
    uint32_t unk1;
    uint32_t unk2;
};

class CGxDevice {
public:
    // Static variables
    static uint32_t s_alphaRef[];
    static C3Vector s_pointScaleIdentity;
    static uint32_t s_primVtxAdjust[];
    static uint32_t s_primVtxDiv[];
    static ShaderConstants s_shadowConstants[2];
    static uint32_t s_streamPoolSize[];
    static uint32_t s_texFormatBitDepth[];
    static uint32_t s_texFormatBytesPerBlock[];

    // Static functions
    static void Log(const char *format, ...);

    static void Log(const CGxFormat &format);


    static CGxDevice *NewGLL();


    static CGxDevice *NewOpenGl();

    static uint32_t PrimCalcCount(EGxPrim primType, uint32_t count);

    // Member variables
    TSGrowableArray<CGxPushedRenderState> m_pushedStates;
    TSGrowableArray<size_t> m_stackOffsets;
    TSGrowableArray<EGxRenderState> m_dirtyStates;
    CRect m_defWindowRect;
    CRect m_curWindowRect;
    EGxApi m_api = GxApis_Last;
    CGxFormat m_format;
    CGxCaps m_caps;
    TSHashTable<CGxShader, HASHKEY_STRI> m_shaderList[GxShTargets_Last];

    int32_t (*m_windowProc)(void *window, uint32_t message, uintptr_t wparam, intptr_t lparam) = nullptr;

    int32_t m_context = 0;
    int32_t intF5C = 0;
    int32_t m_windowVisible = 0;
    int32_t intF64 = 0;
    int32_t intF6C = 1;
    CBoundingBox m_viewport;
    C44Matrix m_projection;
    C44Matrix m_projNative;
    CGxMatrixStack m_xforms[GxXforms_Last];
    uint32_t m_appMasterEnables = 0;
    uint32_t m_hwMasterEnables = 0;
    TSList<CGxPool, TSGetLink<CGxPool>> m_poolList;
    CGxBuf *m_bufLocked[GxPoolTargets_Last];
    CGxPool *m_vertexPool = nullptr;
    CGxPool *m_indexPool = nullptr;
    CGxBuf *m_streamBufs[GxPoolTargets_Last];
    CGxVertexAttrib m_primVertexFormatAttrib[GxVertexBufferFormats_Last];
    CGxBuf *m_primVertexFormatBuf[GxVertexBufferFormats_Last];
    uint32_t m_primVertexMask = 0;
    uint32_t m_primVertexDirty = 0;
    EGxVertexBufferFormat m_primVertexFormat = GxVertexBufferFormats_Last;
    CGxBuf *m_primVertexBuf = nullptr;
    uint32_t m_primVertexSize;
    CGxBuf *m_primIndexBuf = nullptr;
    int32_t m_primIndexDirty = 0;
    TSFixedArray<CGxAppRenderState> m_appRenderStates;
    TSFixedArray<CGxStateBom> m_hwRenderStates;
    uint32_t m_baseMipLevel = 0; // TODO placeholder

    // Virtual member functions
    virtual void ITexMarkAsUpdated(CGxTex *) = 0;

    virtual void IRsSendToHw(EGxRenderState) = 0;

    virtual void ICursorCreate(const CGxFormat &format);

    virtual int32_t
    DeviceCreate(int32_t (*windowProc)(void *window, uint32_t message, uintptr_t wparam, intptr_t lparam),
                 const CGxFormat &);

    virtual int32_t DeviceSetFormat(const CGxFormat &);

    virtual void *DeviceWindow() = 0;

    virtual void DeviceWM(EGxWM wm, uintptr_t param1, uintptr_t param2) = 0;

    virtual void CapsWindowSize(CRect &) = 0;

    virtual void CapsWindowSizeInScreenCoords(CRect &dst) = 0;

    virtual void ScenePresent();

    virtual void SceneClear(uint32_t, CImVector) {};

    virtual void XformSetProjection(const C44Matrix &);

    virtual void XformSetView(const C44Matrix &);

    virtual void Draw(CGxBatch *batch, int32_t indexed) {};

    virtual void ValidateDraw(CGxBatch *, int32_t);

    virtual void MasterEnableSet(EGxMasterEnables, int32_t);

    virtual void PoolSizeSet(CGxPool *, uint32_t) = 0;

    virtual char *BufLock(CGxBuf *);

    virtual int32_t BufUnlock(CGxBuf *, uint32_t);

    virtual void BufData(CGxBuf *buf, const void *data, size_t size, uintptr_t offset);

    virtual int32_t
    TexCreate(EGxTexTarget, uint32_t, uint32_t, uint32_t, EGxTexFormat, EGxTexFormat, CGxTexFlags, void *,
              void (*)(EGxTexCommand, uint32_t, uint32_t, uint32_t, uint32_t, void *, uint32_t &, const void *&),
              const char *, CGxTex *&);

    virtual void TexDestroy(CGxTex *texId);

    virtual void ShaderCreate(CGxShader *[], EGxShTarget, const char *, const char *, int32_t);

    virtual void ShaderConstantsSet(EGxShTarget, uint32_t, const float *, uint32_t);

    virtual void IShaderCreate(CGxShader *) = 0;

    virtual int32_t StereoEnabled() = 0;

    // Member functions
    CGxDevice();

    const CGxCaps &Caps() const;

    CGxBuf *BufCreate(CGxPool *, uint32_t, uint32_t, uint32_t);

    CGxBuf *BufStream(EGxPoolTarget, uint32_t, uint32_t);

    void DeviceCreatePools();

    void DeviceCreateStreamBufs();

    const CRect &DeviceCurWindow();

    void DeviceSetCurWindow(const CRect &);

    void DeviceSetDefWindow(CRect const &);

    const CRect &DeviceDefWindow();

    int32_t IDevIsWindowed();

    void IRsDirty(EGxRenderState);

    void IRsForceUpdate();

    void IRsForceUpdate(EGxRenderState);

    void IRsInit();

    void IRsSync(int32_t);

    void IShaderBind(void) {};

    void IShaderLoad(CGxShader *[], EGxShTarget, const char *, const char *, int32_t);

    void ITexBind(void) {};

    void ITexWHDStartEnd(CGxTex *, uint32_t &, uint32_t &, uint32_t &, uint32_t &);

    int32_t MasterEnable(EGxMasterEnables);

    CGxPool *PoolCreate(EGxPoolTarget, EGxPoolUsage, uint32_t, EGxPoolHintBits, const char *);

    void PrimIndexPtr(CGxBuf *);

    void PrimVertexFormat(CGxBuf *, CGxVertexAttrib *, uint32_t);

    void PrimVertexMask(uint32_t);

    void PrimVertexPtr(CGxBuf *, EGxVertexBufferFormat);

    void RsGet(EGxRenderState, int32_t &);

    void RsSet(EGxRenderState, int32_t);

    void RsSet(EGxRenderState, void *);

    void RsSetAlphaRef();

    void RsPop();

    void RsPush();

    void ShaderConstantsClear();

    char *ShaderConstantsLock(EGxShTarget target);

    void ShaderConstantsUnlock(EGxShTarget target, uint32_t index, uint32_t count);

    void TexMarkForUpdate(CGxTex *, const CiRect &, int32_t);

    void TexSetWrap(CGxTex *texId, EGxTexWrapMode wrapU, EGxTexWrapMode wrapV);

    void XformPop(EGxXform xf);

    void XformProjection(C44Matrix &);

    void XformProjNative(C44Matrix &);

    void XformPush(EGxXform xf);

    void XformSet(EGxXform xf, const C44Matrix &matrix);

    void XformSetViewport(float, float, float, float, float, float);

    void XformView(C44Matrix &);

    void XformViewport(float &, float &, float &, float &, float &, float &);
};

extern CGxDevice *g_theGxDevicePtr;
