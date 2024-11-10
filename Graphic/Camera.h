#pragma once

#include <cstdint>
#include "Common/DataMgr.h"
#include <NTempest/CRect.h>
#include <NTempest/C2Vector.h>

using namespace NTempest;

typedef HDATAMGR HCAMERA;


HCAMERA CameraCreate();

void CameraSetupScreenProjection(const CRect &, const C2Vector &, float, int32_t);

void CameraSetupWorldProjection(HCAMERA camera, const CRect &projectionRect, uint32_t flags);


