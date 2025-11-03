#pragma once

struct Vec2 {
    float x;
    float y;

    Vec2(float x = 0.0f, float y = 0.0f)
        : x(x),
        y(y)
    {}

    Vec2 operator+(Vec2 other) const;
    void operator+=(Vec2 other);
    Vec2 operator-() const;
    Vec2 operator-(Vec2 other) const;
    void operator-=(Vec2 other);
    Vec2 operator*(float scalar) const;
    Vec2 operator/(float scalar) const;
    void operator/=(float scalar);
    
    float length() const;
    Vec2 normalized() const;
};

struct Vec4 {
    float x;
    float y;
    float z;
    float w;

    Vec4(float x, float y, float z, float w)
        : x(x),
        y(y),
        z(z),
        w(w)
    {}

    Vec4(float value)
        : Vec4(value, value, value, value)
    {}
};
