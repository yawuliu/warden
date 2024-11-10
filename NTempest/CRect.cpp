#include "CRect.h"
#include "C2Vector.h"
#include <cmath>

using namespace NTempest;

CRect CRect::Intersection(const CRect &l, const CRect &r) {
    CRect i;

    i.maxX = r.maxX <= l.maxX ? r.maxX : l.maxX;
    i.maxY = r.maxY <= l.maxY ? r.maxY : l.maxY;
    i.minX = r.minX >= l.minX ? r.minX : l.minX;
    i.minY = r.minY >= l.minY ? r.minY : l.minY;

    return i;
}

CRect::CRect() {
    minY = 0.0f; // t
    minX = 0.0f; // l
    maxY = 0.0f; // b
    maxX = 0.0f; // r
}

CRect::CRect(float miny, float minx, float maxy, float maxx) : minY(miny), minX(minx), maxY(maxy), maxX(maxx) {}

bool CRect::operator==(CRect &rect) {
    return this->minX == rect.minX && this->minY == rect.minY && this->maxX == rect.maxX &&
           this->maxY == rect.maxY;
}


bool CRect::IsPointInside(const C2Vector &pt) {
    return this->minX <= pt.x && this->maxX >= pt.x && this->minY <= pt.y && this->maxY >= pt.y;
}

CRect *CRect::Clamp(C2Vector &a2) {
    float y;
    float lminy;
    float lminx;

    y = a2.y;
    if (this->minY <= y)
        lminy = fminf(this->maxY, y);
    else
        lminy = this->minY;
    a2.y = lminy;
    if (this->minX <= a2.x)
        lminx = fminf(this->maxX, a2.x);
    else
        lminx = this->minX;
    a2.x = lminx;
    return this;
}

//bool NTempest::operator==(const CRect &rectA, const CRect &rectB) {
//    return rectA.minX == rectB.minX && rectA.minY == rectB.minY && rectA.maxX == rectB.maxX &&
//           rectA.maxY == rectB.maxY;
//}
bool CRect::Sub4826D0() const {
    return this->maxY < 0.0f || this->minY > 1.0f || this->maxX < 0.0f || this->minX > 1.0f;
}

const float &CRect::Width() const {
    return this->maxX - this->minX;
}

const float &CRect::Height() const {
    return this->maxY - this->minY;
}