#pragma once

#include <cstdint>
#include <NTempest/C3Vector.h>

using namespace NTempest;

class CGxStateBom {
public:
    // Member variables
    union {
        int32_t i[3];
        uint32_t u[3];
        float f[3];
        void *p;
    } m_data;

    int32_t filler;

    // Member functions
    CGxStateBom &operator=(float);

    CGxStateBom &operator=(int32_t);

    CGxStateBom &operator=(uint32_t);

    CGxStateBom &operator=(void *);

    CGxStateBom &operator=(C3Vector &);

    bool operator==(float);

    bool operator==(int32_t);

    bool operator==(uint32_t);

    bool operator==(void *) const;

    bool operator==(C3Vector &);

    bool operator!=(float);

    bool operator!=(int32_t);

    bool operator!=(uint32_t);

    bool operator!=(void *) const;

    bool operator!=(C3Vector &);

    bool operator!=(CGxStateBom &);

    explicit operator CImVector() const;

    explicit operator float() const;

    explicit operator int32_t() const;

    explicit operator uint32_t() const;

    explicit operator void *() const;
};


