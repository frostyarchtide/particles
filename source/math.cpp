#include <math.h>

#include "math.hpp"

Vec2 Vec2::operator+(Vec2 other) const {
    return Vec2(this->x + other.x, this->y + other.y);
}

void Vec2::operator+=(Vec2 other) {
    *this = *this + other;
}

Vec2 Vec2::operator-() const {
    return *this * -1.0f;
}

Vec2 Vec2::operator-(Vec2 other) const {
    return Vec2(this->x - other.x, this->y - other.y);
}

void Vec2::operator-=(Vec2 other) {
    *this = *this - other;
}

Vec2 Vec2::operator*(float scalar) const {
    return Vec2(this->x * scalar, this->y * scalar);
}

Vec2 Vec2::operator/(float scalar) const {
    return Vec2(this->x / scalar, this->y / scalar);
}

void Vec2::operator/=(float scalar) {
    *this = *this / scalar;
}

float Vec2::length() const {
    return sqrtf(x * x + y * y);
}

Vec2 Vec2::normalized() const {
    return *this / length();
}
