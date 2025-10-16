#include "math.hpp"

Vec2 Vec2::operator/(float scalar) const {
    return Vec2(this->x / scalar, this->y / scalar);
}
