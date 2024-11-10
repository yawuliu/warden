#include "GLAbstractWindow.h"
#include <cmath>

int32_t GLAbstractWindow::GetBackingWidth() {
    return static_cast<int32_t>(std::floor(this->GetBackingRect().Width()));
}

int32_t GLAbstractWindow::GetBackingHeight() {
    return static_cast<int32_t>(std::floor(this->GetBackingRect().Height()));
}

int32_t GLAbstractWindow::GetWidth() {
    return static_cast<int32_t>(std::floor(this->GetRect().Width()));
}

int32_t GLAbstractWindow::GetHeight() {
    return static_cast<int32_t>(std::floor(this->GetRect().Height()));
}
