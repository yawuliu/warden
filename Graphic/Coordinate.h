#pragma once

float CoordinateGetAspectCompensation();

void CoordinateSetAspectRatio(float);

void DDCToNDC(float, float, float *, float *);

float DDCToNDCHeight(float);

float DDCToNDCWidth(float);

void NDCToDDC(float, float, float *, float *);

float NDCToDDCHeight(float);

float NDCToDDCWidth(float);


