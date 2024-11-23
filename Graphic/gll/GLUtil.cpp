#include "GLUtil.h"
#include "GL.h"
#include "Storm/Debug.h"


uint32_t GLLTextureTypeToIndex(GLEnum textureType) {
    uint32_t index;

    if (textureType == GL_TEXTURE_2D) {
        index = 0;
    } else if (textureType == GL_TEXTURE_3D) {
        index = 1;
    } else if (textureType == GL_TEXTURE_CUBE_MAP) {
        index = 2;
    } else if (textureType == GL_TEXTURE_RECTANGLE_NV) {
        index = 3;
    } else {
        index = 5;

        BLIZZARD_ASSERT(false);
    }

    return index;
}
